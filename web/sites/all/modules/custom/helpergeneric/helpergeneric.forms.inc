<?php
/**
 * @file
 * Contains hooks implementations that deal with cleaning up various forms.
 */

/**
 * Implements hook_update_projects_alter().
 *
 * Hide project-specific modules from the module update list.
 */
function helpergeneric_update_projects_alter(&$projects) {
  $not_updated = array();
  foreach ($projects as $project_name => $project_info) {
    if ($project_info['project_type'] == 'core') {
      continue;
    }

    // Determine where the module is located.
    $projet_path = drupal_get_path($project_info['project_type'], $project_info['name']);

    // Projects like 'features_extra' don't contain a module called 'features_extra' so an empty path is returned.
    $project_location = '';
    if (!empty($projet_path)) {
      $project_location = dirname($projet_path);
    }

    // Do not query updates for custom modules and features.
    switch ($project_location) {
      case 'sites/all/modules/custom':
      case 'sites/all/modules/features':
        // Hide project-specific modules from the update list.
        $not_updated[] = $projects[$project_name]['info']['name'];
        unset($projects[$project_name]);
        break;
    }
  }

  // if (!empty($not_updated)) {
  //   $message = 'The following modules are not being checked for updates: @moduleslist';
  //   drupal_set_message(t($message, array('@moduleslist' => implode(', ', $not_updated))), 'warning');
  // }
}

/**
 * Implements hook_features_api_alter().
 *
 * Prevent exporting of some features API components.
 */
function helpergeneric_features_api_alter(&$components) {
  // We manage menu_links manually or via update scripts.
  unset($components['menu_links']);
}

/**
 * Implements hook_features_component_export_alter().
 *
 * Filter the available compoenents in the (re)create feature form.
 */
function helpergeneric_features_component_export_alter(&$component_export, $component) {
  switch ($component) {
    case 'dependencies':
      // Hide custom features from dependencies.
      $entries_list = array(
        'ampet_blog',
        'ampet_page',
        'amppermissions',
        'ampsettings',
        'ampviewsettings',
      );
      break;

    case 'menu_custom':
      // Hide menus.
      $entries_list = array(
        'devel',
        'main-menu',
        'management',
        'navigation',
        'user-menu',
      );
      break;

    case 'user_permission':
      $entries_list = array(
        // Hide admin_menu module permissions.
        'access administration menu',
        'flush caches',
        'display drupal links',

        // Hide devel module permissions.
        'access devel information',
        'execute php code',
        'switch users',

        // Hide ds_ui module permissions.
        'admin_view_modes',
        'admin_fields',
        'admin_classes',

        // Hide less module permissions.
        'administer less',
      );
      break;

    case 'variable':
      // Hide variables that should not be exported.
      $entries_list = array(
        // Custom variables.
        'contentblock_blockref_blog',
        'contentblock_blockref_homepage',
        'date_format_shortest',
        'helpergeneric_cleanup_ui_force',

        // Hide CORE variables.
        'additional_settings__active_tab_blog',
        'additional_settings__active_tab_page',
        'cache',
        'cache_lifetime',
        'clean_url',
        'cron_key',
        'cron_last',
        'css_js_query_string',
        'date_default_timezone',
        'date_first_day',
        'date_format_long',
        'date_format_medium',
        'date_format_short',
        'dblog_row_limit',
        'drupal_private_key',
        'drupal_css_cache_files',
        'drupal_http_request_fails',
        'drupal_js_cache_files',
        'error_level',
        'file_temporary_path',
        'htmlpurifier_version_current',
        // 'image_toolkit',
        'install_profile',
        'install_task',
        'install_time',
        // 'job_scheduler_rebuild_all',
        'menu_expanded',
        'menu_masks',
        'page_cache_maximum_age',
        'page_compression',
        'path_alias_whitelist',
        'preprocess_css',
        'preprocess_js',
        'site_default_country',
        'site_mail',
        'site_name',
        'theme_default',

        // Hide ctools.module variables.
        'ctools_last_cron',

        // Hide date.module variables.
        'date_api_version',
        'date_views_month_format_with_year',
        'date_views_month_format_without_year',
        'date_views_day_format_with_year',
        'date_views_day_format_without_year',
        'date_views_week_format_with_year',
        'date_views_week_format_without_year',

        // Hide entity.module variables.
        'entity_cache_tables_created',

        // Hide entityreference.module variables.
        'entityreference:base-tables',

        // Hide features.module variables.
        'features_codecache',
        'features_default_export_path',
        'features_feature_locked',
        'features_ignored_orphans',
        'features_lock_mode',
        'features_semaphore',

        // Hide less.module variables.
        'less_devel',
        'less_dir',
        'less_engine',
        'less_watch',

        // Hide update.module variables.
        'update_last_check',

        // Hide update_scripts.module variables.
        'update_scripts_clear_cache',
        'update_scripts_directory',
        'update_scripts_revert_features',

        // Hide views.module variables.
        'views_show_additional_queries',

        // Hide views_ui.module variables.
        'views_ui_always_live_preview',
        'views_ui_custom_theme',
        'views_ui_display_embed',
        'views_ui_show_advanced_column',
        'views_ui_show_advanced_help_warning',
        'views_ui_show_listing_filters',
        'views_ui_show_master_display',
        'views_ui_show_performance_statistics',
        'views_ui_show_preview_information',
        'views_ui_show_sql_query',
        'views_ui_show_sql_query_where',
      );
      break;

    case 'views_view':
      // Hide views.
      $entries_list = array(
        'redirects',
      );
      break;

  }

  if (empty($entries_list)) {
    return;
  }

  $removed_entries_list = array();
  foreach ($entries_list as $name) {
    if (isset($component_export['options']['sources'][$name])) {
      unset($component_export['options']['sources'][$name]);
      $removed_entries_list[] = check_plain($name);
    }

    if ($component == 'dependencies') {
      if (isset($component_export['options']['detected'][$name])) {
        unset($component_export['options']['detected'][$name]);
      }
    }
  }

  if (!empty($removed_entries_list)) {
    $message = 'The following are not listed in the <b>%name</b> components export list: @entries';
    $t_args = array(
      '%name' => $component_export['name'] . " (${component})",
      '@entries' => implode(', ', $removed_entries_list),
    );
    drupal_set_message(t($message, $t_args), 'warning');
  }
}

