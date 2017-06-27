<?php


/**
 * Implements hook_form_alter().
 */
function ampreports_form_views_exposed_form_alter(&$form, &$form_state) {
  $form['location_dep']['#ajax'] = array(
    'callback' => 'ampreports_location_filter_ajax_callback',
    'wrapper' => 'location-municipality',
    'effect' => 'fade',
  );
  $form['location_mun']['#prefix'] = '<div id="location-municipality">';
  $form['location_mun']['#suffix'] = '</div>';

  if (!empty($form_state['input']['location_dep'])) {
    $form['location_mun']['#autocomplete_path'] .= '/3:' . drupal_encode_path($form_state['input']['location_dep']);
  }
  elseif (!empty($form_state['values']['location_dep'])) {
    $form['location_mun']['#autocomplete_path'] .= '/3:' . drupal_encode_path($form_state['values']['location_dep']);
  }
  elseif (empty($form_state['input']['location_dep'])) {
    $form['location_mun']['#disabled'] = TRUE;
  }
}

/**
 * A custom form AJAX callback.
 */
function ampreports_location_filter_ajax_callback($form, $form_state) {
  return $form['location_mun'];
}
