<?php
/**
 * @file
 * ampreports.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ampreports_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_dpi';
  $strongarm->value = '96';
  $export['pdf_using_mpdf_dpi'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_img_dpi';
  $strongarm->value = '96';
  $export['pdf_using_mpdf_img_dpi'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_margin_bottom';
  $strongarm->value = '16';
  $export['pdf_using_mpdf_margin_bottom'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_margin_footer';
  $strongarm->value = '9';
  $export['pdf_using_mpdf_margin_footer'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_margin_header';
  $strongarm->value = '9';
  $export['pdf_using_mpdf_margin_header'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_margin_left';
  $strongarm->value = '15';
  $export['pdf_using_mpdf_margin_left'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_margin_right';
  $strongarm->value = '15';
  $export['pdf_using_mpdf_margin_right'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_margin_top';
  $strongarm->value = '16';
  $export['pdf_using_mpdf_margin_top'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_pdf_css_file';
  $strongarm->value = 'styles/mpdf.css';
  $export['pdf_using_mpdf_pdf_css_file'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_pdf_default_font';
  $strongarm->value = 'DejaVuSerif';
  $export['pdf_using_mpdf_pdf_default_font'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_pdf_filename';
  $strongarm->value = '[site:name] - [node:title] - [node:changed:custom:Y-m-d]';
  $export['pdf_using_mpdf_pdf_filename'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_pdf_font_size';
  $strongarm->value = '10';
  $export['pdf_using_mpdf_pdf_font_size'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_pdf_footer';
  $strongarm->value = '';
  $export['pdf_using_mpdf_pdf_footer'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_pdf_header';
  $strongarm->value = '';
  $export['pdf_using_mpdf_pdf_header'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_pdf_page_size';
  $strongarm->value = 'A4';
  $export['pdf_using_mpdf_pdf_page_size'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_pdf_password';
  $strongarm->value = '';
  $export['pdf_using_mpdf_pdf_password'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_pdf_save_option';
  $strongarm->value = '1';
  $export['pdf_using_mpdf_pdf_save_option'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_pdf_set_author';
  $strongarm->value = '';
  $export['pdf_using_mpdf_pdf_set_author'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_pdf_set_creator';
  $strongarm->value = '';
  $export['pdf_using_mpdf_pdf_set_creator'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_pdf_set_subject';
  $strongarm->value = '';
  $export['pdf_using_mpdf_pdf_set_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_pdf_set_title';
  $strongarm->value = '';
  $export['pdf_using_mpdf_pdf_set_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_pdf_watermark_text';
  $strongarm->value = '';
  $export['pdf_using_mpdf_pdf_watermark_text'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_type_blog';
  $strongarm->value = 0;
  $export['pdf_using_mpdf_type_blog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_type_page';
  $strongarm->value = 0;
  $export['pdf_using_mpdf_type_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_type_slide';
  $strongarm->value = 0;
  $export['pdf_using_mpdf_type_slide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_watermark_image';
  $strongarm->value = 0;
  $export['pdf_using_mpdf_watermark_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_watermark_opacity';
  $strongarm->value = '0.5';
  $export['pdf_using_mpdf_watermark_opacity'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pdf_using_mpdf_watermark_option';
  $strongarm->value = 'text';
  $export['pdf_using_mpdf_watermark_option'] = $strongarm;

  return $export;
}
