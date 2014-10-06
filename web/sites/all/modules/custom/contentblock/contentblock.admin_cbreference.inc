<?php
/**
 * @file
 * Forms and helper functions for administrative pages.
 */

module_load_include('inc', 'contentblock', 'contentblock.admin');

/**
 * Page callback for 'admin/settings/content-sections/*'.
 */
function contentblock_cbreference_entity_form($machine_name = NULL) {
  $entity_type = 'contentblock';
  $entities = entity_load($entity_type, array(), array('machine_name' => $machine_name));
  $entity = reset($entities);

  // Make sure we do the proper action.
  $op = 'edit';
  if (empty($entity)) {
    $op = 'add';
    $default_values = array(
      'type' => 'hidden',
      'machine_name' => $machine_name,
    );
    $entity = entity_create($entity_type, $default_values);
  }
  else {
    list(, , $bundle) = entity_extract_ids($entity_type, $entity);
  }

  // Determine which form to use.
  $form_id = (!isset($bundle) || $bundle == $entity_type) ? $entity_type . '_form' : $entity_type . '_edit_' . $bundle . '_form';

  // Do not use drupal_get_form(), but invoke drupal_build_form() ourself so
  // we can prepulate the form state.
  $form_state['wrapper_callback'] = 'entity_ui_main_form_defaults';
  $form_state['entity_type'] = $entity_type;
  form_load_include($form_state, 'inc', 'entity', 'includes/entity.ui');

  // We don't pass the entity type as first parameter, as the implementing
  // module knows the type anyway. However, in order to allow for efficient
  // hook_forms() implementiations we append the entity type as last argument,
  // which the module implementing the form constructor may safely ignore.
  // @see entity_forms()
  $form_state['build_info']['args'] = array($entity, $op, $entity_type);

  // We need to be able to update the title after building the form.
  $form = drupal_build_form($form_id, $form_state);

  // Get the predefined name.
  $cbreference_info = contentblock_get_hidden_types($entity->machine_name);
  drupal_set_title($cbreference_info['title']);

  // Add a default title value for sections.
  if (!empty($cbreference_info['is section'])) {
    $langcode = isset($entity->language) ? $entity->language : LANGUAGE_NONE;
    $title_element = &$form['title_field'][$langcode][0];
    if (empty($title_element['value']['#value'])) {
      $title_element['value']['#value'] = $cbreference_info['title'];
    }
  }

  // Hide the default title element.
  if (!in_array('title_field', $cbreference_info['available_fields'])) {
    $form['title_field']['#attributes']['class'][] = 'element-hidden';
  }

  // Add a description on add form.
  if ($op == 'add' && !empty($_GET['destination'])) {
    $form['form_description'] = array(
      '#markup' => t('If you only want to remove the instructions from this section you can just click "Save" without adding/configuring any content.'),
      '#prefix' => '<div class="description">',
      '#suffix' => '</div>',
      '#weight' => 101,
    );
  }

  return $form;
}

/**
 * Implements hook_form_FORM_ID_alter() for contentblock_form().
 */
function _contentblock_form_contentblock_form_alter(&$form, &$form_state, $form_id) {
  foreach (contentblock_get_hidden_types() as $machine_name => $info) {
    if ($form['#entity']->machine_name != $machine_name) {
      continue;
    }

    foreach (element_children($form) as $element_child) {
      if (substr($element_child, 0, 6) !== 'field_') {
        continue;
      }

      if (!in_array($element_child, $info['available_fields'])) {
        $form[$element_child]['#access'] = FALSE;
      }
    }
  }

  // Attach validate callbacks.
  switch ($form['#entity']->machine_name) {
    case 'linkedmap':
      $form['#validate'][] = '_contentblock_cbreference_entity_form_linkedmap_validate';
      break;
    case 'footer':
      $form['#validate'][] = '_contentblock_cbreference_entity_form_footer_validate';
      break;
    case 'welcome':
      $form['#validate'][] = '_contentblock_cbreference_entity_form_welcome_validate';
      break;
  }
}

/**
 * Form validation handler for contentblock_cbreference_entity_form() for linkedmap.
 */
function _contentblock_cbreference_entity_form_linkedmap_validate($form, &$form_state) {
  $entity_type = $form_state['entity_type'];
  $entity = $form_state[$entity_type];
  $langcode = isset($entity->language) ? $entity->language : LANGUAGE_NONE;

  if (!empty($form_state['values']['field_cblinks'][$langcode][0]['url']) && empty($form_state['values']['field_cbimage'][$langcode][0]['fid'])) {
    form_set_error('field_cbimage', t('Field %name is required.', array('%name' => $form['field_cbimage'][$langcode][0]['#title'])));
  }

  if (!empty($form_state['values']['field_cbimage'][$langcode][0]['fid']) && empty($form_state['values']['field_cblinks'][$langcode][0]['url'])) {
    form_set_error('field_cblinks', t('Field %name is required.', array('%name' => $form['field_cblinks'][$langcode][0]['#title'])));
  }
}

/**
 * Form validation handler for contentblock_cbreference_entity_form() for welcome.
 */
function _contentblock_cbreference_entity_form_welcome_validate($form, &$form_state) {
  $entity_type = $form_state['entity_type'];
  $entity = $form_state[$entity_type];
  $langcode = isset($entity->language) ? $entity->language : LANGUAGE_NONE;

  if (!empty($form_state['values']['field_cbbody'][$langcode][0]['value'])) {
    $max_char_count = 640; // @TODO: reduce to 320 and count using strip_tags
    $body_char_count = drupal_strlen(strip_tags($form_state['values']['field_cbbody'][$langcode][0]['value']));
    if ($body_char_count > $max_char_count) {
      form_set_error('field_cbbody', t('Field %name should not have more than %max characters, %count given.', array('%name' => $form['field_cbbody'][$langcode][0]['#title'], '%max' => $max_char_count, '%count' => $body_char_count)));
    }
  }
}

/**
 * Form validation handler for contentblock_cbreference_entity_form() for footer.
 */
function _contentblock_cbreference_entity_form_footer_validate($form, &$form_state) {
  $entity_type = $form_state['entity_type'];
  $entity = $form_state[$entity_type];
  $langcode = isset($entity->language) ? $entity->language : LANGUAGE_NONE;

  if (!empty($form_state['values']['field_cbbody'][$langcode][0]['value'])) {
    $max_char_count = 640;
    $body_char_count = drupal_strlen($form_state['values']['field_cbbody'][$langcode][0]['value']);
    if ($body_char_count > $max_char_count) {
      form_set_error('field_cbbody', t('Field %name should not have more than %max characters, %count given.', array('%name' => $form['field_cbbody'][$langcode][0]['#title'], '%max' => $max_char_count, '%count' => $body_char_count)));
    }
  }
}
