<?php

/**
 * @file
 * Provides a custom Top Donors widget.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'hidden' => TRUE,
  'title' => 'Total Activities',
  'description' => 'Will display the total commitments, disbursements and the total number of activities in system.',
  'render callback' => 'contentwidget_totalactivities_widget_render',
  'settings form' => 'contentwidget_totalactivities_widget_settings',
  'settings storage' => 'contentwidget_totalactivities_widget_settings_storage',
  'resource api path' => 'data/report/custom/paginate',
  'defaults' => array(
  ),
);

function contentwidget_totalactivities_widget_retrieve_data($plugin, $widget_settings, $langcode = NULL) {
  $api_status = ampAPIRestClient::status();
  if (!$api_status['online']) {
    return array();
  }

  $langcode = (empty($langcode) ? LANGUAGE_NONE : $langcode);
  $cache_id = "contentblock:widget:{$langcode}:totalactivities:" . md5(serialize($widget_settings));

  // Let's prepare the amount units (pre-configured per widget).
  $amount_units_key = isset($widget_settings['amount-units']) ? $widget_settings['amount-units'] : 'amount-units-1';
  $amount_fraction_digits = isset($widget_settings['amount-fraction-digits']) ? $widget_settings['amount-fraction-digits'] : 3;
  $amount_units_settings = _ampapi_activity_get_api_settings('amount-format:number-divider');
  $amount_units_options = array();
  foreach ($amount_units_settings->value->options as $delta => $amount_unit_option) {
    $amount_units_options[$amount_unit_option->id] = $amount_unit_option;
  }
  $amount_units = $amount_units_options[$amount_units_key];

  // Try to get the processed response from cache.
  if ($cached = cache_get($cache_id, 'cache')) {
    return $cached->data;
  }

  // Prepare a list of options for the request.
  $options = array();
  $options['headers'] = array(
    'Accept' => 'application/json',
    'Content-Type' => 'application/json',
  );

  $request_body = array();

  $id_plugin = ampapi_get_mapper_by_property_name('id');
  $request_body['add_columns'][] = $id_plugin['report field key'];

  // If one of these is disabled, don't add it to the measures.
  if ((isset($widget_settings['enable_commitments']) && $widget_settings['enable_commitments'] == TRUE)
    || !isset($widget_settings['enable_commitments'])) {
    $actual_commitments_plugin = ampapi_get_mapper_by_property_name('actual_commitments');
    $request_body['add_measures'][] = $actual_commitments_plugin['report field key'];
  }
  if ((isset($widget_settings['enable_disbursements']) && $widget_settings['enable_disbursements'] == TRUE)
    || !isset($widget_settings['enable_disbursements'])) {
    $actual_disbursements_plugin = ampapi_get_mapper_by_property_name('actual_disbursements');
    $request_body['add_measures'][] = $actual_disbursements_plugin['report field key'];
  }

  $request_body['page'] = 1;
  $request_body['recordsPerPage'] = 1;
  $request_body['regenerate'] = TRUE;
  $request_body['rowTotals'] = TRUE;
  $request_body['raw_values'] = array('M');
  $request_body['name'] = 'api:totalactivities';

  // Include Activities with empty funding in the total activities count.
  $request_body['show_empty_rows'] = TRUE;

  // Get the API settings.
  $api_settings = helpergeneric_get_api_settings();

  // Let's add amount units.
  $request_body['settings']['amount-format']['number-divider'] = $amount_units->value;
  $request_body['settings']['amount-format']['max-frac-digits'] = (integer) $amount_fraction_digits;

  // Handle the global "Humanitarian Aid" filter.
  // @see helpergeneric_api_settings_form()
  if (!empty($api_settings['humanitarian_aid_only'])) {
    $humanitarian_aid_plugin = ampapi_get_mapper_by_property_name('humanitarian_aid');
    $class_name = ctools_plugin_get_class($humanitarian_aid_plugin, 'handler');
    /** @var activityMapperOptionsInterface $handler */
    $handler = new $class_name();

    // Only display data related to humanitarian aid.
    // NOTE: Filters for the custom reports endpoint need to be inside a "filters" key.
    $ha_key = $humanitarian_aid_plugin['report field key'];
    $ha_value = $handler->getMatchedValue($humanitarian_aid_plugin, TRUE);
    $request_body['filters'][$ha_key] = array($ha_value);
  }

  // Handle the global "Disaster Response Marker" filter.
  // @see helpergeneric_api_settings_form()
  if (!empty($api_settings['disaster_response_marker_only'])) {
    $disaster_response_marker_plugin = ampapi_get_mapper_by_property_name('disaster_response_marker');
    $class_name = ctools_plugin_get_class($disaster_response_marker_plugin, 'handler');
    /** @var activityMapperOptionsInterface $handler */
    $handler = new $class_name();

    // Only display data related to disaster response.
    $drm_key = $disaster_response_marker_plugin['report field key'];
    $drm_value = $handler->getMatchedValue($disaster_response_marker_plugin, TRUE);
    $request_body['filters'][$drm_key] = array($drm_value);
  }

  // JSON Encode the request body. Can't use JSON_FORCE_OBJECT.
  $options['body'] = empty($request_body) ? '{}' : json_encode($request_body);

  // Get the data.
  $use_cache = FALSE;  // We cache the processed data, not the request.
  $response_data = ampAPIRestClient::post($plugin['resource api path'], $options, $use_cache);

  if (empty($response_data)) {
    return array();
  }

  // Get the number formatting pattern.
  $currency_setting = _ampapi_activity_get_api_settings('currency-code');
  $currency = $currency_setting->value->defaultId;

  $report_totals = array();
  /** @noinspection PhpUndefinedFieldInspection */
  foreach ($response_data->headers as $h_info) {
    // @TODO: use mappers.
    if (!in_array($h_info->hierarchicalName, array('[Totals][Actual Commitments]', '[Totals][Actual Disbursements]'))) {
      continue;
    }

    /** @noinspection PhpUndefinedFieldInspection */
    if (!isset($response_data->page->pageArea->contents->{$h_info->hierarchicalName}->value)) {
      continue;
    }

    // Now, we really trust the API display values.
    if (isset($widget_settings['amount-units-label-type'])) {
      $amount_units_label = filter_xss(_ampapi_amount_unit_get_label($amount_units->id, $widget_settings['amount-units-label-type']));
    }
    else {
      $amount_units_label = filter_xss(_ampapi_amount_unit_get_label($amount_units->id, 'long'));
    }

    /** @noinspection PhpUndefinedFieldInspection */
    $amount = check_plain($response_data->page->pageArea->contents->{$h_info->hierarchicalName}->displayedValue);
    $amount = '<span class="amount">' . $amount . '</span> ';
    $amount .= '<span class="text">' . t('@amount_units !currencysymbol', array('!currencysymbol' => $currency, '@amount_units' => $amount_units_label)) . '</span>';

    switch ($h_info->hierarchicalName) {
      case '[Totals][Actual Commitments]':
        $report_totals['actual_commitments'] = $amount;
        break;
      case '[Totals][Actual Disbursements]':
        $report_totals['actual_disbursements'] = $amount;
        break;
    }
  }

  /** @noinspection PhpUndefinedFieldInspection */
  if (!empty($response_data->page->totalRecords)) {
    /** @noinspection PhpUndefinedFieldInspection */
    $report_totals['activities_count'] = '<span class="amount">' . intval($response_data->page->totalRecords) . '</span> ';
  }

  if (empty($report_totals)) {
    ampAPIRestClient::log($plugin['title'] . ': Data for measures is missing', array());
    return array();
  }

  // 1 hours cache life time for requests should be plenty for now.
  $expire = 3600;
  cache_set($cache_id, $report_totals, 'cache', REQUEST_TIME + $expire);

  return $report_totals;
}

