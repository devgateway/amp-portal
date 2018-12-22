<?php
/**
 * @file
 * activityStatus plugin.
 */

$plugin = array(
  'title' => t('Status'),
  'description' => t(''),

  'property name' => 'status',
  'property info' => array(
    'type' => 'integer',
    'options list' => array('activityStatusMapper', 'optionsList'),
  ),

  'report field group' => 'columns',
  'report field key' => 'Status',

  'report filter endpoint' => 'nifilters/activityStatus',
  'report filter name' => 'Status',

  'handler' => 'activityStatusMapper',
);

class activityStatusMapper extends activityMapperBase {
  public static function optionsList($plugin) {
    // Small sanity check.
    if (!is_array($plugin)) {
      $plugin = ampapi_get_mapper('activityStatus');
    }

    $filter_details = FALSE;
    $response_filter_data = ampAPIRestClient::get($plugin['report filter endpoint']);
    foreach ($response_filter_data->listDefinitions as $listDefinition) {
      if ($listDefinition->name == $plugin['report filter name']) {
        $filter_details = $listDefinition;
      }
    }
    $response_data = $response_filter_data->items->{$filter_details->items};

    if (empty($response_data)) {
      return array();
    }

    $options = array();
    /** @noinspection PhpUndefinedFieldInspection */
    foreach ($response_data as $value) {
      $options[intval($value->id)] = filter_xss_admin($value->name);
    }

    return $options;
  }

  public static function filter($plugin, &$api_parameters, &$request_body, $condition) {
    // API requires integers, not strings.
    if (is_array($condition['value'])) {
      foreach ($condition['value'] as $key => &$value) {
        $value = intval($value);
      }
    }
    else {
      // Case of a string.
      $condition['value'] = array($condition['value']);
    }

    parent::filter($plugin, $api_parameters, $request_body, $condition);
  }
}
