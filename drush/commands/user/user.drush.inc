<?php
// $Id:

/**
 * @file Drush User Management commands
 */

function user_drush_help($section) {
  switch ($section) {
    case 'meta:user:title':
      return dt('User commands');
    case 'meta:user:summary':
      return dt('Add, modify and delete users.');
  }
}

/**
 * Implementation of hook_drush_command().
 */
function user_drush_command() {
  $items['user-information'] = array(
    'description' => 'Print information about the specified user(s).',
    'aliases' => array('uinf'),
    'examples' => array(
      'drush user-information 2,3,someguy,somegal,billgates@microsoft.com' =>
        'Display information about any users with uids, names, or mail addresses matching the strings between commas.',
    ),
    'arguments' => array(
      'users' => 'A comma delimited list of uids, user names, or email addresses.',
    ),
    'required-arguments' => TRUE,
    'outputformat' => array(
      'default' => 'key-value-list',
      'pipe-format' => 'csv',
      'field-labels' => array(
        'uid' => 'User ID',
        'name' => 'User name',
        'pass' => 'Password',
        'mail' => 'User mail',
        'theme' => 'User theme',
        'signature' => 'Signature',
        'signature_format' => 'Signature format',
        'user_created' => 'User created',
        'created' => 'Created',
        'user_access' => 'User last access',
        'access' => 'Last access',
        'user_login' => 'User last login',
        'login' => 'Last login',
        'user_status' => 'User status',
        'status' => 'Status',
        'timezone' => 'Time zone',
        'picture' => 'User picture',
        'init' => 'Initial user mail',
        'roles' => 'User roles',
        'group_audience' => 'Group Audience',
      ),
      'format-cell' => 'csv',
      'fields-default' => array('uid', 'name', 'mail', 'roles', 'user_status'),
      'fields-pipe' => array('name', 'uid', 'mail', 'status', 'roles'),
      'fields-full' => array('uid', 'name', 'pass', 'mail', 'theme', 'signature', 'user_created', 'user_access', 'user_login', 'user_status', 'timezone', 'roles', 'group_audience'),
      'output-data-type' => 'format-table',
    ),
  );
  $items['user-block'] = array(
    'description' => 'Block the specified user(s).',
    'aliases' => array('ublk'),
    'arguments' => array(
      'users' => 'A comma delimited list of uids, user names, or email addresses.',
    ),
    'required-arguments' => TRUE,
    'examples' => array(
      'drush user-block 5,user3 --uid=2,3 --name=someguy,somegal --mail=billgates@microsoft.com' =>
        'Block the users with name, id, or email 5 or user3, uids 2 and 3, names someguy and somegal, and email address of billgates@microsoft.com',
    ),
    'options' => array(
      'uid' => 'A comma delimited list of uids to block',
      'name' => 'A comma delimited list of user names to block',
      'mail' => 'A comma delimited list of user mail addresses to block',
    ),
  );
  $items['user-unblock'] = array(
    'description' => 'Unblock the specified user(s).',
    'aliases' => array('uublk'),
    'arguments' => array(
      'users' => 'A comma delimited list of uids, user names, or email addresses.',
    ),
    'required-arguments' => TRUE,
    'examples' => array(
      'drush user-unblock 5,user3 --uid=2,3 --name=someguy,somegal --mail=billgates@microsoft.com' =>
        'Unblock the users with name, id, or email 5 or user3, uids 2 and 3, names someguy and somegal, and email address of billgates@microsoft.com',
    ),
    'options' => array(
      'uid' => 'A comma delimited list of uids to unblock',
      'name' => 'A comma delimited list of user names to unblock',
      'mail' => 'A comma delimited list of user mail addresses to unblock',
    ),
  );
  $items['user-add-role'] = array(
    'description' => 'Add a role to the specified user accounts.',
    'aliases' => array('urol'),
    'arguments' => array(
      'role' => 'The name of the role to add',
      'users' => '(optional) A comma delimited list of uids, user names, or email addresses.',
    ),
    'required-arguments' => 1,
    'examples' => array(
      'drush user-add-role "power user" 5,user3 --uid=2,3 --name=someguy,somegal --mail=billgates@microsoft.com' =>
        'Add the "power user" role to the accounts with name, id, or email 5 or user3, uids 2 and 3, names someguy and somegal, and email address of billgates@microsoft.com',
    ),
    'options' => array(
      'uid' => 'A comma delimited list of uids',
      'name' => 'A comma delimited list of user names',
      'mail' => 'A comma delimited list of user mail addresses',
    ),
  );
  $items['user-remove-role'] = array(
    'description' => 'Remove a role from the specified user accounts.',
    'aliases' => array('urrol'),
    'arguments' => array(
      'role' => 'The name of the role to remove',
      'users' => '(optional) A comma delimited list of uids, user names, or email addresses.',
    ),
    'required-arguments' => 1,
    'examples' => array(
      'drush user-remove-role "power user" 5,user3 --uid=2,3 --name=someguy,somegal --mail=billgates@microsoft.com' =>
        'Remove the "power user" role from the accounts with name, id, or email 5 or user3, uids 2 and 3, names someguy and somegal, and email address of billgates@microsoft.com',
    ),
    'options' => array(
      'uid' => 'A comma delimited list of uids',
      'name' => 'A comma delimited list of user names',
      'mail' => 'A comma delimited list of user mail addresses',
    ),
  );
  $items['user-create'] = array(
    'description' => 'Create a user account with the specified name.',
    'aliases' => array('ucrt'),
    'arguments' => array(
      'name' => 'The name of the account to add'
    ),
    'required-arguments' => TRUE,
    'examples' => array(
      'drush user-create newuser --mail="person@example.com" --password="letmein"' =>
        'Create a new user account with the name newuser, the email address person@example.com, and the password letmein',
    ),
    'options' => array(
      'password' => 'The password for the new account',
      'mail' => 'The email address for the new account',
    ),
  );
  $items['user-cancel'] = array(
    'description' => 'Cancel a user account with the specified name.',
    'aliases' => array('ucan'),
    'arguments' => array(
      'name' => 'The name of the account to cancel',
    ),
    'required-arguments' => TRUE,
    'examples' => array(
      'drush user-cancel username' =>
        'Cancel the user account with the name username and anonymize all content created by that user.',
    ),
  );
  $items['user-password'] = array(
    'description' => '(Re)Set the password for the user account with the specified name.',
    'aliases' => array('upwd'),
    'arguments' => array(
      'name' => 'The name of the account to modify.'
    ),
    'required-arguments' => TRUE,
    'options' => array(
      'password' => array(
        'description' => 'The new password for the account.',
        'required' => TRUE,
        'example-value' => 'foo',
      ),
    ),
    'examples' => array(
      'drush user-password someuser --password="correct horse battery staple"' =>
        'Set the password for the username someuser. @see xkcd.com/936',
    ),
  );
  $items['user-login'] = array(
    'description' => 'Display a one time login link for the given user account (defaults to uid 1).',
    'aliases' => array('uli'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'handle-remote-commands' => TRUE,
    'arguments' => array(
      'user' => 'An optional uid, user name, or email address for the user to log in as. Default is to log in as uid 1. The uid/name/mail options take priority if specified.',
      'path' => 'Optional path to redirect to after logging in.',
    ),
    'options' => array(
      'browser' => 'Optional value denotes which browser to use (defaults to operating system default). Set to 0 to suppress opening a browser.',
      'uid' => 'A uid to log in as.',
      'name' => 'A user name to log in as.',
      'mail' => 'A user mail address to log in as.',
    ),
    'examples' => array(
      'drush user-login ryan node/add/blog' => 'Displays and opens default web browser (if configured or detected) for a one-time login link for the user with the username ryan and redirect to the path node/add/blog.',
      'drush user-login --browser=firefox --mail=drush@example.org admin/settings/performance' => 'Open firefox web browser, login as the user with the e-mail address drush@example.org and redirect to the path admin/settings/performance.',
    ),
  );
  return $items;
}

/**
 * Implements hook_drush_help_alter().
 */
function user_drush_help_alter(&$command) {
  // Drupal 7+ only options.
  if ($command['command'] == 'user-cancel' && drush_drupal_major_version() >= 7) {
    $command['options']['delete-content'] = 'Delete all content created by the user';
    $command['examples']['drush user-cancel --delete-content username'] =
      'Cancel the user account with the name username and delete all content created by that user.';
  }
}

/**
 * Prints information about the specified user(s).
 */
function drush_user_information($users) {
  $result = array();
  $uids = _drush_user_get_users_from_arguments($users);
  foreach($uids as $uid) {
    $result[$uid] = _drush_user_info($uid);
  }
  return $result;
}

/**
 * Block the specified user(s).
 */
function drush_user_block($users = '') {
  $uids = _drush_user_get_users_from_options_and_arguments($users);
  if (!empty($uids)) {
    drush_op('user_user_operations_block', $uids);
  }
  else {
    return drush_set_error("Could not find any valid uids!");
  }
}

/**
 * Unblock the specified user(s).
 */
function drush_user_unblock($users = '') {
  $uids = _drush_user_get_users_from_options_and_arguments($users);
  if (!empty($uids)) {
    drush_op('user_user_operations_unblock', $uids);
  }
  else {
    return drush_set_error("Could not find any valid uids!");
  }
}

/**
 * Add a role to the specified user accounts.
 */
function drush_user_add_role($role, $users = '') {
  $uids = _drush_user_get_users_from_options_and_arguments($users);
  if (drush_drupal_major_version() >= 7) {
    $rid_query = db_query("SELECT rid FROM {role} WHERE name = :role", array(':role' => $role));
  }
  else {
    $rid_query = db_query("SELECT rid FROM {role} WHERE name = '%s'", $role);
  }
  if (!empty($uids)) {
    if ($rid = drush_db_result($rid_query)) {
      drush_op('user_multiple_role_edit', $uids, 'add_role', $rid);
      foreach($uids as $uid) {
        drush_log(dt("Added the !role role to uid !uid", array('!role' => $role, '!uid' => $uid)), 'success');
      }
    }
    else {
      return drush_set_error(dt("There is no role named: !role", array('!role' => $role)));
    }
  }
  else {
    return drush_set_error("Could not find any valid uids!");
  }
}

/**
 * Remove a role from the specified user accounts.
 */
function drush_user_remove_role($role, $users = '') {
  $uids = _drush_user_get_users_from_options_and_arguments($users);
  if (drush_drupal_major_version() >= 7) {
    $rid_query = db_query("SELECT rid FROM {role} WHERE name = :role", array(':role' => $role));
  }
  else {
    $rid_query = db_query("SELECT rid FROM {role} WHERE name = '%s'", $role);
  }
  if (!empty($uids)) {
    if ($rid = drush_db_result($rid_query)) {
      drush_op('user_multiple_role_edit', $uids, 'remove_role', $rid);
      foreach($uids as $uid) {
        drush_log(dt("Removed the !role role from uid !uid", array('!role' => $role, '!uid' => $uid)), 'success');
      }
    }
    else {
      return drush_set_error(dt("There is no role named: !role", array('!role' => $role)));
    }
  }
  else {
    return drush_set_error("Could not find any valid uids!");
  }
}

/**
 * Creates a new user account.
 */
function drush_user_create($name) {
  $mail = drush_get_option('mail');
  $pass = drush_get_option('password');
  $new_user = array(
    'name' => $name,
    'pass' => $pass,
    'mail' => $mail,
    'access' => '0',
    'status' => 1,
  );
  if (drush_drupal_major_version() >= 7) {
    $result = db_query("SELECT uid FROM {users} WHERE name = :name OR mail = :mail", array(':name' => $name, ':mail' => $new_user['mail']));
  }
  else {
    $result = db_query("SELECT uid FROM {users} WHERE name = '%s' OR mail = '%s'", $name, $new_user['mail']);
  }
  if (drush_db_result($result) === FALSE) {
    if (!drush_get_context('DRUSH_SIMULATE')) {
      if (drush_drupal_major_version() >= 8) {
        $new_user_object = entity_create('user', $new_user);
        $new_user_object->save();
      }
      else {
        $new_user_object = user_save(NULL, $new_user, NULL);
      }
      if ($new_user_object !== FALSE) {
        // See https://github.com/drush-ops/drush/issues/464
        // _drush_user_print_info($new_user_object->uid);
        drush_backend_set_result($new_user_object);
        return TRUE;
      }
      else {
        return drush_set_error("Could not create a new user account with the name " . $name . "!");
      }
    }
  }
  else {
    return drush_set_error("There is already a user account with the name " . $name . " or email address " . $new_user['mail'] . "!");
  }
}

/**
 * Cancels a user account.
 */
function drush_user_cancel($name) {
  if (drush_drupal_major_version() >= 7) {
    $result = db_query("SELECT uid FROM {users} WHERE name = :name", array(':name' => $name));
  }
  else {
    $result = db_query("SELECT uid FROM {users} WHERE name = '%s'", $name);
  }
  $uid = drush_db_result($result);
  if ($uid !== FALSE) {
    if (drush_get_option('delete-content') && drush_drupal_major_version() >= 7) {
      drush_log("All content created by this user will be deleted.", 'ok');
    }
    if (drush_confirm('Cancel user account?: ')) {
      if (drush_drupal_major_version() >= 7) {
        if (drush_get_option('delete-content')) {
          user_cancel(array(), $uid, 'user_cancel_delete');
        }
        else {
          user_cancel(array(), $uid, 'user_cancel_reassign');
        }
        // I got the following technique here: http://drupal.org/node/638712
        $batch =& batch_get();
        $batch['progressive'] = FALSE;
        batch_process();
      }
      else {
        user_delete(array(), $uid);
      }
    }
  }
  else {
    return drush_set_error("Could not find a user account with the name " . $name . ".");
  }
}

/**
 * Sets the password for the account with the given username
 */
function drush_user_password($name) {
  if (drush_drupal_major_version() >= 7) {
    $user = user_load_by_name($name);
  }
  else {
    $user = user_load(array('name' => $name));
  }
  if ($user !== FALSE) {
    if (!drush_get_context('DRUSH_SIMULATE')) {
      $pass = drush_get_option('password');
      // If no password has been provided, prompt for one.
      if (empty($pass)) $pass = drush_prompt(dt('Password'), NULL, TRUE, TRUE);
      if (drush_drupal_major_version() >= 8) {
        $user->pass = $pass;
        $user_object = $user->save();
      }
      else {
        $user_object = user_save($user, array('pass' => $pass));
      }
      if ($user_object === FALSE) {
        drush_set_error("Could not change the password for the user account with the name " . $name . "!");
      }
    }
  }
  else {
    drush_set_error("The user account with the name " . $name . " could not be loaded.");
  }
}

/**
 * Displays a one time login link for the given user.
 */
function drush_user_login($user = NULL, $path = NULL) {
  // Fix up arguments based on our assumptions.
  $user_object = $uid = FALSE;
  $args = func_get_args();

  // Redispatch if called against a remote-host so a browser is started on the
  // the *local* machine.
  $alias = drush_get_context('DRUSH_TARGET_SITE_ALIAS');
  if (drush_sitealias_is_remote_site($alias)) {
    $return = drush_invoke_process($alias, 'user-login', $args, drush_redispatch_get_options(), array('integrate' => FALSE));
    if ($return['error_status']) {
      return drush_set_error('Unable to execute user login.');
    }
    else {
      $link = $return['object'];
    }
  }
  else {
    if (!drush_bootstrap(DRUSH_BOOTSTRAP_DRUPAL_FULL)) {
      // Fail gracefully if unable to bootstrap Drupal.
      // drush_bootstrap() has already logged an error.
      return FALSE;
    }

    if (drush_get_option('uid', FALSE) || drush_get_option('name', FALSE) || drush_get_option('mail', FALSE)) {
      // A user option was passed, prefer that to the user argument.
      $user = NULL;
      // If we only have a single argument and one of the user options is passed,
      // then we assume the argument is the path to open.
      if (count($args) == 1) {
        $path = $args[0];
      }
    }
    else if (empty($user)) {
      // No user option or argument was passed, so we default to uid 1.
      $uid = 1;
    }

    // Try to load a user from provided options and arguments.
    if ($uid || $uid = reset(_drush_user_get_users_from_options_and_arguments($user))) {
      if ($user_object = user_load($uid)) {
        if ($user_object->status) {
          $options = array();
          if ($path) {
            $options['query']['destination'] = $path;
          }
          $link = url(user_pass_reset_url($user_object) . '/login', $options);
        }
        else {
          return drush_set_error("The user account $uid is blocked.");
        }
      }
      else {
        return drush_set_error("The user account for uid $uid could not be loaded.");
      }
    }
    else {
      return FALSE; // An error has already been logged.
    }
  }

  drush_start_browser($link);
  return $link;
}

/**
 * Print information about a given uid
 */
function _drush_user_print_info($uid) {
  $user_info = _drush_user_info($uid);
  drush_print_format($user_info, 'key-value-list');
}

function _drush_user_info($uid) {
  if (drush_drupal_major_version() >= 7) {
    $userinfo = user_load($uid);
  }
  else {
    $userinfo = user_load(array('uid' => $uid));
  }
  $userinfo = (array)$userinfo;
  unset($userinfo['data']);
  unset($userinfo['block']);
  unset($userinfo['form_build_id']);
  foreach (array('created', 'access', 'login') as $key) {
    $userinfo['user_' . $key] = format_date($userinfo[$key]);
  }
  // Note: in D8, $userinfo->roles may not contain the human-readable role names.
  // For example, it may contain 'authenticated' => 'authenticated' instead of
  // 'authenticated' => 'Authenticated user'.  In any event, we display the
  // machine name rather than the human-readable name for better output-conformity
  // with D6 and D7.
  if (drush_drupal_major_version() >= 8) {
    $userinfo['user_roles'] = $userinfo['roles'];
    $userinfo['roles'] = array_keys($userinfo['roles']);
  }
  $userinfo['user_status'] = $userinfo['status'] ? 'active' : 'blocked';
  return $userinfo;
}

/**
 * Given a comma-separated list of users, return uids
 * for users that match either by uid or email address.
 */
function _drush_user_get_users_from_arguments($users) {
  $uids = array();
  if ($users !== '') {
    $users = _convert_csv_to_array($users);
    foreach($users as $user) {
      $uid = _drush_user_get_uid($user);
      if ($uid !== FALSE) {
        $uids[] = $uid;
      }
    }
  }
  return $uids;
}

/**
 * Return the list of matching uids given
 */
function _drush_user_get_users_from_options_and_arguments($users) {
  $uids = drush_get_option_list('uids');

  foreach (array('uid', 'name', 'mail' ) as $user_attr) {
    if ($arg = drush_get_option($user_attr)) {
      foreach(explode(',', $arg) as $search) {
        $uid_query = FALSE;
        switch ($user_attr) {
          case 'uid':
            if (drush_drupal_major_version() >= 7) {
              $uid_query = db_query("SELECT uid FROM {users} WHERE uid = :uid", array(':uid' => $search));
            }
            else {
              $uid_query = db_query("SELECT uid FROM {users} WHERE uid = %d", $search);
            }
            break;
          case 'name':
            if (drush_drupal_major_version() >= 7) {
              $uid_query = db_query("SELECT uid FROM {users} WHERE name = :name", array(':name' => $search));
            }
            else {
              $uid_query = db_query("SELECT uid FROM {users} WHERE name = '%s'", $search);
            }
            break;
          case 'mail':
            if (drush_drupal_major_version() >= 7) {
              $uid_query = db_query("SELECT uid FROM {users} WHERE mail = :mail", array(':mail' => $search));
            }
            else {
              $uid_query = db_query("SELECT uid FROM {users} WHERE mail = '%s'", $search);
            }
            break;
        }
        if ($uid_query !== FALSE) {
          if ($uid = drush_db_result($uid_query)) {
            $uids[] = $uid;
          }
          else {
            drush_set_error("Could not find a uid for $user_attr = $search");
          }
        }
      }
    }
  }

  return array_merge($uids, _drush_user_get_users_from_arguments($users));
}

/**
 * Get uid(s) from a uid, user name, or email address.
 * Returns a uid, or FALSE if none found.
 */
function _drush_user_get_uid($search) {
  // We use a DB query while looking for the uid to keep things speedy.
  $uids = array();
  if (is_numeric($search)) {
    if (drush_drupal_major_version() >= 7) {
      $uid_query = db_query("SELECT uid, name FROM {users} WHERE uid = :uid OR name = :name", array(':uid' => $search, ':name' => $search));
    }
    else {
      $uid_query = db_query("SELECT uid, name FROM {users} WHERE uid = %d OR name = '%d'", $search, $search);
    }
  }
  else {
    if (drush_drupal_major_version() >= 7) {
      $uid_query = db_query("SELECT uid, name FROM {users} WHERE mail = :mail OR name = :name", array(':mail' => $search, ':name' => $search));
    }
    else {
      $uid_query = db_query("SELECT uid, name FROM {users} WHERE mail = '%s' OR name = '%s'", $search, $search);
    }
  }
  while ($uid = drush_db_fetch_object($uid_query)) {
    $uids[$uid->uid] = $uid->name;
  }
  switch (count($uids)) {
    case 0:
      return drush_set_error("Could not find a uid for the search term '" . $search . "'!");
      break;
    case 1:
      return array_pop(array_keys($uids));
      break;
    default:
      drush_print('More than one user account was found for the search string "' . $search . '".');
      return(drush_choice($uids, 'Please choose a name:', '!value (uid=!key)'));
  }
}
