<?php

/**
 * @file
 * This file contains search settings form functions.
 */

/**
 * Page callback for 'admin/settings/search'.
 */
function ampapi_activity_search_settings_form($form, &$form_state) {
  $search_settings = ampapi_activity_get_search_settings();

  $form['ampapi_activity_search_settings'] = array(
    '#tree' => TRUE,
  );

  $form_elements['ssc'] = array(
    '#type' => 'fieldset',
    '#title' => t('SSC Integration'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#parents' => array('ampapi_activity_search_settings'), // Remove the fieldset from the submitted values structure.
  );

  // @TODO: Check if SSC functionality is enabled in the API, before allowing
  // the admins to change anything.
  $form_elements['ssc']['ssc_status'] = array(
    '#type' => 'hidden',
    '#value' => $search_settings['ssc_status'],
  );

  if (empty($search_settings['ssc_status'])) {
    $form_elements['ssc']['#title'] .= ' (disabled)';
    $form_elements['ssc']['#description'] = t('South-South Cooperation search functionality and widgets are disabled.');
    $form_elements['ssc']['enable_ssc'] = array(
      '#type' => 'button',
      '#value' => t('Enable SSC'),
      '#submit' => array('ampapi_activity_search_settings_form_ssc_submit'),
      '#executes_submit_callback' => TRUE,
    );
  }
  else {
    $form_elements['ssc']['#title'] .= ' (enabled)';
    $form_elements['ssc']['#description'] = t('South-South Cooperation search functionality and widgets are enabled.');
    $form_elements['ssc']['disable_ssc'] = array(
      '#type' => 'button',
      '#value' => t('Disable SSC'),
      '#submit' => array('ampapi_activity_search_settings_form_ssc_submit'),
      '#executes_submit_callback' => TRUE,
    );
  }

  // Prepare a list of available columns.
  $full_columns_list = array();
  $full_filters_list = array();
  $mappers = ampapi_get_mappers();
  foreach ($mappers as $key => $plugin) {
    if (empty($plugin['property name'])) {
      continue;
    }

    if (!empty($plugin['report filter key']) || !empty($plugin['report filter endpoint'])) {
      // Add to the list of available filters.
      $full_filters_list[$plugin['property name']] = $plugin['title'];
    }

    // Hide SSC specific fields when SSC functionality is disabled.
    if (empty($search_settings['ssc_status']) && !empty($plugin['report field ssc'])) {
      continue;
    }

    // Add to the list of available columns.
    $full_columns_list[$plugin['property name']] = $plugin['title'];
  }
  ksort($full_columns_list);
  ksort($full_filters_list);

  $form_elements['columns'] = array(
    '#type' => 'fieldset',
    '#title' => t('Enabled Columns'),
    '#description' => t('A list of columns to be displayed in the search results table.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#parents' => array('ampapi_activity_search_settings'), // Remove the fieldset from the submitted values structure.
  );

  // We always want the activity id and title to be visible.
  $controllable_columns_list = $full_columns_list;
  unset($controllable_columns_list['id']);
  unset($controllable_columns_list['title']);

  $notes = theme('item_list', array('items' => array(
    t('Only columns that are also enabled in AMP will be displayed.'),
    t('For SSC columns to be displayed the SSC integration needs to be enabled.'),
    t('The title and details link columns are always displayed.'),
  )));
  $form_elements['columns']['enabled_columns'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Enabled search columns'),
    '#description' => t('Please select the enabled columns. NOTES: !notes', array('!notes' => $notes)),
    '#options' => $controllable_columns_list,
    '#default_value' => $search_settings['enabled_columns'],
    '#element_validate' => array('ampapi_activity_search_enabled_columns_validate'),
  );

  $form_elements['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Enabled Filters'),
    '#description' => t('A list of filters to be displayed in the search form.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#parents' => array('ampapi_activity_search_settings'), // Remove the fieldset from the submitted values structure.
  );

  // We always want the activity id and title to be visible.
  $controllable_filters_list = $full_filters_list;

  // Do not allow admins to disabled the title (keywords) search filter.
  unset($controllable_filters_list['title']);

  // Allow admins to disable the activities_search_type filter.
  if (!empty($search_settings['ssc_status'])) {
    $controllable_filters_list['activities_search_type'] = t('Activities Search Type');
  }

  $notes = theme('item_list', array('items' => array(
    t('Only filters that are also enabled in AMP will be displayed.'),
    t('It is recommended to also enable the column for each of the enabled filters.'),
    t('The "Search Terms" filter is always displayed.'),
  )));
  $form_elements['filters']['enabled_filters'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Enabled search filters'),
    '#description' => t('Please select the enabled filters. NOTES: !notes', array('!notes' => $notes)),
    '#options' => $controllable_filters_list,
    '#default_value' => $search_settings['enabled_filters'],
    '#element_validate' => array('ampapi_activity_search_enabled_filters_validate'),
  );

  $form_elements['sort'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default Sort'),
    '#description' => t('<h4>Feature not implemented yet.</h4>') . t("The column on which the results should be sorted by default if the user didn't change the sort."),

    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#parents' => array('ampapi_activity_search_settings'), // Remove the fieldset from the submitted values structure.
  );

  // TODO: Allow administrators to change the default sort.
  $form_elements['sort']['default_sort'] = array(
    '#disabled' => TRUE,
    '#type' => 'radios',
    '#title' => t('Default Sort'),
    '#description' => t('Please select the default sort column.'),
    '#options' => $full_columns_list,
    '#default_value' => $search_settings['default_sort'],
    '#element_validate' => array('ampapi_activity_search_enabled_columns_validate'),
  );

  // Let's allow users to select global amount option.
  $amount_units_settings = _ampapi_activity_get_api_settings('amount-format:number-divider');
  $amount_units_options = array();
  foreach ($amount_units_settings->value->options as $delta => $amount_unit_option) {
    $amount_units_options[$amount_unit_option->id] = $amount_unit_option->name;
  }
  $form_elements['amount_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Amount Options'),
    '#description' => t("These options change the global amount formatting for the numeric output for measure columns."),

    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#parents' => array('ampapi_activity_search_settings'), // Remove the fieldset from the submitted values structure.
  );
  $form_elements['amount_settings']['global_amount'] = array(
    '#type' => 'select',
    '#title' => t('Global (Search) Amounts'),
    '#options' => $amount_units_options,
    '#default_value' => $search_settings['global_amount'],
    '#description' => t('Please specify which global amount formatting option you would like to use.'),
  );

  $form_elements['misc_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Misc'),
    '#description' => t("All the miscellaneous settings can be found here."),

    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#parents' => array('ampapi_activity_search_settings'), // Remove the fieldset from the submitted values structure.
  );
  $form_elements['misc_settings']['front_search_collapsed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Front Search - Default to Collapsed'),
    '#description' => t('If you wish to have an expanded search on the homepage, uncheck this box.'),
    '#default_value' => isset($search_settings['front_search_collapsed']) ? $search_settings['front_search_collapsed'] : TRUE,
  );

  $filter_options = _ampapi_activity_search_get_exposed_filters();
  $form_elements['misc_settings']['search_exposed_main_widget'] = array(
    '#type' => 'select',
    '#title' => t('Main Search Field'),
    '#description' => t('This field will appear as first filter, and if the search form is collapsed, it will be the default field shown.'),
    '#options' => $filter_options,
    '#default_value' => isset($search_settings['search_exposed_main_widget']) ? $search_settings['search_exposed_main_widget'] : 'search',
  );
  $form_elements['misc_settings']['search_move_keywords_last'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move Search Terms to the bottom'),
    '#description' => t('If you check this box, the keyword search will actually be displayed as the last item.'),
    '#default_value' => isset($search_settings['search_move_keywords_last']) ? $search_settings['search_move_keywords_last'] : FALSE,
    '#states' => array(
      'invisible' => array(
        ":input[name=\"ampapi_activity_search_settings[search_exposed_main_widget]\"]" => array('value' => 'search'),
      ),
    )
  );


  $form['ampapi_activity_search_settings'] += $form_elements;
  $form['#submit'][] = 'ampapi_activity_search_settings_form_submit';

  return system_settings_form($form);
}

