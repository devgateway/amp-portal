<?php

/**
 * @file
 * Provides a custom Total Pledges widget.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'hidden' => TRUE,
  'title' => 'Total Pledges',
  'description' => 'Will display the total pledges, related commitments, disbursements and the total number of related activities in system.',
  'render callback' => 'contentwidget_totalpledges_widget_render',
  'settings form' => 'contentwidget_totalpledges_widget_settings',
  'settings storage' => 'contentwidget_totalpledges_widget_settings_storage',
  'resource api path' => array(
    'report' => 'data/report/custom/paginate',
    'activities' => 'public/activitiesPledges',
  ),
  'defaults' => array(
  ),
);

/**
 * Retrieves data from the report endpoint.
 */
function contentwidget_totalpledges_widget_retrieve_report_data($plugin, $widget_settings, $langcode = NULL) {
  global $language;
  $api_status = ampAPIRestClient::status();
  if (!$api_status['online']) {
    return array();
  }

  $langcode = (empty($langcode) ? LANGUAGE_NONE : $langcode);
  $cache_id = "contentblock:widget:{$langcode}:totalpledges:" . $language->language . ':' . md5(serialize($widget_settings));

  $amount_units_key = isset($widget_settings['amount-units']) ? $widget_settings['amount-units'] : 'amount-units-1';
  $amount_fraction_digits = isset($widget_settings['amount-fraction-digits']) ? $widget_settings['amount-fraction-digits'] : 3;
  $amount_units_settings = _ampapi_activity_get_api_settings('amount-format:number-divider');
  $amount_units_options = array();
  foreach ($amount_units_settings->value->options as $delta => $amount_unit_option) {
    $amount_units_options[$amount_unit_option->id] = $amount_unit_option;
  }
  $amount_units = $amount_units_options[$amount_units_key];

  // Try to get the response from cache.
  $report_totals = array();

  // Try to get the processed response from cache.
  if ($cached = cache_get($cache_id, 'cache')) {
    return $cached->data;
  }

  // Prepare a list of parameters for the request.
  $options = array();
  $options['headers'] = array(
    'Accept' => 'application/json',
    'Content-Type' => 'application/json',
  );

  $request_body = array();

  // Note: Because we don't use these as fields, we require no mappings so far,
  // that's why we just use the plain values without ctools plugins.
  $request_body['add_columns'][] = 'Related Projects';
  $request_body['add_columns'][] = 'Pledges Titles';

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

  // Also, we don't use the mapper plugin because so far it's not needed.
  if ((isset($widget_settings['enable_pledges']) && $widget_settings['enable_pledges'] == TRUE)
    || !isset($widget_settings['enable_pledges'])) {
    $request_body['add_measures'][] = 'Actual Pledge';
  }

  $request_body['page'] = 1;
  $request_body['recordsPerPage'] = -1;
  $request_body['regenerate'] = TRUE;
  $request_body['rowTotals'] = TRUE;
  $request_body['raw_values'] = array('M');
  $request_body['reportType'] = 'P';
  $request_body['name'] = 'api:totalpledges';

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
  $response_data = ampAPIRestClient::post($plugin['resource api path']['report'], $options, $use_cache);

  if (empty($response_data)) {
    return array();
  }

  // Get the number formatting pattern.
  $currency_setting = _ampapi_activity_get_api_settings('currency-code');
  $currency = $currency_setting->value->defaultId;

  // There's a case (for now) when API returns wrong data, we should handle it.
  $report_totals = array();
  if (isset($response_data->headers)) {
    foreach ($response_data->headers as $h_info) {
      // @TODO: use mappers.
      if (!in_array($h_info->hierarchicalName, array('[Totals][Actual Pledge]', '[Totals][Actual Commitments]', '[Totals][Actual Disbursements]'))) {
        continue;
      }

      /** @noinspection PhpUndefinedFieldInspection */
      if (!isset($response_data->page->pageArea->contents->{$h_info->hierarchicalName}->value)) {
        continue;
      }

      // Now, we really trust the API display values.
      if (!empty($widget_settings['amount-label'][$language->language])) {
        $amount_units_label = $widget_settings['amount-label'][$language->language];
      }
      elseif (isset($widget_settings['amount-units-label-type'])) {
        $amount_units_label = filter_xss(_ampapi_amount_unit_get_label($amount_units->id, $widget_settings['amount-units-label-type']));
      }
      else {
        $amount_units_label = filter_xss(_ampapi_amount_unit_get_label($amount_units->id, 'long'));
      }

      /** @noinspection PhpUndefinedFieldInspection */
      $amount = check_plain($response_data->page->pageArea->contents->{$h_info->hierarchicalName}->displayedValue);
      $amount = '<span class="amount">' . $amount . '</span> ';
      if ($language->direction == 0) {
        $amount .= '<span class="text">' . t('@amount_units !currencysymbol', array(
            '!currencysymbol' => $currency,
            '@amount_units' => $amount_units_label
          )) . '</span>';
      }
      else {
        $amount .= '<span class="text">' . t('!currencysymbol @amount_units', array(
            '!currencysymbol' => $currency,
            '@amount_units' => $amount_units_label
          )) . '</span>';
      }

      switch ($h_info->hierarchicalName) {
        case '[Totals][Actual Pledge]':
          $report_totals['actual_pledge'] = $amount;
          break;
        case '[Totals][Actual Commitments]':
          $report_totals['actual_commitments'] = $amount;
          break;
        case '[Totals][Actual Disbursements]':
          $report_totals['actual_disbursements'] = $amount;
          break;
      }
    }
  }
  else {
    $report_totals['actual_pledge'] = '<span class="text">' . t('Not Available') . '</span>';
    $report_totals['actual_commitments'] = '<span class="text">' . t('Not Available') . '</span>';
    $report_totals['actual_disbursements'] = '<span class="text">' . t('Not Available') . '</span>';
  }

  // 1 hours cache life time for requests should be plenty for now.
  $expire = 3600;
  cache_set($cache_id, $report_totals, 'cache', REQUEST_TIME + $expire);

  return $report_totals;
}

