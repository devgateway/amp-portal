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
  return drupal_build_form($form_id, $form_state);
}
