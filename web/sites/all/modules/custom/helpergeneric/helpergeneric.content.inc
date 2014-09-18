<?php

/**
 * @file
 * This file contains settings form functions.
 */

/**
 * Page callback for 'admin/settings/page-content/homepage'.
 */
function helpergeneric_homepage_content_settings_form($form) {
  $form = array();

  return system_settings_form($form);
}

/**
 * Page callback for 'admin/settings/page-content/blog'.
 */
function helpergeneric_blog_content_settings_form($form) {
  $form = array();

  return system_settings_form($form);
}