/**
 * Render callback for the 'Top Donors' predefined widget.
 */
function contentwidget_totalactivities_widget_render($plugin, $widget_settings, $entity, $langcode) {
  // Provide some default values.
  $widget_settings += $plugin['defaults'];

  // Make the queries only if the entity is published.
  if ($entity->status == NODE_PUBLISHED) {
    $data = contentwidget_totalactivities_widget_retrieve_data($plugin, $widget_settings, $langcode);
    if (empty($data)) {
      return '';
    }
  }

  $info_blocks = array(
    'actual_commitments' => 'Total Commitments',
    'actual_disbursements' => 'Total Disbursements',
    'activities_count' => 'Total Activities',
  );

  $build = array();

  // If it is not published (we don't make the call, and we render a custom version of the block).
  if (empty($entity->status) || $entity->status == NODE_NOT_PUBLISHED) {
    $build = array(
      '#prefix' => '<div class="contentblock-unpublished empty-contentblock clearfix">',
      '#suffix' => '</div>',
    );
    $build['title'] = array(
      '#markup' => '<h3 class="contentblock-title">' . t('Activities Block - Not Published') . '</h3>',
    );
    $build['content'] = array(
      '#markup' => '<p>' . t('This block is unpublished. To re-enable it - click !here and publish it.', array(
          '!here' => l(t('here'), 'admin/settings/content-sections/' . $entity->machine_name)
        )) . '</p>',
    );
    return $build;
  }

  // Create the table headers.
  $populated_data_counter = 0;
  foreach ($info_blocks as $key => $label) {

    // Make sure we add only info-boxes with data.
    if (!empty($data[$key])) {
      $populated_data_counter++;
      $build[$key] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array(
            'infoblock',
            drupal_html_class($key),
          ),
        ),
      );

      $build[$key]['label'] = array(
        '#prefix' => '<h3 class="header">',
        '#suffix' => '</h3>',
        '#markup' => t($label),
      );

      $build[$key]['info'] = array(
        '#type' => 'container',
        '#children' => $data[$key],
        '#attributes' => array(
          'class' => array('info'),
        ),
      );
    }
  }

  // Add defaults.
  $build['#prefix'] = '<div class="contentblock-published clearfix spread-' . $populated_data_counter . '">';
  $build['#suffix'] = '</div>';

  return array('#markup' => drupal_render($build));
}

