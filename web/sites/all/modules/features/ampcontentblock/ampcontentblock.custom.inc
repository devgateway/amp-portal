<?php
/**
 * @file
 * ampcontentblock.custom.inc
 */

/**
 * Implements hook_field_formatter_info().
 */
function ampcontentblock_field_formatter_info() {
  return array(
    'ampcontentblock_widget_callback' => array(
      'label' => t('Widget Callback'),
      'description' => t('Display the rendered content returned by the callback function.'),
      'field types' => array('list_text'),
      'settings' => array(
        'callback' => '',
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function ampcontentblock_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $element = array();
  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function ampcontentblock_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $summary = array();
  return implode('<br />', $summary);
}

/**
 * Implements hook_field_formatter_view().
 */
function ampcontentblock_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $result = array();
  $settings = $display['settings'];

  switch ($display['type']) {
    case 'ampcontentblock_widget_callback':
      $widget_callback = array_shift($items);

      include_once 'ampcontentblock.predefined.inc';
      if (function_exists($widget_callback['value'])) {
        $function = $widget_callback['value'];
        // Call ampcontentblock_widget_callback.
        $result[] = array('#markup' => $function());
      }

      break;
  }

  return $result;
}
