<?php
/**
 * @file
 * Custom filter.
 */

/**
 *
 * @see views_handler_filter_many_to_one
 * @see efq_views_handler_filter_property_in_operator
 */
class ampapi_activity_views_handler_filter_in_operator extends efq_views_handler_filter_property_in_operator {
  /**
   * @var bool
   * Disable the possibility to force a single value.
   */
  var $always_multiple = TRUE;

  function has_extra_options() { return TRUE; }

  function expose_options() {
    parent::expose_options();

    // Just to make sure it saves properly.
    $this->options['expose']['required'] = FALSE;
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['type'] = array('default' => 'autocomplete');
    $options['error_message'] = array('default' => TRUE, 'bool' => TRUE);
    $options['amp_extra_options']['location_level'] = 0;

    return $options;
  }

  function extra_options_form(&$form, &$form_state) {
    $form['type'] = array(
      '#type' => 'radios',
      '#title' => t('Selection type'),
      '#options' => array(
        'tokeninput' => t('Tokeninput'),
        'autocomplete' => t('Autocomplete'),
        'select' => t('Dropdown Select'),
        'checkbox' => t('Checkbox'),
      ),
      '#default_value' => $this->options['type'],
    );
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['amp_extra_options'] = array(
      '#type' => 'fieldset',
      '#title' => t('Extra Options'),
      '#description' => t('All the extra options go here (such as custom AMP related options).')
    );
    $plugin = ampapi_get_mapper_by_property_name($this->options['field']);
    if ($plugin['property name'] == 'location') {
      $form['amp_extra_options']['location_level'] = array(
        '#type' => 'select',
        '#title' => t('Location Level'),
        '#options' => array(
          0 => t('- Show all - '),
          2 => t('Level 2 (Department)'),
          3 => t('Level 3 (Municipality)')
        ),
        '#default_value' => $this->options['amp_extra_options']['location_level'],
      );
    }
  }

  function value_form(&$form, &$form_state) {
    $identifier = $this->options['expose']['identifier'];
    $field_name = $this->options['field'];

    if ($this->options['type'] == 'tokeninput') {
      // @HACK: For some reason we don't have the provided data.
      $js_setting = array();
      $js_setting[$identifier]['values'] = array();

      if (isset($form_state['input'][$identifier]) && $this->view->tag === 'default') {
        $values = $form_state['input'][$identifier];

        if (!empty($values)) {
          $values = explode(',', $values);

          $plugin = ampapi_get_mapper_by_property_name($this->options['field']);
          $class_name = ctools_plugin_get_class($plugin, 'handler');

          // If we have previously validated input, override.
          /** @var activityMapperAutocompleteInterface $handler */
          $handler = new $class_name();

          $js_setting[$identifier]['values'] = $handler->getAutocompleteValue($plugin, $values, 'tokeninputids');
        }
      }
      $js_setting['language'] = $GLOBALS['language']->language;
      drupal_add_js(array('viewsTokeninput' => $js_setting), 'setting');

      // Load the "jQuery Tokeninput" JavaScript library.
      libraries_load('jquery-tokeninput', 'minified');

      // @TODO: Use libraries API.
      if ($this->view->name !== 'reports') {
        $module_path = drupal_get_path('module', 'ampapi_activity');
        drupal_add_js($module_path . '/scripts/ampapi_activity.searchform.js');
      }
      else {
        // Just a copy of previous script but adjusted to our reports' case.
        $module_path = drupal_get_path('module', 'ampreports');
        drupal_add_js($module_path . '/js/ampapi_reports.searchform.js');
      }

      $form['value'] = array(
        '#title' => t('Selected'),
        '#type' => 'textfield',
        '#default_value' => NULL,
        '#attributes' => array(
          'class' => array(
            'tokeninput-textfield',
          ),
          'data-name' => $field_name,
          'data-identifier' => $identifier,
          'data-level' => $this->options['amp_extra_options']['location_level'],
        ),
      );
    }
    else if ($this->options['type'] == 'autocomplete') {
      $default = '';
      // @TODO: Provide default value for filter!
      if ($this->value) {
        // @TODO: Provide a list of selected filters.
        // If we have previously validated input, override.
        // $field_name = $this->options['field'];
        // $handler = new $class_name();
        // $js_setting[$field_name]['values'] = $handler->getAutocompleteValue($plugin, $values, 'tokeninputids');
        // $query = new EntityFieldQuery;
        // $result = $query
        //   ->entityCondition('entity_type', 'taxonomy_term')
        //   ->entityCondition('entity_id', $this->value)
        //   ->execute();
        // if (!empty($result['taxonomy_term'])) {
        //   $terms = entity_load('taxonomy_term', array_keys($result['taxonomy_term']));
        //   foreach ($terms as $term) {
        //     if ($default) {
        //       $default .= ', ';
        //     }
        //     $default .= $term->name;
        //   }
        // }
      }
      $form['value'] = array(
        '#title' => t('Selected'),
        '#type' => 'textfield',
        '#default_value' => $default,
        '#autocomplete_path' => 'ampapi/autocomplete/' . $field_name,
      );

      // We want to make certain changes in the case of location.
      if ($this->options['amp_extra_options']['location_level'] != 0) {
        $form['value']['#autocomplete_path'] = 'ampapi/autocomplete/' . $field_name . '/' . $this->options['amp_extra_options']['location_level'];
      }
    }
    else if ($this->options['type'] == 'select') {
      if (!empty($this->definition['options arguments'])) {
        foreach ($this->definition['options arguments'] as $options_argument) {
          $plugin = ampapi_get_mapper($options_argument);
          ctools_plugin_get_class($plugin, 'handler');
        }
      }

      parent::value_form($form, $form_state);
    }
    else if ($this->options['type'] == 'checkbox') {
      if (!empty($form['group_button'])) {
        if (!empty($this->definition['options arguments'])) {
          foreach ($this->definition['options arguments'] as $options_argument) {
            $plugin = ampapi_get_mapper($options_argument);
            ctools_plugin_get_class($plugin, 'handler');
          }
        }
        parent::value_form($form, $form_state);
        $form['value']['#type'] = 'select';
        $form['value']['#multiple'] = FALSE;
      }
      else {
        $form['value'] = array(
          '#title' => $this->options['expose']['label'],
          '#type' => 'checkbox',
          '#default_value' => 0,
        );
      }
    }
  }

