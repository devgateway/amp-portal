<?php

/**
 * Menu callback; Retrieve a JSON object containing autocomplete suggestions for existing surveys.
 */
function ampapi_activity_autocomplete($property_name, $string = '') {
  $matches = array();

  $plugin = ampapi_get_mapper_by_property_name($property_name);

  // @HACK: Temporary!
  if ($plugin['report field key'] == 'Donor Agency') {
    $plugin['report field key'] = 'Donor'; // Yes, we have a consistent API.
  }

  if (empty($plugin['report filter endpoint'])) {
    drupal_json_output($matches);
  }

  $class_name = ctools_plugin_get_class($plugin, 'handler');
  if (empty($class_name) || !in_array('activityMapperAutocompleteInterface', class_implements($class_name))) {
    drupal_json_output($matches);
  }

  if ($string) {
    $matches += $class_name::autocomplete($plugin, $string);
  }

  drupal_json_output($matches);
}
