<?php
/**
 * @file
 * Custom filter.
 */

class ampapi_activity_views_handler_filter_in_operator extends efq_views_handler_filter_property_in_operator {
  function get_value_options() {
    if (isset($this->value_options)) {
      return;
    }

    // Load the plugin information.
    $plugin_name = reset($this->definition['options arguments']);
    $plugin = ampapi_get_mapper($plugin_name);

    // Load the plugin code and get the options.
    if ($class_name = ctools_plugin_get_class($plugin, 'handler')) {
      $this->value_options = call_user_func_array($this->definition['options callback'], array($plugin));
    }
    else {
      $this->value_options = array(t('No'), t('Yes'));
    }

    return $this->value_options;
  }
}
