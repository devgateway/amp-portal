<?php
/**
 * @file
 * donorAgency plugin.
 */

$plugin = array(
  'title' => t('Donor Agency'),
  'description' => t(''),

  'property name' => 'donor_agency',
  'property info' => array(
    'type' => 'text',
  ),

  'report field group' => 'columns',
  'report field key' => 'Donor Agency',
  // 'report filter key' => 'Donor Agency Id',
  'report filter key' => 'Donor Id',

  'handler' => 'donorAgencyMapper',
);

class donorAgencyMapper extends activityMapperBase {
  /**
   * Filter handler.
   */
  public static function filter($plugin, &$api_parameters, &$request_body, $condition) {
    $condition['value'] = array(intval($condition['value']));
    $condition['operator'] = 'IN';
    parent::filter($plugin, $api_parameters, $request_body, $condition);
  }
}
