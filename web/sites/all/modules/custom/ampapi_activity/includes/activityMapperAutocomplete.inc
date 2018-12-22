<?php

/**
 * @file
 * Shared classes and interfaces for the API mapper system.
 */

class activityMapperAutocompleteBase extends activityMapperBase implements activityMapperAutocompleteInterface {
  private $extra_filters = array();

  public function autocomplete($plugin, $data, $type = 'autocomplete') {
    $info = $this->getAutocompleteInfo($plugin, $data, $type);
    if (empty($info)) {
      return array();
    }

    $returned_filter = FALSE;

    // Get the filter data, which contains filter definition(s) and filter data.
    $returned_filter_data = ampAPIRestClient::get($info['endpoint']);
    if (empty($returned_filter_data)) {
      return array();
    }
    else {
      foreach ($returned_filter_data->listDefinitions as $delta => $filter_definition) {
        if ($filter_definition->name == $plugin['report filter name']) {
          $returned_filter = $filter_definition;
        }
      }
    }

    // Because we switched to nifilters we will figure out the data ourselves.
    $returned_data = $returned_filter_data->items->{$returned_filter->items};
    $info['filter details'] = $returned_filter;

    // Offer subclasses a possibility to filter-out the returned data.
    $returned_data = $this->filterData($info, $returned_data);
    return $this->getMatchedValues($info, $returned_data);
  }

  public function getAutocompleteInfo($plugin, $data, $type) {
    $info = array();

    if (in_array($type, array('autocomplete', 'tokeninput'))) {
      $info['string'] = reset($data);
    }
    else {
      $info['values'] = $data;
    }

    $info['plugin'] = $plugin;
    $info['type'] = $type;
    $info['endpoint'] = $plugin['report filter endpoint'];

    return $info;
  }

  public function getMatchedValues(array $info, array $entries, $level = 0) {
    global $language;
    $matches = array();

    $search_string = '';
    if (in_array($info['type'], array('autocomplete', 'tokeninput'))) {
      $search_string = transliteration_get($info['string'], '', $language->language);
    }
    foreach ($entries as $entry) {
      if (count($matches) >= 10) {
        break;
      }

      // Because $entry->filterId is missing now, we can grab it from $info.
      if (!empty($info['filter details'])) {
        $filter_id = $info['filter details']->filterIds[$level];
        $entry->filterId = $filter_id;
      }

      // Match full codes and codes starting with the provided string.
      if (!$this->_valueMatches($info, $entry, $search_string)) {
        continue;
      }

      // Include all parent items in name, if any.
      $name = '';
      if (strpos($info['plugin']['report filter endpoint'], 'nifilters') !== FALSE) {
        if (isset($info['parents'])) {
          foreach ($info['parents'] as $parent) {
            $name .= filter_xss_admin($parent->name) . ' > ';
          }
        }
        $id = $entry->filterId . ':' . intval($entry->id);
      }
      else {
        $id = intval($entry->id);
      }

      // Include acronym in name, if any.
      $name .= filter_xss_admin($entry->name);
      if (isset($entry->acronym)) {
        $name .= ' (' . filter_xss_admin($entry->acronym) . ')';
      }

      // This filtered property is set in cases we want to filter-out some values in filterData().
      if (!isset($entry->filtered) || $entry->filtered === FALSE) {
        $new_value = array(
          'id' => $id,
          'name' => $name,
        );

        $matches[] = $new_value;
      }
    }

    // Search sub-levels, if any.
    foreach ($entries as $entry) {
      if (count($matches) >= 10) {
        break;
      }

      if (!empty($entry->children)) {
        // We need to change the info only for the current children.
        $temp_info = $info;
        if ($level == 0) {
          $entry->top_level = TRUE;
        }
        $temp_info['parents'][] = $entry;
        $matches = array_merge($matches, $this->getMatchedValues($temp_info, $entry->children, $level + 1));
      }
    }

    return $matches;
  }

  /**
   * Public function that filters out the data according the certain values in $info.
   *
   * @param array $info
   *   Info array.
   * @param  array $data
   *   Array of data that needs to be filtered.
   * @return array
   *   Filtered data.
   */
  public function filterData($info, $data) {
    return $data;
  }

  /**
   * Test if the entry object show be included in the returned values or not.
   */
  private function _valueMatches(array $info, $entry, $search_string) {
    global $language;

    switch ($info['type']) {
      case 'tokeninput':
      case 'autocomplete':
        $matches = FALSE;

        $entry_name = transliteration_get($entry->name, '', $language->language);
        if (stripos($entry_name, $search_string) !== FALSE) {
          $matches = TRUE;
        }

        if ($info['plugin']['report filter endpoint'] == 'filters/orgs') {
          if (isset($entry->acronym) && stripos($entry->acronym, $search_string) !== FALSE) {
            $matches = TRUE;
          }
        }

        // Filter out donors without funding.
        // if ($info['plugin']['property name'] == 'donor_agency') {
        //   if (empty($entry->hasFundings)) {
        //     $matches = FALSE;
        //   }
        // }

        if ($matches) {
          return TRUE;
        }
        break;
      case 'autocompleteids':
        if ($info['plugin']['property name'] == 'location') {
          $name = '';
          if (isset($info['parents'])) {
            foreach ($info['parents'] as $parent) {
              if (empty($parent->top_level)) {
                $name .= filter_xss_admin($parent->name) . ' > ';
              }
            }
            $name .= filter_xss_admin($entry->name);
          }
          else {
            $name = filter_xss_admin($entry->name);
          }
          if (in_array($name, $info['values'])) {
            return TRUE;
          }
        }
        else if ($entry->name == $search_string) {
          return TRUE;
        }
        break;

      case 'tokeninputids':
        $id = $entry->id;

        // Slight adjustment for locations.
        if (strpos($info['plugin']['report filter endpoint'], 'nifilters') !== FALSE) {
          $id = $entry->filterId . ':' . intval($entry->id);
        }


        if (in_array($id, $info['values'])) {
          return TRUE;
        }
        break;
    }

    return FALSE;
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
        return array(intval($entry['id']));
      }
    }

    return $matches;
  }

  /**
   * Sets a value to the specified key (for extra filtering).
   */
  public function setExtraFilter($key, $value) {
    $this->extra_filters[$key] = $value;
  }

  /**
   * Gets the value for the key. If none exists, uses default one.
   */
  public function getExtraFilter($key, $default_value) {
    if (!empty($this->extra_filters[$key])) {
      return $this->extra_filters[$key];
    }
    return $default_value;
  }
}
