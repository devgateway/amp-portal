<?php

/**
 * @file
 * This file contains form/UI cleanup functions.
 */

/**
 * Page callback for 'admin/settings/ui'.
 */
function helpergeneric_ui_settings_form($form) {
  $form = array();

  $cleanup_ui_force = helpergeneric_cleanup_ui();

  $form['cleanup_ui'] = array(
    '#type' => 'fieldset',
    '#title' => t('UI settings'),
    '#description' => '<p>' . t('By default the UI is cleaned, you can disable this behaviour and have access to more options. This is only as a UI cleanup functionality and not a security feature.') . '</p><p>' . t('<strong>DO NOT CLICK</strong> on these buttons unless you were told to!') . '</p>',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
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

  return $form;
}

/**
 * Submit handler for helpergeneric_ui_settings_form().
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
 * Page callback for 'admin/settings/generic'.
 */
function helpergeneric_settings_form($form) {
  $form = array();

  return system_settings_form($form);
}
