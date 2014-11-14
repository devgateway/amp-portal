<?php

/**
 * @file
 * Shared classes and interfaces for the API mapper system.
 */

class activityMapperRoleAutocomplete extends activityMapperBase implements activityMapperAutocompleteInterface {
  public static function autocomplete($plugin, $string, $autocomplete = TRUE) {
    $matches = array();

    $role_id = self::_getRoleId($plugin);
    if (empty($role_id)) {
      return $matches;
    }

    $count = 0;
    $request_data = ampapi_request('get', $plugin['report filter endpoint']);
    foreach ($request_data as $entry) {
      if ($count >= 10) {
        break;
      }

      if (!in_array($role_id, $entry->rolesIds)) {
        continue;
      }

      if (stripos($entry->name, $string) === FALSE) {
        continue;
      }

      if ($autocomplete) {
        // $return_string = check_plain($entry->name) . ' (' . intval($entry->id) . ')';
        $return_string = check_plain($entry->name);
        $matches[$return_string] = $return_string;
      }
      else {
        $matches[] = clone $entry;
      }

      $count++;
    }

    return $matches;
  }

  public static function getAutocompleteValue($plugin, $string) {
    $matches = self::autocomplete($plugin, $string, FALSE);

    if (empty($matches)) {
      return NULL;
    }

    $entry = reset($matches);
    if (isset($entry->id)) {
      return array(intval($entry->id));
    }
  }

  // @TODO: Request ID from the API.
  public static function _getRoleId($plugin) {
    static $roles_data;

    if (!isset($roles_data)) {
      $roles_data = ampapi_request('get', $plugin['report filter endpoint extra']);
    }

    if (empty($roles_data)) {
      return FALSE;
    }

    // @HACK: Temporary!
    if ($plugin['report field key'] == 'Donor Agency') {
      $plugin['report field key'] = 'Donor'; // Yes, we have a consistent API.
    }

    foreach ($roles_data as $info) {
      if ($info->name == $plugin['report field key']) {
        return $info->id;
      }
    }
  }
}

/**
 * Autocomplete helper.
 */
class activityMapperSectorAutocomplete extends activityMapperBase implements activityMapperAutocompleteInterface {
  public static function autocomplete($plugin, $string, $autocomplete = TRUE) {
    $matches = array();

    $sector_id = self::_getSectorId($plugin);
    if (empty($sector_id)) {
      return $matches;
    }

    $request_data = ampapi_request('get', $plugin['report filter endpoint'] . '/' . $sector_id);
    if (empty($request_data->children)) {
      return $matches;
    }

    $count = 0;
    foreach ($request_data->children as $entry) {
      if ($count >= 10) {
        break;
      }

      $is_code = FALSE;
      // Match full codes and codes starting with the provided string.
      if (!$autocomplete && is_numeric($string) && $string == $entry->code) {
        $is_code = TRUE;
      }

      $is_matching = FALSE;
      if (stripos($entry->name, $string) !== FALSE) {
        $is_matching = TRUE;
      }

      if (!$is_matching && !$is_code) {
        continue;
      }

      if ($autocomplete) {
        // $return_string = check_plain($entry->name) . ' (' . intval($entry->id) . ')';
        $return_string = check_plain($entry->name);

        if ($autocomplete && $is_code) {
          $matches = array($return_string => $return_string) + $matches;
        }
        else {
          $matches[$return_string] = $return_string;
        }
      }
      else {
        $matches[] = clone $entry;
      }

      $count++;
    }

    return $matches;
  }

  // @TODO: Request ID from the API.
  public static function _getSectorId($plugin) {
    static $sectors_data;

    if (!isset($sectors_data)) {
      $sectors_data = ampapi_request('get', $plugin['report filter endpoint']);
    }

    if (empty($sectors_data)) {
      return FALSE;
    }

    foreach ($sectors_data as $info) {
      if ($info->name == $plugin['filter sector type']) {
        return $info->id;
      }
    }
  }

  public static function getAutocompleteValue($plugin, $string) {
    $matches = self::autocomplete($plugin, $string, FALSE);

    if (empty($matches)) {
      return NULL;
    }

    $entry = reset($matches);
    if (isset($entry->id)) {
      return array(intval($entry->id));
    }
  }

}
