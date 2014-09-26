<?php

/**
 * @file
 * This file contains settings form functions.
 */

/**
 * Page callback for 'admin/settings/static-content/map'.
 */
function helpergeneric_map_content_settings_form($form, &$form_state) {
  $widget_settings = variable_get('helpergeneric_map_widget_settings', array());
  $form_state['original_widget_settings'] = $widget_settings;

  $form['url'] = array(
    '#type' => 'textfield',
    '#title' => t('Map page URL'),
    '#description' => t('Please provide an URL to the map page.'),
    '#default_value' => isset($widget_settings['url']) ? $widget_settings['url'] : NULL,
  );

  $form['image'] = array(
    '#type' => 'fieldset',
    '#title' => t('Image'),
    '#description' => t('Image to use for the "Explore the map" widget.'),
  );

  $default_image = NULL;
  if (!empty($widget_settings['image_fid'])) {
    $default_image = file_load($widget_settings['image_fid']);
  }

  if (!empty($default_image)) {
    $form['image']['action'] = array(
      '#type' => 'radios',
      '#title' => t('Action'),
      '#default_value' => 'keep',
      '#options' => array(
        'keep' => 'Keep existing image',
        'remove' => 'Remove existing image',
        'replace' => 'Replace existing image',
      ),
    );

    $form['image']['preview'] = array(
      '#type' => 'container',
      '#states' => array(
        'visible' => array(
          'input[name="action"]' => array('value' => 'keep'),
        ),
      ),
    );
    $form['image']['preview']['thumbnail'] = array(
      '#markup' => _helpergeneric_map_image_preview($default_image),
    );
  }


  $form['image']['image_upload'] = array(
    '#type' => 'file',
    '#title' => t('Map Image'),
    '#maxlength' => 40,
    '#description' => t('Use this field to upload an image for the map widget.'),
  );

  // Only show the form when we want to replace the image..
  if (!empty($default_image)) {
    $form['image']['image_upload']['#states']['visible'] = array(
      'input[name="action"]' => array('value' => 'replace'),
    );

    // Using the "required" state doesn't seem to work, only marks the field as required.
    $form['image']['image_upload']['#states']['required'] = array(
      'input[name="action"]' => array('value' => 'replace'),
    );
  }
  else {
    // Using the "required" state doesn't seem to work, only marks the field as required.
    $form['image']['image_upload']['#states']['required'] = array(
      'input[name="url"]' => array('empty' => FALSE),
    );
  }

  // // Only show the form when we already have a default image.
  // $default_alt_image = NULL;
  // if (!empty($widget_settings['alternative_fid'])) {
  //   $default_alt_image = file_load($widget_settings['alternative_fid']);
  // }
  // if (!empty($default_image)) {
  //   $form['altimage'] = array(
  //     '#type' => 'fieldset',
  //     '#title' => t('Homepage Alternative Image'),
  //     '#description' => t('Use an alternative image only if the default one does not look good in the wide homepage "Explore the map" widget.'),
  //     '#collapsible' => TRUE,
  //     '#collapsed' => TRUE,
  //   );

  //   if (empty($default_alt_image)) {
  //     $form['altimage']['use_alternative'] = array(
  //       '#type' => 'checkbox',
  //       '#title' => t('Use alternative image on the homepage widget'),
  //       '#default_value' => isset($widget_settings['alternative_upload']) ? TRUE : FALSE,
  //     );
  //   }
  //   else {
  //     $form['altimage']['#collapsed'] = FALSE;
  //     $form['altimage']['replace_alt_image'] = array(
  //       '#type' => 'checkbox',
  //       '#title' => t('Replace existing alternative image.'),
  //       '#default_value' => FALSE,
  //     );
  //     $form['altimage']['remove_alt_image'] = array(
  //       '#type' => 'checkbox',
  //       '#title' => t('Remove existing alternative image.'),
  //       '#default_value' => FALSE,
  //     );
  //   }

  //   $form['altimage']['alternative_upload'] = array(
  //     '#type' => 'file',
  //     '#title' => t('Alternative Image on homepage'),
  //     '#maxlength' => 40,
  //     '#description' => t('Use this field to upload an alternative image for the homepage map widget.'),
  //     '#default_value' => isset($widget_settings['alternative_upload']) ? $widget_settings['alternative_upload'] : NULL,
  //     '#states' => array(
  //       // Hide the logo settings when using the default logo.
  //       'visible' => array(
  //         'input[name="use_alternative"]' => array('checked' => TRUE),
  //       ),
  //     ),
  //   );

  //   // Only show the form when we want to replace the image..
  //   if (!empty($default_alt_image)) {
  //     $form['altimage']['alternative_upload']['#states']['visible'] = array(
  //       'input[name="replace_alt_image"]' => array('checked' => TRUE),
  //     );
  //   }
  // }


  $form['#validate'][] = 'helpergeneric_map_content_settings_form_validate';
  $form['#submit'][] = 'helpergeneric_map_content_settings_form_submit';


  // @see system_settings_form()
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'));

  if (!empty($_POST) && form_get_errors()) {
    drupal_set_message(t('The settings have not been saved because of the errors.'), 'error');
  }
  // By default, render the form using theme_system_settings_form().
  if (!isset($form['#theme'])) {
    $form['#theme'] = 'system_settings_form';
  }

  return $form;
}