/**
 * Settings form for the 'Total Activities' fixed widget.
 */
function contentwidget_totalactivities_widget_settings($form, &$form_state, $plugin, $widget_settings) {
  // Include this file, so that submit form works correctly.
  ctools_form_include_file($form_state, $plugin['path'] . '/' . $plugin['file']);

  // Let's allow users to select widget-related amount formatting.
  $amount_units_settings = _ampapi_activity_get_api_settings('amount-format:number-divider');
  $amount_units_options = array();
  foreach ($amount_units_settings->value->options as $delta => $amount_unit_option) {
    $amount_units_options[$amount_unit_option->id] = $amount_unit_option->name;
  }
  $form['amount_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Amount Options'),
    '#description' => t("These options change the widget amount formatting for the numeric output."),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight' => 10
  );
  $form['amount_settings']['widget_amount'] = array(
    '#type' => 'select',
    '#title' => t('Widget Amount Units'),
    '#options' => $amount_units_options,
    '#default_value' => isset($widget_settings['amount-units']) ? $widget_settings['amount-units'] : 'amountUnits1',
    '#description' => t('Please specify which widget-based amount formatting option you would like to use.'),
  );
  $form['amount_settings']['widget_amount_label_type'] = array(
    '#type' => 'radios',
    '#title' => t('Amount Units Type'),
    '#options' => array('short' => t('Short'), 'long' => t('Long')),
    '#default_value' => isset($widget_settings['amount-units-label-type']) ? $widget_settings['amount-units-label-type'] : 'short',
    '#description' => t('Please specify format would you like to use.<br />Short Example: M; Long Example: Millions.'),
  );
  $form['amount_settings']['widget_amount_fraction_digits'] = array(
    '#type' => 'select',
    '#title' => t('Fraction Digits'),
    '#options' => array('0' => t('0 Digits (No digits)'), '1' => t('1 Digits'), '2' => t('2 Digits'), '3' => t('3 Digits')),
    '#default_value' => isset($widget_settings['amount-fraction-digits']) ? $widget_settings['amount-fraction-digits'] : '3',
    '#description' => t('Please specify how many digits after the Decimal Symbol (Fraction Digits) you would like to display.'),
  );

  // Build the Extra settings, we need to figure out what we want to show.
  $form['extra_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Additional Settings'),
    '#collapsible' => FALSE,
    '#weight' => 15,
  );
  $form['extra_settings']['enable_commitments'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Commitments'),
    '#description' => t('If you want to disable the commitments totals, uncheck this box.'),
    '#default_value' => isset($widget_settings['enable_commitments']) ? $widget_settings['enable_commitments'] : TRUE,
  );
  $form['extra_settings']['enable_disbursements'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Disbursements'),
    '#description' => t('If you want to disable the disbursements totals, uncheck this box.'),
    '#default_value' => isset($widget_settings['enable_disbursements']) ? $widget_settings['enable_disbursements'] : TRUE,
  );

  // Disable some options based on the API functionality.
  $funding_type = _ampapi_activity_get_api_settings('funding-type');
  $flat_funding_types = array();
  foreach ($funding_type->value->options as $opt_delta => $option) {
    $flat_funding_types[] = $option->id;
  }
  if (!in_array('Actual Commitments', $flat_funding_types)) {
    $form['extra_settings']['enable_commitments']['#disabled'] = TRUE;
    $form['extra_settings']['enable_commitments']['#default_value'] = FALSE;
    $form['extra_settings']['enable_commitments']['#description'] = t('This functionality is disabled on the API.');
  }
  if (!in_array('Actual Disbursements', $flat_funding_types)) {
    $form['extra_settings']['enable_disbursements']['#disabled'] = TRUE;
    $form['extra_settings']['enable_disbursements']['#default_value'] = FALSE;
    $form['extra_settings']['enable_disbursements']['#description'] = t('This functionality is disabled on the API.');
  }

  $form['#submit'][] = 'contentwidget_totalactivities_widget_settings_submit';

  return $form;
}

/**
 * Widget form submit handler.
 *
 * This is where we basically put everything into a standard variable.
 */
function contentwidget_totalactivities_widget_settings_submit($form, $form_state) {
  $entity = $form['#entity'];

  $values = $form_state['values'];
  $amount = $values['widget_amount'];
  $fraction_digits = $values['widget_amount_fraction_digits'];
  $label_type = $values['widget_amount_label_type'];

  $data['amount-units'] = $amount;
  $data['amount-units-label-type'] = $label_type;
  $data['amount-fraction-digits'] = $fraction_digits;
  $data['enable_commitments'] = $values['enable_commitments'];
  $data['enable_disbursements'] = $values['enable_disbursements'];

  _contentwidget_fixed_set_settings($entity->machine_name, $data);
}
