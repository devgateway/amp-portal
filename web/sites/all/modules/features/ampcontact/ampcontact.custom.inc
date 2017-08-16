<?php
/**
 * @file
 * ampcontact.custom.inc
 */

/**
 * An entity-bound allowed values callback.
 */
function ampcontact_organization_values_callback($field, $instance, $entity_type, $entity, &$cacheable) {
  $cacheable = FALSE;

  $organizations = variable_get('amp_contact_organizations', array());
  if (empty($organizations)) {
    return array();
  }

  $values = array();
  foreach ($organizations as $org) {
    $org = check_plain($org);
    $values[$org] = t($org);
  }

  return $values;
}

/**
 * Implements hook_form_alter().
 */
function ampcontact_form_contact_entityform_edit_form_alter(&$form, &$form_state) {
  $query = drupal_get_query_parameters();
  if (!empty($query) && in_array('subject', array_keys($query))) {
    $subject = $query['subject'];
    $form['field_contact_subject']['und'][0]['value']['#default_value'] = check_plain($subject);
  }
}
