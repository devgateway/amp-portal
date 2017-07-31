<?php

/**
 * An overridden version of the theme function specifically for the PDF export.
 */
function theme_views_data_export_pdf_body(&$vars) {
  // Here we just took _views_data_export_header_shared_preprocess and made sure
  // it uses translated labels instead of the labels of the fields.
  $view     = $vars['view'];
  $fields   = &$view->field;

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

  $output = '';
  $header = $vars['header'];
  unset($header['title']);
  unset($header['description']);
  foreach ($complete_array as $item) {
    if (!empty($item['title'])) {
      $output .= '<h3>' . $item['title'] . '</h3>';
      unset($item['title']);
    }
    if (!empty($item['description'])) {
      $output .= '<p>' . $item['description'] . '</p>';
      unset($item['description']);
    }
    $output .= theme('table', array(
      'header' => $header,
      'rows' => array($item),
      'sticky' => FALSE,
    ));
  }

  return $output;
}
