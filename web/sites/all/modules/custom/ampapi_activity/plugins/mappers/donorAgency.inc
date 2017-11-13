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

  'report filter endpoint' => 'filters/organizations',
  'report filter key' => 'donor-agency',

  'handler' => 'donorAgencyMapper',
);

class donorAgencyMapper extends activityMapperSubFilterAutocomplete {
}
