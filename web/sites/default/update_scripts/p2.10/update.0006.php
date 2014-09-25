<?php

// Update module weight.
db_update('system')
  ->fields(array('weight' => 20))
  ->condition('name', 'helpergeneric')
  ->execute();

// Update module weight.
db_update('system')
  ->fields(array('weight' => 20))
  ->condition('name', 'helpertheme')
  ->execute();

// Update module weight.
db_update('system')
  ->fields(array('weight' => 20))
  ->condition('name', 'helperviews')
  ->execute();

// Provide a list of modules to be installed.
$modules = array(
  'contextual',

  'elements',

  'contentblock',
  'helpergeneric',
  'helpertheme',
  'helperviews',
);
_us_module__install($modules);

// Clear system caches.
drupal_flush_all_caches();
