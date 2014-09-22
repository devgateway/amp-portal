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
  'title' => t('CB Reference'),
  'description' => t('Add a entity from your site as content stored in a variable.'),
  'icon' => 'icon.png',
  'single' => TRUE,
  'defaults' => array(
    'variable_name' => '',
    'template' => '',
  ),
  'top level' => TRUE,
);

/**
 * Output function for the 'entity' content type.
 *
 * Outputs a entity based on the module and delta supplied in the configuration.
 */
function contentblock_cbreference_content_type_render($subtype, $conf, $panel_args) {
  $block = new stdClass();
  $block->module = 'contentblock';
  $block->delta = $conf['variable_name'];

  // Get the settings.
  $contentblocks = variable_get($conf['variable_name'], NULL);
  if (empty($contentblocks) || !is_array($contentblocks)) {
    return;
  }

  foreach ($contentblocks as $info) {
    if (empty($info['contentblock']) || !is_numeric($info['contentblock'])) {
      continue;
    }

    $entity = entity_load_single('contentblock', $info['contentblock']);
    if (!entity_access('view', 'contentblock', $entity)) {
      continue;
    }

    if (!empty($conf['template'])) {
      $entity->ctools_template_identifier = $conf['template'];
    }

    $view_mode = 'default';
    if (!empty($info['view_mode'])) {
      $view_mode = $info['view_mode'];
    }

    // @TODO: Add language support.
    $language = NULL;

    $block->content[] = $entity->view($view_mode, $language);
  }

  return $block;
}

/**
 * The form to add or edit a entity as content.
 */
function contentblock_cbreference_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['variable_name'] = array(
    '#title' => t('Variable Name'),
    '#description' => t('The variable containing the ID of the referenced content.'),
    '#type' => 'textfield',
    '#default_value' => $conf['variable_name'],
    '#maxlength' => 512,
    '#prefix' => '<div class="no-float">',
    '#suffix' => '</div>',
    '#weight' => -10,
  );

  $form['template'] = array(
    '#type' => 'textfield',
    '#default_value' => !empty($conf['template']) ? $conf['template'] : '',
    '#title' => t('Template identifier'),
    '#description' => t('This identifier will be added as a template suggestion to display this entity: entity--panel--IDENTIFIER.tpl.php. Please see the Drupal theming guide for information about template suggestions.'),
  );

  return $form;
}

/**
 * Validate the entity selection.
 */
function contentblock_cbreference_content_type_edit_form_validate(&$form, &$form_state) {
  if ($form_state['op'] != 'add') {
    return;
  }

  $variable_name = $form_state['values']['variable_name'];
  $contentblocks = variable_get($variable_name, NULL);

  if (empty($contentblocks)) {
    return;
  }
}

/**
 * Validate the entity selection.
 */
function contentblock_cbreference_content_type_edit_form_submit($form, &$form_state) {
  foreach (array('variable_name', 'template') as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/**
 * Returns the administrative title for a entity.
 */
function contentblock_cbreference_content_type_admin_title($subtype, $conf) {
  $variable_name = $conf['variable_name'];
  return t('Block Reference: %variable_name', array('%variable_name' => $variable_name));
}

/**
 * Display the administrative information for a entity pane.
 */
function contentblock_cbreference_content_type_admin_info($subtype, $conf) {
  $variable_name = $conf['variable_name'];

  $variable_name = variable_get($variable_name, NULL);
  if (!isset($variable_name)) {
    return t('Variable @var does not exist.', array('@var' => $variable_name));
  }

  return $variable_name;
}