/**
 * Implements hook_form_FORM_ID_alter() for node_form().
 */
function helpergeneric_form_node_form_alter(&$form, &$form_state, $form_id) {
  if (helpergeneric_cleanup_ui()) {
    helpergeneric_cleanup_node_form($form, $form_state, $form_id);
  }

  // Control "Event Date" field visibility.
  if (isset($form['field_blog_entry_type'], $form['field_blog_event_date'])) {
    // Show the "Event Date" only if blog entry type is event.
    // @todo Deal with language translations.
    $form['field_blog_event_date']['#states'] = array(
      'visible' => array(
        ':input[name="field_blog_entry_type[und][event]"]' => array('checked' => TRUE),
      ),
    );
    // Remove event date value on submit if field_blog_entry_type is not an event.
    $form['#validate'][] = 'helpergeneric_node_form_event_date_validate';
  }
}

/**
 * Helper function required by hook_form_FORM_ID_alter() for node_form().
 */
function helpergeneric_cleanup_node_form(&$form, &$form_state, $form_id) {
  // Do not display as vertical tabs.
  $form['additional_settings'] = array();

  if (isset($form['author'])) {
    $form['author']['#access'] = FALSE;
  }

  // Hide "Comment settings" fieldset for all node types except "Blog entry".
  if ($form['#node']->type != 'blog') {
    $form['comment_settings']['#access'] = FALSE;
  }

  if (isset($form['menu'])) {
    $form['menu']['#access'] = FALSE;
  }

  if (isset($form['redirect'])) {
    $form['redirect']['#access'] = FALSE;
  }

  if (isset($form['revision_information'])) {
    $form['revision_information']['#access'] = FALSE;
  }

  if (isset($form['options']['promote'])) {
    $form['options']['promote']['#access'] = FALSE;
  }

  if (isset($form['options']['sticky'])) {
    $form['options']['sticky']['#access'] = FALSE;
  }
}

/**
 * Form validation handler for node_form_alter().
 */
function helpergeneric_node_form_event_date_validate($form, &$form_state) {
  // Get the submitted input values.
  $blog_entry_type = $form_state['input']['field_blog_entry_type'][LANGUAGE_NONE];

  if (empty($blog_entry_type['event'])) {
    // Remove event date if the blog entry is not tagged as an event..
    $form_state['values']['field_blog_event_date'][LANGUAGE_NONE] = array();
  }
  else if (empty($form_state['values']['field_blog_event_date'][LANGUAGE_NONE][0]['value'])) {
    // Display an error if the user submitted an event blog but did not provide an event date.
    form_set_error('field_blog_event_date', t('The blog entry is tagged as an event, please provide a valid event date.'));
  }
}

/**
 * Implements hook_form_FORM_ID_alter() for user_profile_form().
 */
function helpergeneric_form_user_profile_form_alter(&$form, &$form_state, $form_id) {
  if (helpergeneric_cleanup_ui()) {
    helpergeneric_cleanup_user_form($form, $form_state, $form_id);
  }
}

/**
 * Helper function required by hook_form_FORM_ID_alter() for user_profile_form().
 */
function helpergeneric_cleanup_user_form(&$form, &$form_state, $form_id) {
  if (isset($form['redirect'])) {
    $form['redirect']['#access'] = FALSE;
  }
}

/**
 * Implements hook_form_FORM_ID_alter() for file_entity_edit().
 */
function helpergeneric_form_file_entity_edit_alter(&$form, &$form_state, $form_id) {
  if (helpergeneric_cleanup_ui()) {
    helpergeneric_cleanup_file_form($form, $form_state, $form_id);
  }
}

/**
 * Helper function required by hook_form_FORM_ID_alter() for file_entity_edit().
 */
function helpergeneric_cleanup_file_form(&$form, &$form_state, $form_id) {
  if (isset($form['destination'])) {
    $form['destination']['#access'] = FALSE;
  }

  if (isset($form['path'])) {
    $form['path']['#access'] = FALSE;
  }

  if (isset($form['redirect'])) {
    $form['redirect']['#access'] = FALSE;
  }

  if (isset($form['user'])) {
    $form['user']['#access'] = FALSE;
  }
}

/**
 * Implements hook_form_alter().
 */
function helpergeneric_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'user_login') {
    drupal_set_title('Log in');
    $form['actions']['cancel'] = array(
      '#type' => 'link',
      '#title' => t('Lost password?'),
      '#href' => 'user/password',
      '#weight' => 20,
    );
  }
}
