<?php

/**
 * An overridden version of the theme function specifically for the PDF export.
 */
function theme_views_data_export_reports_body(&$vars) {
  // Here we just took _views_data_export_header_shared_preprocess and made sure
  // it uses translated labels instead of the labels of the fields.
  $view     = $vars['view'];
  $fields   = &$view->field;
  $output = '';

  $vars['header'] = array();
  foreach ($fields as $key => $field) {
    if (empty($field->options['exclude'])) {
      $vars['header'][$key] = check_plain($field->label());
    }
  }

  // And now we call the standard body-shared function.
  _views_data_export_body_shared_preprocess($vars);

  // Decode HTML entities.
  $complete_array = $vars['themed_rows'];
  foreach ($complete_array as &$row) {
    foreach ($row as &$value) {
      $value = decode_entities($value);
    }
  }

  $output  .= $view->display_handler->render_area('header', FALSE);

  // Try to get and load the file.
  $input_hash = md5(implode(':', $view->exposed_input));
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'file')
    ->propertyCondition('filename', $input_hash . '.png');
  $result = $query->execute();
  if (!empty($result['file'])) {
    $files = entity_load('file', array_keys($result['file']));
    if (!empty($files)) {
      $file = reset($files);
      $image = theme_image(array(
        'path' => $file->uri,
        'width' => '100%',
        'height' => 'auto',
        'alt' => t('Projects graph'),
        'title' => t('Projects graph'),
        'attributes' => array(),
      ));
    }
  }
  $output .= '<div style="text-align: center;">' . $image . '</div>';

  $header = $vars['header'];
  unset($header['title']);
  unset($header['description']);
  foreach ($complete_array as $item) {
    // Use title outside of the table.
    if (!empty($item['title'])) {
      $output .= '<h3>' . $item['title'] . '</h3>';
    }
    // Then unset it, so it won't go into the table cells.
    unset($item['title']);

    // Same goes for the description.
    if (!empty($item['description'])) {
      $output .= '<p>' . $item['description'] . '</p>';
    }
    unset($item['description']);

    // Now we want to nicely print a table with header and a single-row body.
    $output .= theme('table', array(
      'header' => $header,
      'rows' => array($item),
      'sticky' => FALSE,
    ));
  }

  return $output;
}

/**
 * Implements temmplate_preprocess_HOOK().
 */
function template_preprocess_views_data_export_reports(&$vars) {
  $vars['header'] = $vars['rows']['header'];
  $vars['body'] = $vars['rows']['body'];
  $vars['footer'] = $vars['rows']['footer'];

  $view     = $vars['view'];
  $fields   = &$view->field;
}
