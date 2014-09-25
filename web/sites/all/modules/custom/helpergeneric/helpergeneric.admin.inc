<?php

/**
 * @file
 * This file contains form/UI cleanup functions.
 */

/**
 * Page callback for 'admin/settings/generic'.
 */
function helpergeneric_settings_form($form) {
  $form = array();

  $cleanup_ui_force = TRUE;
  if (isset($_COOKIE['helpergeneric_cleanup_ui_force'])) {
    $cleanup_ui_force = (bool) $_COOKIE['helpergeneric_cleanup_ui_force'];
  }

  $form['cleanup_ui'] = array(
    '#type' => 'fieldset',
    '#title' => t('UI settings'),
    '#description' => '<p>' . t('By default the UI is cleaned, you can disable this behaviour and have access to more options. This is only as a UI cleanup functionality and not a security feature.') . '</p><p>' . t('<strong>DO NOT CLICK</strong> on these buttons unless you were told to!') . '</p>',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['cleanup_ui']['enable'] = array(
    '#type' => 'button',
    '#value' => 'Enable',
    '#disabled' => $cleanup_ui_force,
    '#submit' => array('helpergeneric_toggle_cleanup_ui_force_submit'),
    '#executes_submit_callback' => TRUE,
  );

  $form['cleanup_ui']['disable'] = array(
    '#type' => 'button',
    '#value' => 'Disable',
    '#disabled' => !$cleanup_ui_force,
    '#submit' => array('helpergeneric_toggle_cleanup_ui_force_submit'),
    '#executes_submit_callback' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * Submit handler for helpergeneric_settings_form().
 */
function helpergeneric_toggle_cleanup_ui_force_submit($form, &$form_state) {
  if ($form_state['triggering_element']['#value'] == 'Enable') {
    // Enable UI cleanup.
    setcookie('helpergeneric_cleanup_ui_force', 1, NULL, base_path());
  }
  else {
    // Disable UI cleanup.
    setcookie('helpergeneric_cleanup_ui_force', 0, NULL, base_path());
  }
}

/**
 * Page callback: Outputs JSON for entity autocomplete suggestions.
 */
function helpergeneric_entity_autocomplete($entity_type, $string = '') {
  $matches = array();

  if (empty($string)) {
    return drupal_json_output($matches);
  }

  // @TODO: Log error!
  $entity_info = entity_get_info($entity_type);
  if (empty($entity_info)) {
    return drupal_json_output($matches);
  }

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', $entity_type, '=')
        // ->fieldCondition('title_field', 'title_field_value', '%' . db_like($string) . '%', 'LIKE')
        ->propertyCondition('title', '%' . db_like($string) . '%', 'LIKE')
        ->propertyOrderBy('title')
        ->range(0, 10);
  $result = $query->execute();

  foreach ($result[$entity_type] as $entity_id => $entity) {
    // @TODO: Optimize!
    $entity = entity_load_single($entity_type, $entity_id);
    $return_value = check_plain($entity->label()) . ' (' . $entity->identifier() . ')';
    $matches[$return_value] = $return_value;
  }

  drupal_json_output($matches);
}
