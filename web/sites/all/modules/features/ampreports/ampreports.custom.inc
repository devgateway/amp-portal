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
    );
    $form['location_mun']['#prefix'] = '<div id="location-municipality">';
    $form['location_mun']['#suffix'] = '</div>';

    $form['location_mun']['#autocomplete_path'] .= '/3:';
    if (!empty($form_state['values']['location_dep']) && trim($form_state['values']['location_dep']) !== '') {
      $form['location_mun']['#autocomplete_path'] .= drupal_encode_path($form_state['values']['location_dep']);
    }
    elseif (!empty($form_state['input']['location_dep']) && trim($form_state['input']['location_dep']) !== '') {
      $form['location_mun']['#autocomplete_path'] .= drupal_encode_path($form_state['input']['location_dep']);
    }

    $svgicon = helpertheme_get_svg_icons('search', array(
      'width' => '1em',
      'height' => '1em'
    ));
    $form['submit']['#prefix'] = $svgicon;
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