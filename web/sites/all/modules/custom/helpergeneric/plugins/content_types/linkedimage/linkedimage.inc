<?php

/**
 * @file
 * Plugin to handle the 'entity' content type which allows individual entities
 * to be embedded into a panel.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'category' => t('Custom'),
  'title' => t('Linked Image'),
  'description' => t('Add a linked image block.'),
  'defaults' => array(
    'variable_name' => '',
    'style' => 'normal',
  ),
);

/**
 * Output function for the 'entity' content type.
 *
 * Outputs a entity based on the module and delta supplied in the configuration.
 */
function helpergeneric_linkedimage_content_type_render($subtype, $conf, $panel_args) {
  $block = new stdClass();
  $block->module = 'linkedimage';
  $block->delta = $conf['variable_name'];

  // Get the settings.
  $widget_settings = variable_get($conf['variable_name'], array());
  if (empty($widget_settings) || !is_array($widget_settings)) {
    return;
  }

  if (empty($widget_settings['url']) || empty($widget_settings['image_fid'])) {
    return;
  }

  // Load the image file.
  $image_file = file_load($widget_settings['image_fid']);
  if (empty($image_file)) {
    return;
  }

  $block->content['#contextual_links'] = array(
    'helpergeneric' => array('admin/settings/static-content', array('map')),
  );

  if (!isset($block->css_class)) {
    $block->css_class = '';
  }

  // Set up preview file information.
  if (!empty($conf['style']) && $conf['style'] == 'wide') {
    $style = image_style_load('liwblock');
    $block->css_class .= ' linkedimage-wide';
  }
  else {
    $style = image_style_load('lisblock');
    $block->css_class .= ' linkedimage-normal';
  }

  $preview_file = image_style_path($style['name'], $image_file->uri);
  if (!file_exists($preview_file)) {
    image_style_create_derivative($style, $image_file->uri, $preview_file);
  }

  // Set the title.
  $svgicon = helpertheme_get_svg_icons('maps', array('width' => '2em', 'height' => '2em'));
  $block->title = $svgicon . t('Explore the Map');
  $block->title_is_xss_free = TRUE;
  $block->title_link = array(
    'href' => $widget_settings['url'],
    'external' => TRUE,
    'html' => TRUE,
  );

  $block->content['image'] = array(
    '#theme' => 'link',
    '#path' => $widget_settings['url'],
    '#text' => theme('image', array('path' => $preview_file)),
    '#options' => array(
      'external' => TRUE,
      'html' => TRUE,
      'attributes' => array(
      ),
    ),
  );

  // Add separator class.
  $block->css_class .= ' layout-separator';

  return $block;
}

/**
 * The form to add or edit a entity as content.
 */
function helpergeneric_linkedimage_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['variable_name'] = array(
    '#title' => t('Variable Name'),
    '#description' => t('The variable containing the ID of the referenced content.'),
    '#type' => 'textfield',
    '#default_value' => $conf['variable_name'],
    '#required' => TRUE,
    '#maxlength' => 128,
    '#prefix' => '<div class="no-float">',
    '#suffix' => '</div>',
  );

  $form['style'] = array(
    '#type' => 'radios',
    '#title' => t('Style'),
    '#default_value' => $conf['style'],
    '#options' => array(
      'normal' => 'Normal',
      'wide' => 'Wide',
    ),
  );

  return $form;
}

/**
 * Validate the entity selection.
 */
function helpergeneric_linkedimage_content_type_edit_form_validate(&$form, &$form_state) {
  if ($form_state['op'] != 'add') {
    return;
  }

  $variable_name = $form_state['values']['variable_name'];
  $widget_settings = variable_get($variable_name, NULL);

  if (empty($widget_settings)) {
    return;
  }
}

/**
 * Validate the entity selection.
 */
function helpergeneric_linkedimage_content_type_edit_form_submit($form, &$form_state) {
  foreach (array('variable_name', 'style') as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/**
 * Returns the administrative title for a entity.
 */
function helpergeneric_linkedimage_content_type_admin_title($subtype, $conf) {
  $variable_name = $conf['variable_name'];
  return t('Linked Image: %variable_name', array('%variable_name' => $variable_name));
}

/**
 * Display the administrative information for a entity pane.
 */
function helpergeneric_linkedimage_content_type_admin_info($subtype, $conf) {
  $variable_name = $conf['variable_name'];

  $variable_name = variable_get($variable_name, NULL);
  if (!isset($variable_name)) {
    return t('Variable @var does not exist.', array('@var' => $variable_name));
  }

  return $variable_name;
}
