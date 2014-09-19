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
  'title' => t('CB Reference'),
  'single' => TRUE,
  'defaults' => array(
    'variable_name' => '',
    // 'links' => FALSE,
    // 'remove_title' => FALSE,
    // 'linked_title' => FALSE,
    'identifier' => '',
    'build_mode' => 'default',
  ),
  'icon' => 'icon.png',
  'description' => t('Add a entity from your site as content stored in a variable.'),
  'category' => t('Custom'),
  'top level' => TRUE,
  'js' => array('misc/autocomplete.js'),
);

/**
 * Output function for the 'entity' content type.
 *
 * Outputs a entity based on the module and delta supplied in the configuration.
 */
function contentblock_cbreference_content_type_render($subtype, $conf, $panel_args) {
  $block = new stdClass();

  // Get the referenced entity id.
  $entity_id = variable_get($conf['variable_name'], NULL);

  $language = NULL;
  // Support translations.
  // if (module_exists('translation')) {
  //   if ($translations = module_invoke('translation', 'entity_get_translations', $entity_id)) {
  //     if (isset($translations[$GLOBALS['language']->language]))  {
  //       $entity_id = $translations[$GLOBALS['language']->language]->entity_id;
  //     }
  //   }
  // }

  if (!is_numeric($entity_id)) {
    return;
  }

  $entity = entity_load_single('contentblock', $entity_id);
  if (!entity_access('view', 'contentblock', $entity)) {
    return;
  }

  // We need to alter the entity content.
  $entity = clone($entity);

  $block->module = 'contentblock';
  $block->delta = $entity->identifier();

  // Set block->title to the plain entity title, then additionally set block->title_link to
  // the entity url if required. The actual link is rendered in ctools_content_render().
  $block->title = check_plain($entity->label());

  $remove_title = FALSE;
  // if (!empty($conf['remove_title'])) {
  //   $remove_title = TRUE;
  // }

  // if (empty($conf['remove_title']) && !empty($conf['linked_title'])) {
  //   $entity_uri = $entity->uri();
  //   $block->title_link = $entity_uri['path'];
  // }

  if (!empty($conf['identifier'])) {
    $entity->ctools_template_identifier = $conf['identifier'];
  }

  // Handle existing configurations with the deprecated 'teaser' option.
  if (isset($conf['teaser'])) {
    $conf['build_mode'] = $conf['teaser'] ? 'teaser' : 'full';
  }

  $block->content = $entity->view($conf['build_mode'], $language, $remove_title);

  // Hide links if they've been suppressed.
  // if (!empty($conf['links'])) {
  //   $block->content['links']['#access'] = FALSE;
  // }

  return $block;
}

/**
 * The form to add or edit a entity as content.
 */
function contentblock_cbreference_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  // $form['remove_title'] = array(
  //   '#type' => 'checkbox',
  //   '#default_value' => !empty($conf['remove_title']),
  //   '#title' => t('Remove entity title'),
  // );

  // $form['linked_title'] = array(
  //   '#type' => 'checkbox',
  //   '#default_value' => !empty($conf['linked_title']),
  //   '#title' => t('Link the entity title to the entity'),
  //   '#description' => t('Check this box if you would like your pane title to link to the entity.'),
  // );

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

  // $form['links'] = array(
  //   '#type' => 'checkbox',
  //   '#default_value' => $conf['links'],
  //   '#title' => t('Include entity links for "add comment", "read more" etc.'),
  // );

  $form['identifier'] = array(
    '#type' => 'textfield',
    '#default_value' => !empty($conf['identifier']) ? $conf['identifier'] : '',
    '#title' => t('Template identifier'),
    '#description' => t('This identifier will be added as a template suggestion to display this entity: entity--panel--IDENTIFIER.tpl.php. Please see the Drupal theming guide for information about template suggestions.'),
  );

  $entity = entity_get_info('contentblock');
  $build_mode_options = array('default' => t('Default'));
  foreach ($entity['view modes'] as $mode => $option) {
    $build_mode_options[$mode] = t($option['label']);
  }

  // Handle existing configurations with the deprecated 'teaser' option.
  // Also remove the teaser key from the form_state.
  if (isset($conf['teaser']) || !isset($conf['build_mode'])) {
    unset($form_state['conf']['teaser']);
    $conf['build_mode'] = $conf['teaser'] ? 'teaser' : 'full';
  }
  $form['build_mode'] = array(
    '#title' => t('Build mode'),
    '#type' => 'select',
    '#description' => t('Select a build mode for this entity.'),
    '#options' => $build_mode_options,
    '#default_value' => $conf['build_mode'],
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
  $entity_id = variable_get($variable_name, NULL);

  if (empty($entity_id)) {
    return;
  }

  // $entity = entity_load_single('contentblock', $entity_id);
  // if (empty($entity)) {
  //   form_error($form['variable_name'], t('Invalid variable, it does not contain a valid entity ID.'));
  // }
}

/**
 * Validate the entity selection.
 */
function contentblock_cbreference_content_type_edit_form_submit($form, &$form_state) {
  foreach (array('variable_name', 'links', 'remove_title', 'linked_title', 'identifier', 'build_mode') as $key) {
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

  $entity_id = variable_get($variable_name, NULL);
  if (!is_numeric($entity_id) || 1) {
    return t('Variable @var does not contain a valid contentblock id.', array('@var' => $variable_name));
  }

  $entity = entity_load_single('contentblock', $entity_id);
  if (empty($entity)) {
    return t('Refereneced contentblock %entity_id does not exist.', array('%entity_id' => $entity_id));
  }

  // Just return the entity label.
  return $entity->label();
}
