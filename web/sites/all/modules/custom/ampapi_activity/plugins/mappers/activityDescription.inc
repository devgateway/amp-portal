<?php
/**
 * @file
 * activityDescription plugin.
 */

$plugin = array(
  'title' => t('Description'),
  'description' => t(''),

  'property name' => 'description',
  'property info' => array(
    'type' => 'text',
  ),

  'report field group' => 'columns',
  'report field key' => 'Project Description',
  'report filter key' => 'keyword',

  'handler' => 'activityDescriptionMapper',
);

class activityDescriptionMapper extends activityMapperBase {
  /**
   * Filter handler.
   */
  public static function filter($plugin, &$api_parameters, &$request_body, $condition) {
    // The filter for this field is not a normal filter.
    $plugin['report field group'] = 'others';
    parent::filter($plugin, $api_parameters, $request_body, $condition);
  }
}