  function value_validate($form, &$form_state) {
    // We only validate if they've chosen the text field style.
    if ($this->options['type'] != 'autocomplete') {
      return;
    }

    // $values = drupal_explode_tags($form_state['values']['options']['value']);
    // $tids = $this->validate_term_strings($form['value'], $values);

    // if ($tids) {
    //   $form_state['values']['options']['value'] = $tids;
    // }
  }

  function accept_exposed_input($input) {
    if (empty($this->options['exposed']) || !$this->view->display_handler->uses_exposed()) {
      return TRUE;
    }

    $identifier = $this->options['expose']['identifier'];
    $raw_value = NULL;
    if (isset($this->view->exposed_raw_input[$identifier])) {
      $raw_value = $this->view->exposed_raw_input[$identifier];
    }

    // If it's non-required and there's no value don't bother filtering.
    if (!$this->options['expose']['required'] && empty($raw_value)) {
      return FALSE;
    }

    if ($this->options['type'] == 'tokeninput') {
      $tokens = explode(',', $raw_value);

      // The API only likes integers (except locations).
      if ($this->field !== 'location') {
//        foreach ($tokens as &$token) {
//          $token = intval($token);
//        }
      }
      $this->value = $tokens;
      return TRUE;
    }
    else if ($this->options['type'] == 'autocomplete') {
      $plugin = ampapi_get_mapper_by_property_name($this->options['field']);
      if (empty($plugin['report filter endpoint'])) {
        return FALSE;
      }

      $class_name = ctools_plugin_get_class($plugin, 'handler');
      if (empty($class_name) || !in_array('activityMapperAutocompleteInterface', class_implements($class_name))) {
        return FALSE;
      }

      // If we have previously validated input, override.
      /** @var activityMapperAutocompleteInterface $handler */
      $handler = new $class_name();
      // Exceptions, this needs to be re-done.
      if ($plugin['property name'] == 'location' && $this->options['expose']['identifier'] == 'location_dep' && !empty($this->view->exposed_input['location_mun'])) {
        return FALSE;
      }
      else {
        $value = $handler->getAutocompleteValue($plugin, array($raw_value), 'autocompleteids');
      }

      if (isset($value)) {
        $this->value = $value;
        return TRUE;
      }
    }
    else if ($this->options['type'] == 'select') {
      if ($raw_value !== 'All') {
        $this->value = array($raw_value);
      }
      return TRUE;
    }
    else if ($this->options['type'] == 'checkbox') {
      if ($raw_value == 1) {
        $this->value = array($this->options['value']);
        return TRUE;
      }
    }
    return FALSE;
  }

  /**
   * @TODO: Add validation!
   */
  function exposed_validate(&$form, &$form_state) {
    if (empty($this->options['exposed'])) {
      return;
    }

    $identifier = $this->options['expose']['identifier'];
    if ($this->options['expose']['required'] && empty($form_state['values'][$identifier])) {
      form_error($form[$identifier], t('The identifier is required if the filter is exposed.'));
    }

    // // We only validate if they've chosen the text field style.
    // if ($this->options['type'] != 'autocomplete') {
    //   if ($form_state['values'][$identifier] != 'All')  {
    //     $this->validated_exposed_input = (array) $form_state['values'][$identifier];
    //   }
    //   return;
    // }

    // if (empty($this->options['expose']['identifier'])) {
    //   return;
    // }

    // $values = drupal_explode_tags($form_state['values'][$identifier]);

    // $tids = $this->validate_term_strings($form[$identifier], $values);
    // if ($tids) {
    //   $this->validated_exposed_input = $tids;
    // }
  }

  function expose_form(&$form, &$form_state) {
    parent::expose_form($form, $form_state);
    if ($this->options['type'] != 'select') {
      unset($form['expose']['reduce']);
    }
    $form['error_message'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display error message'),
      '#default_value' => !empty($this->options['error_message']),
    );
  }

  function admin_summary() {
    return '';
  }
}
