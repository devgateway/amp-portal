<?php

/**
 * AMP Reports custom views area handler.
 */
class ampreports_views_handler_area_result extends views_handler_area_result {

  /**
   * Define additional options.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['chart'] = array(
      'default' => TRUE,
      'bool' => TRUE,
    );
    $options['chart_sectors'] = array(
      'default' => 8,
    );
    $options['chart_projects_length'] = array(
      'default' => 10,
    );
    unset($options['content']);
    return $options;
  }

  /**
   * Alter the form to include our newly defined options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['chart'] = array(
      '#type' => 'checkbox',
      '#title' => t('Include the Google Chart'),
      '#description' => t('If you would like to render the Google Chart, check this box.'),
      '#default_value' => isset($this->options['chart']) ? $this->options['chart'] : TRUE,
    );
    $form['chart_sectors'] = array(
      '#type' => 'textfield',
      '#title' => t('Number of Sectors to show'),
      '#description' => t('All of the other sectors will be Summed up together in the "Other" category.'),
      '#default_value' => isset($this->options['chart_sectors']) ? $this->options['chart_sectors'] : 8,
      '#dependency' => array('edit-options-chart' => array(TRUE)),
    );
    $form['chart_projects_length'] = array(
      '#type' => 'textfield',
      '#title' => t('Length of Project Names'),
      '#description' => t('Max length of the Projects Name.'),
      '#default_value' => isset($this->options['chart_projects_length']) ? $this->options['chart_projects_length'] : 10,
      '#dependency' => array('edit-options-chart' => array(TRUE)),
    );
    unset($form['content']);
    return $form;
  }

  /**
   * Take care of the rendering part.
   */
  function render($empty = FALSE) {
    global $user;
    $output = array();

    if (empty($this->view->exposed_input['location_dep']) && empty($this->view->exposed_input['location_mun'])) {
      return t('Please select a department or municipality.');
    }

    $department = $this->view->exposed_input['location_dep'];
    $municipality = !empty($this->view->exposed_input['location_mun']) ? $this->view->exposed_input['location_mun'] : FALSE;
    $status = !empty($this->view->exposed_input['status']) ? $this->view->exposed_input['status'] : 0;
    $count_all = $this->view->total_rows;

    $output['stats'] = array(
      '#type' => 'container',
      '#attributes' => array('class' => array('stats-wrapper')),
    );
    if (!empty($department)) {
      if (!empty($municipality)) {
        $output['stats']['department'] = array(
          '#markup' => t('<div class="stats-query">Department of @department, municipality @municipality</div>', array(
            '@department' => $department,
            '@municipality' => $municipality,
          )),
        );
      }
      else {
        $output['stats']['department'] = array(
          '#markup' => t('<div class="stats-query">Department of @department</div>', array(
            '@department' => $department,
          )),
          '#weight' => 0,
        );
      }
    }
    else {
      // The extra case, no department, just municipalities.
      if (!empty($municipality)) {
        $output['stats']['department'] = array(
          '#markup' => t('<div class="stats-query">Municipality @municipality</div>', array(
            '@municipality' => $municipality,
          )),
        );
      }
    }

    // Let's find out, how many are 'in execution' (or, any value specified in the settings of 'status').
    if ($status == 0) {
      $view_clone = $this->view->clone_view();
      $new_exposed_input = $this->view->get_exposed_input();
      $new_exposed_input['status'] = 1;
      $view_clone->set_exposed_input($new_exposed_input);
      $view_clone->set_items_per_page('0');
      $view_clone->execute();
      $count_status = $view_clone->total_rows;

      // Load options.
      $status_value_ops = $view_clone->filter['status']->get_value_options();

      if (is_array($view_clone->filter['status']->value)) {
        $status_value_key = reset($view_clone->filter['status']->value);
      }
      else {
        $status_value_key = $view_clone->filter['status']->value;
      }
      $output['stats']['count_all'] = array(
        '#markup' => '<div class="count-all">' . t('Total number of projects:') .
            format_string('<div class="count-value">@count_all</div>', array(
              '@count_all' => $count_all,
            )) . '</div>',
        '#weight' => 5,
      );
      $output['stats']['count_status'] = array(
        '#markup' => '<div class="count-all">' . t('Total number of projects "@status":', array(
            '@status' => $status_value_ops[$status_value_key],
          )) . format_string('<div class="count-value">@count_status</div>', array(
            '@count_status' => $count_status,
          )) . '</div>',
        '#weight' => 10,
      );

      // OMG that's a pain, we NEED to revert.
      unset($new_exposed_input['status']);
      unset($this->view->exposed_raw_input['status']);
      $this->view->set_exposed_input($new_exposed_input);
    }
    else {
      // Load options.
      $status_value_ops = $this->view->filter['status']->get_value_options();
      $status_value_key = reset($this->view->filter['status']->value);
      $view_clone = $this->view->clone_view();
      $view_clone->exposed_input = $this->view->exposed_input;
      $view_clone->set_items_per_page('0');
      $view_clone->execute();

      $output['stats']['count_status'] = array(
        '#markup' => '<div class="count-all">' . t('Total number of projects "@status":', array(
            '@status' => $status_value_ops[$status_value_key],
          )) . format_string('<div class="count-value">@count_status</div>', array(
            '@count_status' => $count_all,
          )) . '</div>',
        '#weight' => 10,
      );
    }

    // Render the chart.
    if ($this->options['chart'] == TRUE) {
      $output['chart'] = array(
        '#markup' => '<div id="projects_chart"></div>',
      );
      $this->get_google_chart($view_clone->result);
      $view_clone->destroy();
    }

    return render($output);
  }

  /**
   * Draw the chart.
   */
  function get_google_chart($results) {
    // Polish the results and structure them properly.
    $normalized_data = array();
    foreach ($results as $result) {
      if (strpos($result->primary_sector, '.') !== FALSE) {
        list($id, $sector) = explode('.', $result->primary_sector);
        $sector = trim($sector);
      }
      else if (strpos($result->primary_sector, '-') !== FALSE) {
        list($id, $sector) = explode('-', $result->primary_sector);
        $sector = trim($sector);
      }
      else {
        $sector = $result->primary_sector;
      }
      if (strlen($sector) > $this->options['chart_projects_length']) {
        $sector = substr($sector, 0, $this->options['chart_projects_length']) . '...';
      }
      $sector = ucfirst(strtolower($sector));
      $normalized_data[$sector] = (!isset($normalized_data[$sector])) ? 0 : $normalized_data[$sector] + 1;
    }
    arsort($normalized_data);
    $cutoff = $this->options['chart_sectors'];
    $showing = array_slice($normalized_data, 0, $cutoff);
    $rest = array_sum(array_slice($normalized_data, $cutoff));
    $all_sectors = $showing + array(t('Other') => $rest);

    // Proper settings.
    $settings['chart']['projects_chart'] = array(
      'chartType' => 'ColumnChart',
      'containerId' => 'projects_chart',
      'columns' => array(t('Projects')),
      'header' => array_keys($all_sectors),
      'rows' => array(array_values($all_sectors)),
      'options' => array(
        'forceIFrame' => FALSE,
        'title' => t('Projects by Sectors'),
        'width' => 1000,
        'height' => 600,
        'legend' => array('position' => 'none'),
        'vAxis' => array(
          'textStyle' => array(
            'fontSize' => '10',
          ),
        ),
        'hAxis' => array(
          'textStyle' => array(
            'fontSize' => '10',
          ),
        ),
      ),
    );

    // Now draw.
    draw_chart($settings);
  }
}
