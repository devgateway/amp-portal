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
    if (!empty($view->exposed_data['location_dep'])) {
      $processed_filters .= drupal_html_class($view->exposed_data['location_dep']);
    }
    if (!empty($view->exposed_data['location_mun'])) {
      $processed_filters .= drupal_html_class($view->exposed_data['location_mun']);
    }

    $tokens['%processed_filters'] = $processed_filters;

    $changed_output = strtr($classic_output, $tokens);
    return $changed_output;
  }
}