function _helpergeneric_map_image_preview($file) {
  $output = '';

  // Set up preview file information.
  $style = image_style_load('media_thumbnail');
  $preview_file = image_style_path($style['name'], $file->uri);
  if (!file_exists($preview_file)) {
    image_style_create_derivative($style, $file->uri, $preview_file);
  }

  // Build the preview of the original image.
  $output .= '<div class="preview-image-wrapper field">';

  $preview_url = file_create_url($preview_file) . '?cache_bypass=' . REQUEST_TIME;
  $output .= '<div class="preview-image">';
  $output .= theme('image', array('path' => $preview_url, 'alt' => t('Sample modified image'), 'title' => ''));
  $output .= '</div>'; // End preview-image.

  $original_url = file_create_url($file->uri);
  $output .= '<div class="original-image">';
  $output .= l(t('view original size'), $original_url, array('attributes' => array('target' => '_blank')));
  $output .= '</div>'; // End original-image.

  $output .= '</div>'; // End preview-image-wrapper.

  return $output;
}
/**
 * Validation callback for helpergeneric_map_content_settings_form().
 *
 * @TODO: Handle language validation.
 */
function helpergeneric_map_content_settings_form_validate($form, &$form_state) {
  // Validate the link.
  $url = link_cleanup_url($form_state['values']['url']);
  $url_parts = _link_parse_url($url);
  if (!empty($url_parts['url'])) {
    $type = link_validate_url($url_parts['url']);

    if ($type == LINK_EXTERNAL) {
      $args = array(
        '%good_example' => '/path-to-resource',
        '%wrong_example' => 'http://example.org/path-to-resource',
      );
      form_set_error('url', t('An absolute path (without a domain) is required. Provide a value like %good_example instead of %wrong_example.', $args));
    }
    else if (substr($url_parts['url'], 0, 1) != '/') {
      $args = array(
        '%good_example' => '/path-to-resource',
        '%wrong_example' => 'path-to-resource',
      );
      form_set_error('url', t('An absolute path (without a domain) is required. Provide a value like %good_example instead of %wrong_example.', $args));
    }
    else {
      $cleaned_url = url($url_parts['url'],
        array(
          'query' => isset($url_parts['query']) ? $url_parts['query'] : NULL,
          'fragment' => isset($url_parts['fragment']) ? $url_parts['fragment'] : NULL,
          'absolute' => TRUE,
          'external' => TRUE, // We don't want to prepend Drupal's $base_path.
        )
      );

      // Update the value to save.
      $form_state['values']['url'] = $cleaned_url;
    }
  }

  // Handle file uploads.
  $validators = array(
    'file_validate_is_image' => array(),
    'file_validate_extensions' => array('png jpg jpeg')
  );

  // Validate the image file and save the file to Drupal's temporary files scheme.
  $image_file = file_save_upload('image_upload', $validators);
  if (isset($image_file)) {
    // File upload was attempted.
    if ($image_file) {
      // Put the temporary file in form_values so we can save it on submit.
      $form_state['values']['image_upload'] = $image_file;
    }
    else {
      // File upload failed.
      form_set_error('image_upload', t('The file could not be uploaded.'));
    }
  }

  $image_upload_required = FALSE;
  if (!isset($form_state['values']['action']) && !empty($form_state['values']['url'])) {
    $image_upload_required = TRUE;
  }
  if (!empty($form_state['values']['action']) && $form_state['values']['action'] == 'replace') {
    $image_upload_required = TRUE;
  }
  if ($image_upload_required && empty($form_state['values']['image_upload'])) {
    form_set_error('image_upload', t('!name field is required.', array('!name' => $form['image']['image_upload']['#title'])));
  }

  // Validate the alternative image file and save the file to Drupal's temporary files scheme.
  // $alt_image_file = file_save_upload('alternative_upload', $validators);
  // if (isset($alt_image_file)) {
  //   // File upload was attempted.
  //   if ($alt_image_file) {
  //     // Put the temporary file in form_values so we can save it on submit.
  //     $form_state['values']['alternative_upload'] = $alt_image_file;
  //   }
  //   else {
  //     // File upload failed.
  //     form_set_error('alternative_upload', t('The file could not be uploaded.'));
  //   }
  // }
}
/**
 * Process system_theme_settings form submissions.
 */
