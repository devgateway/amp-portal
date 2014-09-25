<?php
/**
 * @file
 * ampviewsettings.ds.inc
 */

/**
 * Implements hook_ds_view_modes_info().
 */
function ampviewsettings_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'teaser_featured';
  $ds_view_mode->label = 'Teaser: Featured';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['teaser_featured'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'teaser_normal';
  $ds_view_mode->label = 'Teaser: Normal';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['teaser_normal'] = $ds_view_mode;

  return $export;
}
