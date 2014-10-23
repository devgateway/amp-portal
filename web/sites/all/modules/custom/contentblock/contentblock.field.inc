<?php
/**
 * @file
 * Exposes custom field, field widget and field formatter.
 */

/**
 * Implements hook_field_info().
 */
function contentblock_field_info() {
  return array(
    'contentblock_widget' => array(
      'label' => t('ContentBlock Widget'),
      'description' => t('Can be used for...'),
      'settings' => array(),
      'default_widget' => 'widgets_select',
      'default_formatter' => 'rendered_widget',
    ),
  );
}

/**
 * Implements hook_field_widget_info().
 */
function contentblock_field_widget_info() {
  return array(
    // @TODO: Disable multiple values,
    'widgets_settings' => array(
      'label' => t('Widget Settings Form'),
      'field types' => array('contentblock_widget'),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_CUSTOM,
        'default value' => FIELD_BEHAVIOR_NONE,
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_info().
 */
function contentblock_field_formatter_info() {
  return array(
    'rendered_widget' => array(
      'label' => t('Rendered Widget'),
      'description' => t('Display the rendered widget content.'),
      'field types' => array('contentblock_widget'),
    ),
  );
}

/**
 * Implements hook_field_settings_form().
 */
function contentblock_field_settings_form($field, $instance, $has_data) {
  $settings = $field['settings'];
  $element = array();
  return $element;
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function contentblock_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $element = array();
  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function contentblock_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $summary = array();
  return implode('<br />', $summary);
}

/**
 * Implements hook_field_widget_settings_form().
 */
function contentblock_field_widget_settings_form($field, $instance) {
  $element = array();
  return $element;
}

/**
 * Implements hook_field_formatter_view().
 */
function contentblock_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $result = array();

  $settings = $display['settings'];

  switch ($display['type']) {
    case 'rendered_widget':
      $widget_info = array_shift($items);
      $widget_name = isset($widget_info['widget']) ? $widget_info['widget'] : NULL;
      $widget_settings = isset($widget_info['settings']) ? unserialize($widget_info['settings']) : array();

      $plugin = contentblock_get_predefined_widget($widget_name);
      if ($function = ctools_plugin_get_function($plugin, 'render callback')) {
        // Because of entity_translation, the provided $langcode is the original entity language.
        $entity_langcode = entity_translation_get_existing_language($entity_type, $entity);
        $result[] = $function($widget_settings, $entity, $entity_langcode);
      }
      break;
  }

  return $result;
}

/**
 * Implements hook_field_widget_form().
 */
function contentblock_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  $selected_widget = isset($items[0]['widget']) ? $items[0]['widget'] : NULL;
  $selected_widget_settings = !empty($items[0]['settings']) ? unserialize($items[0]['settings']) : array();

  $entity_type = $element['#entity_type'];
  $entity = $element['#entity'];

  // Prepare the list of widget options.
  $options = array();
  foreach (contentblock_get_predefined_widgets() as $key => $info) {
    $options[$key] = $info['title'];
  }

  $element['widget'] = array(
    '#title' => $element['#title'],
    '#type' => 'radios',
    '#default_value' => $selected_widget,
    '#required' => $element['#required'],
    '#options' => $options,
  );

  $element['settings'] = array();
  foreach ($options as $widget_name => $value) {
    $plugin = contentblock_get_predefined_widget($widget_name);
    if ($function = ctools_plugin_get_function($plugin, 'settings form')) {
      $input_name = "{$element['#field_name']}[{$element['#language']}][widget]";

      $element['settings'][$widget_name] = array(
        '#type' => 'fieldset',
        '#title' => t('Widget Settings'),
        '#description' => t('Settings for the %name widget.', array('%name' => $plugin['title'])),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
        '#states' => array(
          'visible' => array(
            ":input[name=\"{$input_name}\"]" => array('value' => $widget_name),
          ),
        ),
      );

      // Get the widget settings form.
      if ($widget_name == $selected_widget) {
        $widget_settings = $selected_widget_settings + $plugin['defaults'];
      }
      else {
        $widget_settings = $plugin['defaults'];
      }
      $widget_settings_form = $function($element, $form_state, $plugin, $widget_settings);

      if (!empty($widget_settings_form)) {
        $element['settings'][$widget_name] += $widget_settings_form;
      }
      else {
        $element['settings'][$widget_name]['#description'] = t('Widget %name has no settings.', array('%name' => $plugin['title']));
      }
    }
  }

  $element['#element_validate'] = array('contentblock_field_widget_validate');

  return $element;
}

/**
 * Implements hook_field_is_empty().
 */
function contentblock_field_is_empty($item, $field) {
  if (empty($item['widget'])) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Form element validation handler for options element.
 */
function contentblock_field_widget_validate($element, &$form_state) {
  $values = array();
  if (isset($form_state['values'][$element['#field_name']][$element['#language']])) {
    $values = &$form_state['values'][$element['#field_name']][$element['#language']];
  }

  // Clear all cache.
  cache_clear_all();

  // Prepare the data for storage.
  $data = _contentblock_widget_settings_form_to_storage($values);
  form_set_value($element, $data, $form_state);
}

/**
 * Transforms submitted form values into field storage format.
 */
function _contentblock_widget_settings_form_to_storage($values) {
  $data = array(
    'widget' => $values['widget'],
    'settings' => NULL,
  );

  $plugin = contentblock_get_predefined_widget($values['widget']);
  if ($function = ctools_plugin_get_function($plugin, 'settings storage')) {
    $data['settings'] = $function($values['widget'], $values['settings']);
  }

  return array(0 => $data);
}
