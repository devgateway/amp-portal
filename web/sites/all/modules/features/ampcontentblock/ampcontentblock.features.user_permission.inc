<?php
/**
 * @file
 * ampcontentblock.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ampcontentblock_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'contentblock entity access overview'.
  $permissions['contentblock entity access overview'] = array(
    'name' => 'contentblock entity access overview',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'contentblock',
  );

  // Exported permission: 'contentblock entity administer'.
  $permissions['contentblock entity administer'] = array(
    'name' => 'contentblock entity administer',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'contentblock',
  );

  // Exported permission: 'contentblock entity create'.
  $permissions['contentblock entity create'] = array(
    'name' => 'contentblock entity create',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'contentblock',
  );

  // Exported permission: 'contentblock entity delete'.
  $permissions['contentblock entity delete'] = array(
    'name' => 'contentblock entity delete',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'contentblock',
  );

  // Exported permission: 'contentblock entity edit'.
  $permissions['contentblock entity edit'] = array(
    'name' => 'contentblock entity edit',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'contentblock',
  );

  // Exported permission: 'contentblock entity view'.
  $permissions['contentblock entity view'] = array(
    'name' => 'contentblock entity view',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'contentblock',
  );

  return $permissions;
}
