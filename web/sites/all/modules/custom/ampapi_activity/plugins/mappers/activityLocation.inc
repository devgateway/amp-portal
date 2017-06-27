<?php
/**
 * @file
 * activityLocation plugin.
 */

$plugin = array(
  'title' => t('Location'),
  'description' => t(''),

  'property name' => 'location',
  'property info' => array(
    'type' => 'text',
  ),

  'report field group' => 'columns',
  'report field key' => 'Location',
  'report filter key' => 'location',

  'report filter endpoint' => 'filters/locations',

  'handler' => 'activityLocationMapper',
);

class activityLocationMapper extends activityMapperAutocompleteBase {
  public function filterData($info, $data, $parent_entry = NULL) {
    $location_level = $this->getExtraFilter('location_level', NULL);
    $location_field = $this->getExtraFilter('location_field', NULL);

    // Exit if no location level filtering is required.
    if ($location_level === NULL) {
      return $data;
    }
    foreach ($data as $entry) {
      if ($location_field !== NULL) {
        $location_field = urldecode($location_field);

        if ($entry->level != $location_level || ($parent_entry !== NULL && $parent_entry->name !== $location_field)) {
          $entry->filtered = TRUE;
        }
        elseif ($parent_entry !== NULL && $parent_entry->name == $location_field) {
          $entry->filtered = FALSE;
        }
      }
      else {
        if ($entry->level != $location_level) {
          $entry->filtered = TRUE;
        }
        else {
          $entry->filtered = FALSE;
        }
      }

      // Dive deeper.
      if (!empty($entry->children)) {
        $entry->children = $this->filterData($info, $entry->children, $entry);
      }
    }

    return $data;
  }
}
