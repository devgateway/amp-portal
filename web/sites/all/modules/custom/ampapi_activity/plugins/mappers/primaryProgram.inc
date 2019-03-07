<?php
/**
 * @file
 * primaryProgram plugin.
 */

$plugin = array(
  'title' => t('Primary Program'),
  'description' => t(''),

  'property name' => 'primary_program',
  'property info' => array(
    'type' => 'text',
  ),

  'report field group' => 'columns',
  'report field key' => 'Primary Program Level 1',

  'handler' => 'primaryProgramMapper',
);

class primaryProgramMapper extends activityMapperBase {
}