/**
 * Retrieves data from the pledge activities endpoint.
 */
function contentwidget_totalpledges_widget_retrieve_activities_data($plugin, $widget_settings, $langcode = NULL) {
  $api_status = ampAPIRestClient::status();
  if (!$api_status['online']) {
    return array();
  }

  $langcode = (empty($langcode) ? LANGUAGE_NONE : $langcode);
  $cache_id = "contentblock:widget:{$langcode}:totalpledges-activities:" . md5(serialize($widget_settings));

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

  // Get the API settings.
  $api_settings = helpergeneric_get_api_settings();

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
  $response_data = ampAPIRestClient::post($plugin['resource api path']['activities'], $options, $use_cache);

  if (empty($response_data)) {
    return array();
  }

  $pledge_activities = array();

  if ((isset($widget_settings['enable_totalactivities']) && $widget_settings['enable_totalactivities'] == TRUE)
    || !isset($widget_settings['enable_totalactivities'])) {
    if (isset($response_data->ActivitiesWithPledgesCount)) {
      $pledge_activities['pledge_activities'] = '<span class="amount">' . intval($response_data->ActivitiesWithPledgesCount) . '</span>';
    }
    else {
      $pledge_activities = '<span class="amount">' . 0 . '</span>';
    }
  }

  // 1 hours cache life time for requests should be plenty for now.
  $expire = 3600;
  cache_set($cache_id, $pledge_activities, 'cache', REQUEST_TIME + $expire);

  return $pledge_activities;
}

/**
 * Render callback for the 'Top Pledges' predefined widget.
 */