/**
 * Form element validation handler for enabled_columns checkboxes.
 */
function ampapi_activity_search_enabled_columns_validate($element, &$form_state, $form) {
  // Only save the list of enabled columns.
  $key = 'ampapi_activity_search_settings';
  $enabled_columns = $form_state['values'][$key]['enabled_columns'];
  $enabled_columns = array_filter($enabled_columns);
  $form_state['values'][$key]['enabled_columns'] = $enabled_columns;

  // Select all of the measure columns and make sure at least 1 is enabled.
  $mappers = ampapi_get_mappers();
  $measure_columns = array();
  foreach ($mappers as $key => $plugin) {
    if (!empty($plugin['property name']) && $plugin['report field group'] == 'measures') {
      $measure_columns[$plugin['property name']] = $plugin['title'];
    }
  }
  if (!empty($measure_columns)) {
    $enabled_measures = array_intersect(array_keys($measure_columns), array_keys($enabled_columns));
    if (empty($enabled_measures)) {
      $measures = implode(', ', $measure_columns);
      form_set_error('columns', t('Please make sure you have enabled at least 1 measures column.<br />Measures columns are: %measures.', array('%measures' => $measures)));
    }
  }
}

/**
 * Form element validation handler for enabled_filters checkboxes.
 */
function ampapi_activity_search_enabled_filters_validate($element, &$form_state, $form) {
  // Only save the list of enabled columns.
  $key = 'ampapi_activity_search_settings';
  $enabled_filters = $form_state['values'][$key]['enabled_filters'];
  $enabled_filters = array_filter($enabled_filters);
  $form_state['values'][$key]['enabled_filters'] = $enabled_filters;
}

/**
 * Submit handler for ampapi_activity_search_settings_form().
 */
function ampapi_activity_search_settings_form_ssc_submit($form, &$form_state) {
  $search_settings = ampapi_activity_get_search_settings();

  if ($form_state['triggering_element']['#value'] == t('Enable SSC')) {
    $search_settings['ssc_status'] = TRUE;
  }
  else {
    $search_settings['ssc_status'] = FALSE;
  }

  variable_set('ampapi_activity_search_settings', $search_settings);
}

/**
 * Form submission handler for ampapi_activity_search_settings_form().
 */
function ampapi_activity_search_settings_form_submit($form, &$form_state) {
  views_invalidate_cache();
}

/**
 * Small helper function that returns an array of all exposed (available) filters.
 */
function _ampapi_activity_search_get_exposed_filters() {
  $name = 'activities';
  $display_id = 'search_page';
  $view = views_get_view($name);
  if (empty($view)) {
    return array('' => '- Something went wrong -');
  }

  if (!$view->access($display_id)) {
    return array('' => '- Something went wrong -');
  }

  $view->set_display($display_id);
  $view->pre_execute();

  // Let modules modify the view just prior to building it.
  // @see Views::build();
  foreach (module_implements('views_pre_build') as $module) {
    $function = $module . '_views_pre_build';
    $function($view);
  }

  $filters = $view->filter;
  $output = array();
  foreach ($filters as $filter_id => $filter) {
    if ($filter->options['exposed'] === TRUE) {
      $output[$filter->options['expose']['identifier']] = $filter->options['expose']['label'];
    }
  }
  return $output;
}
