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

    // This is used on token-input, as it submits actually fully processed ID instead of string.
    $location_field_processed = $this->getExtraFilter('location_field_processed', NULL);

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
        elseif ($parent_entry !== NULL && ($parent_entry->name == $location_field)) {
          $entry->filtered = FALSE;
        }
      }
      elseif($location_field_processed !== NULL) {
        // We don't really care about the filterId, as we're matching via location level.
        list($filter_id, $id) = explode(':', $location_field_processed);
        // OMG this appears to be needed.
        $id = intval($id);

        if ($entry->level != $location_level || ($parent_entry !== NULL && $parent_entry->id !== $id)) {
          $entry->filtered = TRUE;
        }
        elseif ($parent_entry !== NULL && ($parent_entry->id == $id)) {
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

  public function getAutocompleteValue($plugin, $data, $type) {
    $matches = $this->autocomplete($plugin, $data, $type);
    if (empty($matches)) {
      return NULL;
    }
    // Special case for autocomplete powered view filters.
    // Not using the jQuery TokenInput library.
    if ($type == 'autocompleteids') {
      $entry = reset($matches);
      if (isset($entry['id'])) {
        return array($entry['id']);
      }
    }

    return $matches;
  }
}