function contentwidget_totalpledges_widget_render($plugin, $widget_settings, $entity, $langcode) {
  // Provide some default values.
  $widget_settings += $plugin['defaults'];

  // We need to fail-quickly if the settings says that the pledges are disabled on the API's end.
  $funding_type = _ampapi_activity_get_api_settings('funding-type');
  $flat_funding_types = array();
  foreach ($funding_type->value->options as $opt_delta => $option) {
    $flat_funding_types[] = $option->id;
  }

  // Make the queries only if the entity is published.
  if ($entity->status == NODE_PUBLISHED && in_array('Actual Pledge', $flat_funding_types)) {
    $data = contentwidget_totalpledges_widget_retrieve_report_data($plugin, $widget_settings, $langcode);
    $data_activities = contentwidget_totalpledges_widget_retrieve_activities_data($plugin, $widget_settings, $langcode);

    if (!empty($data) && !empty($data_activities)) {
      $data = array_merge($data, $data_activities);
    }
    elseif (!empty($data_activities)) {
      $data = $data_activities;
    }

    if (empty($data)) {
      return '';
    }
  }

  $info_blocks = array(
    'actual_pledge' => 'Total Pledges',
    'actual_commitments' => 'Total Commitments',
    'actual_disbursements' => 'Total Disbursements',
    'pledge_activities' => 'Pledge Activities',
  );

  $build = array();

  // If it is not published (we don't make the call(s), and we render a custom version of the block).
  if (empty($entity->status) || $entity->status == NODE_NOT_PUBLISHED) {
    $build = array(
      '#prefix' => '<div class="contentblock-unpublished empty-contentblock clearfix">',
      '#suffix' => '</div>',
    );
    $build['title'] = array(
      '#markup' => '<h3 class="contentblock-title">' . t('Pledges Block - Not Published') . '</h3>',
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
 * Settings form for the 'Total Pledges' fixed widget.
 */
function contentwidget_totalpledges_widget_settings($form, &$form_state, $plugin, $widget_settings) {
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
    '#default_value' => isset($widget_settings['amount-units']) ? $widget_settings['amount-units'] : 'amount-units-1',
    '#description' => t('Please specify which widget-based amount formatting option you would like to use.'),
  );
  $form['amount_settings']['widget_amount_label_type'] = array(
    '#type' => 'radios',
    '#title' => t('Amount Units Type'),
    '#options' => array('short' => t('Short'), 'long' => t('Long'), 'override' => t('Custom')),
    '#default_value' => isset($widget_settings['amount-units-label-type']) ? $widget_settings['amount-units-label-type'] : 'short',
    '#description' => t('Please specify format would you like to use.<br />Short Example: M; Long Example: Millions.'),
    '#states' => array(
      'invisible' => array(
        ':input[name="widget_amount"]' => array('value' => 'amount-units-1'),
      ),
    ),
  );
  // Prepare the overriding part of the labels.
  // Get values first.
  $amount_unit = isset($form_state['values']['widget_amount']) ? $form_state['values']['widget_amount'] : $widget_settings['amount-units'];
  $label_default = _ampapi_amount_unit_get_label($amount_unit, 'short');

  $form['amount_settings']['widget_amount_label_override'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom Amount Labels'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name="widget_amount_label_type"]' => array('value' => 'override'),
      ),
      'invisible' => array(
        ':input[name="widget_amount"]' => array('value' => 'amount-units-1'),
      ),
    )
  );
  if (drupal_multilingual()) {
    $languages = language_list();
    foreach ($languages as $lang_id => $language) {
      if ($language->enabled) {
        $form['amount_settings']['widget_amount_label_override']['widget_amount_label_' . $lang_id] = array(
          '#type' => 'textfield',
          '#title' => t('Override Amount (@lang)', array('@lang' => $language->name)),
          '#default_value' => isset($widget_settings['amount-label'][$lang_id]) ? $widget_settings['amount-label'][$lang_id] : $label_default,
          '#size' => 30,
        );
      }
    }
  }

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
    '#description' => t('Please make sure you leave at least 1 option enabled.'),
  );
  $form['extra_settings']['enable_pledges'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Pledges'),
    '#description' => t('If you want to disable the pledges totals, uncheck this box.'),
    '#default_value' => isset($widget_settings['enable_pledges']) ? $widget_settings['enable_pledges'] : TRUE,
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
  $form['extra_settings']['enable_totalactivities'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Total Activities'),
    '#description' => t('If you want to disable the activities totals, uncheck this box.'),
    '#default_value' => isset($widget_settings['enable_totalactivities']) ? $widget_settings['enable_totalactivities'] : TRUE,
  );

  // Disable some options based on the API functionality.
  $funding_type = _ampapi_activity_get_api_settings('funding-type');
  $flat_funding_types = array();
  foreach ($funding_type->value->options as $opt_delta => $option) {
    $flat_funding_types[] = $option->id;
  }
  if (!in_array('Actual Pledge', $flat_funding_types)) {
    $form['extra_settings']['enable_pledges']['#disabled'] = TRUE;
    $form['extra_settings']['enable_pledges']['#default_value'] = FALSE;
    $form['extra_settings']['enable_pledges']['#description'] = t('This functionality is disabled on the API.');
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

  $form['#validate'][] = 'contentwidget_totalpledges_widget_settings_validate';
  $form['#submit'][] = 'contentwidget_totalpledges_widget_settings_submit';

  return $form;
}

/**
 * The custom validation of the form.
 */
function contentwidget_totalpledges_widget_settings_validate($form, $form_state) {
  // Check if user has unchecked all of the measures - and don't allow him to do that.
  $values = $form_state['values'];
  if ($values['enable_pledges'] == FALSE && $values['enable_commitments'] == FALSE
    && $values['enable_disbursements'] == FALSE && $values['enable_totalactivities'] == FALSE) {
    form_set_error('extra_settings', t('You have disabled all options under Extra Settings, make sure you have at least 1 option enabled.'));
  }
}


/**
 * Widget form submit handler.
 *
 * This is where we basically put everything into a standard variable.
 */
function contentwidget_totalpledges_widget_settings_submit($form, $form_state) {
  $entity = $form['#entity'];

  $values = $form_state['values'];
  $amount = $values['widget_amount'];
  $fraction_digits = $values['widget_amount_fraction_digits'];
  $label_type = $values['widget_amount_label_type'];
  $langcode = $values['language'];

  $data['amount-units'] = $amount;
  $data['amount-units-label-type'] = $label_type;
  $data['amount-fraction-digits'] = $fraction_digits;
  $data['enable_pledges'] = $values['enable_pledges'];
  $data['enable_commitments'] = $values['enable_commitments'];
  $data['enable_disbursements'] = $values['enable_disbursements'];
  $data['enable_totalactivities'] = $values['enable_totalactivities'];

  if ($data['amount-units'] == 'amount-units-1') {
    $data['amount-units-label-type'] = '';
  }

  // Fix the custom labels.
  if ($data['amount-units'] !== 'amount-units-1' && $label_type == 'override') {
    if (drupal_multilingual()) {
      $languages = language_list();
      foreach ($languages as $lang_id => $language) {
        if ($language->enabled) {
          $data['amount-label'][$lang_id] = $values['widget_amount_label_' . $lang_id];
        }
      }
    }
  }
  else {
    $data['amount-label'] = array();
  }

  // Forcefully clear this widget's cache.
  $langcode = (empty($langcode) ? LANGUAGE_NONE : $langcode);
  $cache_id = "contentblock:widget:{$langcode}:totalpledges:";
  cache_clear_all($cache_id, 'cache', TRUE);


  _contentwidget_fixed_set_settings($entity->machine_name, $data);
}