function helpergeneric_map_content_settings_form_submit($form, &$form_state) {
  $orig_settings = $form_state['original_widget_settings'];

  // return;

  $widget_settings = array(
    'url' => $form_state['values']['url'],
  );

  $action = isset($form_state['values']['action']) ? $form_state['values']['action'] : NULL;
  if (!isset($action) || $action == 'replace') {
    if (!empty($form_state['values']['image_upload'])) {
      $scheme = variable_get('file_default_scheme', 'public') . '://';
      $uri = file_stream_wrapper_uri_normalize($scheme . $form_state['values']['image_upload']->filename);
      $file = file_move($form_state['values']['image_upload'], $uri, FILE_EXISTS_RENAME);

      if ($file) {
        $widget_settings['image_fid'] = $form_state['values']['image_upload']->fid;
      }
    }
  }
  else if ($action == 'keep') {
    $widget_settings['image_fid'] = $form_state['original_widget_settings']['image_fid'];
  }

  if ($action == 'remove' || $action == 'replace') {
    // Remove existing file.
    $existing_file = file_load($form_state['original_widget_settings']['image_fid']);
    file_delete($existing_file);
  }

  // $save_new_alt_image = FALSE;
  // if (empty($form_state['values']['alt_action'])) {
  //   $save_new_alt_image = TRUE;
  // }
  // if (!empty($form_state['values']['alt_action']) && $form_state['values']['alt_action'] == 'replace') {
  //   $save_new_alt_image = TRUE;
  // }
  // if ($save_new_image && !empty($form_state['values']['alternative_upload'])) {
  //   if (!empty($form_state['values']['alternative_upload'])) {
  //     $filename = file_unmanaged_copy($form_state['values']['alternative_upload']->uri);
  //     $widget_settings['alternative_fid'] = $form_state['values']['alternative_upload']->fid;
  //   }
  // }

  if (!empty($widget_settings)) {
    variable_set('helpergeneric_map_widget_settings', $widget_settings);
  }
  else {
    variable_del('helpergeneric_map_widget_settings');
  }
}

/**
 * Page callback for 'admin/settings/static-content/homepage'.
 */
function helpergeneric_homepage_content_settings_form($form, &$form_state) {
  $varname = 'contentblock_blockref_homepage';
  _helpergeneric_cbreference_settings_form($varname, $form, $form_state);

  return system_settings_form($form);
}

/**
 * Page callback for 'admin/settings/static-content/blog'.
 */
function helpergeneric_blog_content_settings_form($form, &$form_state) {
  $varname = 'contentblock_blockref_blog';
  _helpergeneric_cbreference_settings_form($varname, $form, $form_state);

  return system_settings_form($form);
}

/**
 * Helper function for "static-content" forms.
 */
