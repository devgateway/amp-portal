<?php
/**
 * @file
 * secondarySector plugin.
 */

$plugin = array(
  'title' => t('Secondary Sector'),
  'description' => t(''),

  'property name' => 'secondary_sector',
  'property info' => array(
    'type' => 'text',
  ),

  'report field group' => 'columns',
  'report field key' => 'Secondary Sector',

  'report filter endpoint' => 'filters/sectors',
  'report filter name' => 'Secondary Sectors',

  'handler' => 'secondarySectorMapper',
);

class secondarySectorMapper extends activityMapperAutocompleteBase {
}
