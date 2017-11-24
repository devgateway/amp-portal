<?php


/**
 * Implements hook_form_alter().
 */
function ampreports_form_views_exposed_form_alter(&$form, &$form_state) {
  $view = $form_state['view'];
  if ($view->name == 'reports' && $view->current_display == 'report_page') {
    $form['location_dep']['#ajax'] = array(
      'callback' => 'ampreports_location_filter_ajax_callback',
      'wrapper' => 'location-municipality',
      'effect' => 'fade',
      'event' => 'change',
    );
    $form['location_mun']['#prefix'] = '<div id="location-municipality">';
    $form['location_mun']['#suffix'] = '</div>';

    if (!empty($form['location_mun']['#autocomplete_path'])) {
      $form['location_mun']['#autocomplete_path'] .= '/2:';
      if (!empty($form_state['values']['location_dep']) && trim($form_state['values']['location_dep']) !== '') {
        $form['location_mun']['#autocomplete_path'] .= drupal_encode_path($form_state['values']['location_dep']);
      }
      elseif (!empty($form_state['input']['location_dep']) && trim($form_state['input']['location_dep']) !== '') {
        $form['location_mun']['#autocomplete_path'] .= drupal_encode_path($form_state['input']['location_dep']);
      }
    }
    else {
      if (!empty($form_state['values']['location_dep']) && trim($form_state['values']['location_dep']) !== '') {
        $form['location_mun']['#attributes']['data-extra-filter'] = '2:' . drupal_encode_path($form_state['values']['location_dep']);
      }
      elseif (!empty($form_state['input']['location_dep']) && trim($form_state['input']['location_dep']) !== '') {
        $form['location_mun']['#attributes']['data-extra-filter'] = '2:' . drupal_encode_path($form_state['input']['location_dep']);
      }
    }

    $svgicon_search = helpertheme_get_svg_icons('search', array(
      'width' => '1em',
      'height' => '1em'
    ));
    $svgicon_clear = helpertheme_get_svg_icons('delete', array(
      'width' => '1em',
      'height' => '1em'
    ));
    $form['submit']['#prefix'] = $svgicon_search . $svgicon_clear;
  }
}

/**
 * A custom form AJAX callback.
 */
function ampreports_location_filter_ajax_callback($form, $form_state) {
  return $form['location_mun'];
}

/**
 * Implements hook_views_pre_build().
 */
function ampreports_views_pre_build(&$view) {
  if ($view->name == 'reports' && $view->current_display == 'report_page') {
    $view->get_exposed_input();
    if (empty($view->exposed_input['location_dep']) && empty($view->exposed_input['location_mun'])) {
      $view->executed = TRUE;
    }
  }
}

/**
 * Implements hook_views_pre_render().
 */
function ampreports_views_pre_render(&$view) {
  if ($view->name == 'reports' && $view->current_display == 'report_page') {
    $css_path = drupal_get_path('module', 'ampreports') . '/styles/report.styles.css.less';
    drupal_add_css($css_path, array('preprocess' => FALSE));
  }
}

/**
 * Custom overridden version of draw_charts (google_chart_tools.module).
 */
function _ampreports_custom_draw_chart($settings) {
  drupal_alter('draw_chart', $settings);
  foreach ($settings['chart'] as $id => $chart) {
    if (!isset($settings['chart'][$id]['containerId'])) {
      $settings['chart'][$id]['containerId'] = drupal_strtolower(str_replace(" ", "-", $id));
    }
  }
  drupal_add_css(drupal_get_path('module', 'google_chart_tools') . '/google_chart_tools.css');
  drupal_add_js(drupal_get_path('module', 'ampreports') . '/js/custom_google_charts.js');
  drupal_add_js($settings, array('type' => 'setting'));
  $ret = array(
    'title' =>  $chart['options']['title'],
    'id' =>  $id,
    'weight' => isset($chart['weight']) ? $chart['weight'] : 0,
    'markup' =>  "<div id='{$settings['chart'][$id]['containerId']}'></div>"
  );
  return $ret;
}

/**
 * Implements hook_menu().
 */
function ampreports_menu() {
  $items = array();

  $items['ampreports/chart'] = array(
    'title' => 'Chart export path',
    'page callback' => 'ampreports_charts_ajax',
    'page arguments' => array(2),
    'access callback' => TRUE,
    'type' => MENU_CALLBACK,
  );

  return $items;
}

/**
 * Ajax callback that saves the graph-image to the server-side,
 * to be used later in the PDF / DOC export.
 */
function ampreports_charts_ajax($hash) {
  $result = FALSE;

  if ($hash && !empty($_POST['image'])) {
    // Sanitize.
    $image = preg_replace('#^data:image/\w+;base64,#i', '', $_POST['image']);
    $data = base64_decode($image);

    // Find out the mime.
    $finfo = finfo_open();
    $mime_type = finfo_buffer($finfo, $data, FILEINFO_MIME_TYPE);
    finfo_close($finfo);

    // Save only PNG mime.
    if ($mime_type === 'image/png') {
      $file = file_save_data($data, 'public://' . $hash . '.png', FILE_EXISTS_REPLACE);

      // Save temporary staate.
      $file->status = 0;
      file_save($file);

      $result = 'saved';
    }
  }

  drupal_json_output($result);
}
