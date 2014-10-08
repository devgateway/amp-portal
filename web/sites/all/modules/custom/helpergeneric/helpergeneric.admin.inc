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
  if ($form_state['triggering_element']['#value'] == t('Enable')) {
    // Enable UI cleanup.
    setcookie('helpergeneric_cleanup_ui_force', 1, REQUEST_TIME + (60 * 60 * 12), base_path());
  }
  else {
    // Disable UI cleanup.
    setcookie('helpergeneric_cleanup_ui_force', 0, REQUEST_TIME - (60 * 60 * 12), base_path());
  }
}

/**
 * Page callback for 'admin/settings/generic'.
 */
function helpergeneric_settings_form($form) {
  $form = array();

  $form['site_information'] = array(
    '#type' => 'fieldset',
    '#title' => t('Site details'),
  );
  $form['site_information']['site_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Site name'),
    '#description' => t('The site name will be transformed to uppercase before displaying in the header.'),
    '#default_value' => variable_get('site_name', 'Drupal'),
    '#required' => TRUE
  );
  // $form['site_information']['site_slogan'] = array(
  //   '#type' => 'textfield',
  //   '#title' => t('Slogan'),
  //   '#default_value' => variable_get('site_slogan', ''),
  //   '#description' => t("How this is used depends on your site's theme."),
  // );
  $form['site_information']['site_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address'),
    '#default_value' => variable_get('site_mail', ini_get('sendmail_from')),
    '#description' => t("The <em>From</em> address in automated e-mails sent during registration and new password requests, and other notifications. (Use an address ending in your site's domain to help prevent this e-mail being flagged as spam.)"),
    '#required' => TRUE,
  );

  $form['#validate'][] = 'helpergeneric_settings_form_validate';

  return system_settings_form($form);
}

/**
 * Validates the submitted site-information form.
 */
function helpergeneric_settings_form_validate($form, &$form_state) {
  // Validate the e-mail address.
  if ($error = user_validate_mail($form_state['values']['site_mail'])) {
    form_set_error('site_mail', $error);
  }
}
