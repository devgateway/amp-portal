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

  function get_value_options() { /* don't overwrite the value options */ }


  function option_definition() {
    $options = parent::option_definition();

    $options['type'] = array('default' => 'textfield');
    $options['error_message'] = array('default' => TRUE, 'bool' => TRUE);

    return $options;
  }

  function extra_options_form(&$form, &$form_state) {
    $form['type'] = array(
      '#type' => 'radios',
      '#title' => t('Selection type'),
      '#options' => array('token' => t('TokenInput'), 'textfield' => t('Autocomplete')),
      '#default_value' => $this->options['type'],
    );
  }

  function value_form(&$form, &$form_state) {
    if ($this->options['type'] == 'textfield') {
      $default = '';
      // @TODO: Fix!
      if ($this->value) {
        // @TODO: Provide a list of selected filters.
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
        '#autocomplete_path' => 'ampapi/autocomplete/' . $this->options['field'],
      );
    }
  }


  function value_validate($form, &$form_state) {
    // We only validate if they've chosen the text field style.
    if ($this->options['type'] != 'textfield') {
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

    $raw_value = $this->view->exposed_raw_input[$this->options['expose']['identifier']];

    // If it's non-required and there's no value don't bother filtering.
    if (!$this->options['expose']['required'] && empty($raw_value)) {
      return FALSE;
    }

    $plugin = ampapi_get_mapper_by_property_name($this->options['field']);
    if (empty($plugin['report filter endpoint'])) {
      return FALSE;
    }

    $class_name = ctools_plugin_get_class($plugin, 'handler');
    if (empty($class_name) || !in_array('activityMapperAutocompleteInterface', class_implements($class_name))) {
      return FALSE;
    }

    // If we have previously validated input, override.
    if (isset($raw_value)) {
      $value = $class_name::getAutocompleteValue($plugin, $raw_value);
      if (isset($value)) {
        $this->value = $value;
        return TRUE;
      }
    }

    return FALSE;
  }

  function exposed_validate(&$form, &$form_state) {
    if (empty($this->options['exposed'])) {
      return;
    }

    // $identifier = $this->options['expose']['identifier'];

    // // We only validate if they've chosen the text field style.
    // if ($this->options['type'] != 'textfield') {
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
