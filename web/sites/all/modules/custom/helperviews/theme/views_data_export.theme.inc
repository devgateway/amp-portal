<?php

function theme_views_data_export_pdf_body(&$vars) {
  _views_data_export_header_shared_preprocess($vars);
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
  foreach ($complete_array as $row) {
    if (!empty($row['title'])) {
      $output .= '<h3>' . $row['title'] . '</h3>';
      unset($row['title']);
    }
    if (!empty($row['description'])) {
      $output .= '<p>' . $row['description'] . '</p>';
      unset($row['description']);
    }

    $output .= theme('table', array('header' => $header, 'rows' => array($row)));
  }
  return $output;
}
