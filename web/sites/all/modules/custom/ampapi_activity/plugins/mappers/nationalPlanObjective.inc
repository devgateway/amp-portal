<?php
/**
 * @file
 * nationalPlanObjective plugin.
 */

$plugin = array(
  'title' => t('National Plan Objective'),
  'description' => t(''),

  'property name' => 'national_plan_objective',
  'property info' => array(
    'type' => 'text',
  ),

  'report field group' => 'columns',
  'report field key' => 'National Planning Objectives',

  'report filter endpoint' => 'nifilters/programs',
  'report filter name' => 'National Planning Objectives',

  'handler' => 'nationalPlanObjectiveMapper',
);

class nationalPlanObjectiveMapper extends activityMapperAutocompleteBase {
}
