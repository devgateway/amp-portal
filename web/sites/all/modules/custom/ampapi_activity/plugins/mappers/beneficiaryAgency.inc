<?php
/**
 * @file
 * beneficiaryAgency plugin.
 */

$plugin = array(
  'title' => t('Beneficiary Agency'),
  'description' => t(''),

  'property name' => 'beneficiary_agency',
  'property info' => array(
    'type' => 'text',
  ),

  'report field group' => 'columns',
  'report field key' => 'Beneficiary Agency',

  'report filter endpoint' => 'filters/organizations',
  'report filter name' => 'Beneficiary Agency',

  'handler' => 'beneficiaryAgencyMapper',
);

class beneficiaryAgencyMapper extends activityMapperAutocompleteBase {
}
