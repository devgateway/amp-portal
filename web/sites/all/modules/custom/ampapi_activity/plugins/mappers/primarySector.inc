<?php
/**
 * @file
 * primarySector plugin.
 */

$plugin = array(
  'title' => t('Primary Sector'),
  'description' => t(''),

  'property name' => 'primary_sector',
  'property info' => array(
    'type' => 'text',
  ),

  'report field group' => 'columns',
  'report field key' => 'Primary Sector',

  'report filter endpoint' => 'nifilters/sectors',
  'report filter name' => 'Primary Sectors',

  'handler' => 'primarySectorMapper',
);

class primarySectorMapper extends activityMapperAutocompleteBase {

}
