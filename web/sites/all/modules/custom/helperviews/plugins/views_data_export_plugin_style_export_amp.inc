<?php
/**
 * @file
 * Plugin include file for export style plugin.
 */

/**
 * Generalized style plugin for export plugins.
 *
 * @ingroup views_style_plugins
 */
class views_data_export_plugin_style_export_amp extends views_data_export_plugin_style_export {
  /**
   *  {@inheritdoc}
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $extra_options = array();
    $extra_options[] = '%processed_filters == depart1_mun2';
    $form['help']['#value'] .= theme('item_list', array('items' => $extra_options, 'title' => t('Extra AMP Options')));
  }

  /**
   *  {@inheritdoc}
   */
  function generate_filename() {
    $classic_output = parent::generate_filename();
    $view = $this->view;

    $processed_filters = '';

    $values = array();
    if (!empty($view->exposed_data['location_dep'])) {
      $values['dep'] = $view->exposed_data['location_dep'];
    }
    if (!empty($view->exposed_data['location_mun'])) {
      $values['mun'] = $view->exposed_data['location_mun'];
    }

    // Well guess what, because we're using token-inputs, we have just the IDs.
    // But we really need the names of the locations (or fully loaded locations).
    $plugin = ampapi_get_mapper_by_property_name('location');
    $class_name = ctools_plugin_get_class($plugin, 'handler');
    $handler = new $class_name();
    $values_fetched = $handler->getAutocompleteValue($plugin, $values, 'tokeninputids');
    foreach ($values_fetched as $value_fetched) {
      if (!empty($values['dep']) && $value_fetched['id'] == $values['dep']) {
        $department = $value_fetched;
      }
      if (!empty($values['mun']) && $value_fetched['id'] == $values['mun']) {
        $municipality = $value_fetched;
      }
    }

    // Let's prepend now.
    if (!empty($department)) {
      $processed_filters .= drupal_html_class($department['name']);
    }
    if (!empty($municipality)) {
      $processed_filters .= '--' . drupal_html_class($municipality['name']);
    }

    $tokens['%processed_filters'] = $processed_filters;

    $changed_output = strtr($classic_output, $tokens);
    return $changed_output;
  }
}
