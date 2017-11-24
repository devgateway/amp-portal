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

  'report filter endpoint' => 'filters/locationlist',
  'report filter key' => 'location',
  'report filter name' => 'Locations',

  'handler' => 'activityLocationMapper',
);

class activityLocationMapper extends activityMapperAutocompleteBase {
  public function getAutocompleteInfo($plugin, $data, $type) {
    $info = parent::getAutocompleteInfo($plugin, $data, $type);
    $filter_definition = $this->_getFilterByName($plugin);
    if (is_null($filter_definition)) {
      return NULL;
    }
    $info['filter_definition'] = $filter_definition;
    return $info;
  }

  public function filterData($info, $data, $parent_entry = NULL, $depth = 0) {
    $data = parent::filterData($info, $data);

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

        if ($depth !== $location_level || ($parent_entry !== NULL && $parent_entry->name !== $location_field)) {
          $entry->filtered = TRUE;
        }
        elseif ($parent_entry !== NULL && ($parent_entry->name == $location_field)) {
          $entry->filtered = FALSE;
        }
      }
      elseif($location_field_processed !== NULL) {
        // We don't really care about the filterId, as we're matching via location level.
        if (strpos($location_field_processed, ':') !== FALSE) {
          list($filter_id, $id) = explode(':', $location_field_processed);
          // OMG this appears to be needed.
          $id = intval($id);
        }
        else {
          $id = intval($location_field_processed);
        }


        if ($depth !== $location_level || ($parent_entry !== NULL && $parent_entry->id !== $id)) {
          $entry->filtered = TRUE;
        }
        elseif ($parent_entry !== NULL && ($parent_entry->id == $id)) {
          $entry->filtered = FALSE;
        }
      }
      else {
        if ($depth !== $location_level) {
          $entry->filtered = TRUE;
        }
        else {
          $entry->filtered = FALSE;
        }
      }

      // Dive deeper.
      if (!empty($entry->children)) {
        $entry->children = $this->filterData($info, $entry->children, $entry, $depth + 1);
      }
    }

    return $data;
  }

  /**
   * Helper function that gets the filter definition by its name.
   */
  private function _getFilterByName($plugin) {
    $endpoint = $plugin['report filter endpoint'];

    $data = ampAPIRestClient::get($endpoint);
    // Now all the metadata is stored in the listDefinitions.
    if (empty($data->listDefinitions)) {
      return FALSE;
    }

    // Setup the new and correct filterId value.
    $look_up_filter = (isset($plugin['report filter name'])) ? $plugin['report filter name'] : '';

    foreach ($data->listDefinitions as $metadata) {
      if (!empty($metadata->name) && $look_up_filter === $metadata->name) {
        return $metadata;
      }
    }

    return NULL;
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