function _helpergeneric_cbreference_settings_form($varname, &$form, &$form_state) {
  $form = array();

  $table_header = array(t('Content Blocks'), t('Weight'), t('Style'));
  $columns_count = count($table_header);

  $form_state['varname'] = $varname;

  $form[$varname] = array(
    '#type' => 'table',
    '#header' => $table_header,
    // Optionally, to add tableDrag support:
    '#tabledrag' => array(
      array('order', 'sibling', 'entry-weight'),
    ),
    '#prefix' => '<div id="referenced-contentblocks">',
    '#suffix' => '</div>',
  );


  $blockref = variable_get($varname, array());
  $blockref = array_values($blockref);

  $styles = array(
    '' => t('Default'),
    'cbstyle' => t('Content Block'),
  );

  $count = 2;
  if (!empty($form_state['values'][$varname]) && count($form_state['values'][$varname]) >= 2) {
    $count = count($form_state['values'][$varname]) + 1;
  }
  else if (!empty($blockref) && count($blockref) >= 2) {
    $count = count($blockref) + 1;
  }

  for ($delta = 0; $delta < $count; $delta++) {
    if (isset($blockref[$delta]) && empty($blockref[$delta])) {
      continue;
    }

    if (!empty($blockref[$delta]['contentblock'])) {
      $entry = $blockref[$delta];
      if (!empty($entry['contentblock']) && is_numeric($entry['contentblock'])) {
        $entity = entity_load_single('contentblock', $entry['contentblock']);
        if (empty($entity)) {
          continue;
        }
        $contentblock_value = check_plain($entity->label()) . ' (' . $entity->identifier() . ')';
        $entry['contentblock'] = $contentblock_value;
      }
    }
    else {
      $entry = array(
        'contentblock' => '',
        'style' => '',
        'weight' => $delta,
      );
    }

    // TableDrag: Sort the table row according to its existing/configured weight.
    $form[$varname][$delta]['#weight'] = $entry['weight'];
    // TableDrag: Mark the table row as draggable.
    $form[$varname][$delta]['#attributes']['class'][] = 'draggable';
    $form[$varname][$delta]['#attributes']['class'][] = 'entry-region-main';

    // We'll manually set the #parents property of these fields so that
    // their values appear in the $form_state['values'][$property] array.
    $form[$varname][$delta]['contentblock'] = array(
      '#type' => 'textfield',
      '#title' => t('Content Block'),
      '#title_display' => 'invisible',
      '#default_value' => $entry['contentblock'],
      '#autocomplete_path' => 'helpergeneric/contentblock/autocomplete',
      '#element_validate' => array('_helpergeneric_contentblock_element_validate'),
    );

    // Add tableDrag support.
    $form[$varname][$delta]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#title_display' => 'invisible',
      '#default_value' => $entry['weight'],
      '#attributes' => array('class' => array('entry-weight')),
    );

    $form[$varname][$delta]['style'] = array(
      '#type' => 'select',
      '#title' => t('Style'),
      '#title_display' => 'invisible',
      '#default_value' => $entry['style'],
      '#options' => $styles,
      '#weight' => -10,
    );
  }

  // We name our button 'fbc_add' to avoid conflicts with other modules.
  $form['helperadd'] = array(
    '#type' => 'submit',
    '#value' => t('Add another item'),
    '#attributes' => array(
      'title' => t("If the amount of boxes above isn't enough, click here to add more."),
    ),
    '#weight' => 1,
    '#limit_validation_errors' => array(
      array($varname), // Only validate the referenced entities when using AHAH to update the form.
    ),
    '#submit' => array('_helpergeneric_helperadd_submit'),
    '#ajax' => array(
      'callback' => '_helpergeneric_ajax_form_references',
      'wrapper' => 'referenced-contentblocks',
      'effect' => 'fade',
    ),
  );

  // array_unshift($form['#submit'], 'helpergeneric_contentblock_submit');
  $form['#submit'][] = 'helpergeneric_contentblock_submit';
}

/**
 * Process system_theme_settings form submissions.
 */
function helpergeneric_contentblock_submit($form, &$form_state) {
  $varname = $form_state['varname'];
  $ref_values = &$form_state['values'][$varname];

  foreach ($ref_values as $key => $value) {
    if (empty($value['contentblock'])) {
      unset($ref_values[$key]);
    }
  }
}

/**
 * Form element validation handler for default group audience elements.
 */
function _helpergeneric_contentblock_element_validate($element, &$form_state) {
  preg_match('/\(([0-9]+)\)$/', $element['#value'], $matches);
  if (!empty($matches[1]) && is_numeric($matches[1])) {

    // It's not used that often, so we can load entity.
    $entity = entity_load_single('contentblock', $matches[1]);
    if (!empty($entity)) {
      form_set_value($element, $entity->identifier(), $form_state);
    }
    else {
      $args = array(
        '%value' => $element['#value'],
      );
      form_error($element, t('Content Block %value does not exist.', $args));
    }
  }
  elseif (!empty($element['#value'])) {
    $args = array(
      '%value' => $element['#value'],
    );
    form_error($element, t('"%value" is not a valid reference.', $args));
  }
}

/**
 * Submit handler to add more questions to the form.
 */
function _helpergeneric_helperadd_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback in response to new categories being added to the form.
 *
 * This returns the new page content to replace the page content made obsolete
 * by the form submission.
 *
 * @see _helpergeneric_helperadd_submit()
 */
function _helpergeneric_ajax_form_references($form, $form_state) {
  $varname = $form_state['varname'];
  return $form[$varname];
}
