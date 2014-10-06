<?php
/**
 * @file
 * This file contains view preprocess functions.
 */

/**
 * Implements template_preprocess_views_view().
 */
function ampcms_preprocess_views_view(&$variables) {
  $function = '__' . __FUNCTION__ . '__' . $variables['view']->name;
  if (function_exists($function)) {
    $function($variables);
  }
}

/**
 * Implements template_preprocess_views_view_unformatted().
 */
function ampcms_preprocess_views_view_unformatted(&$variables) {
  $function = '__' . __FUNCTION__ . '__' . $variables['view']->name;
  if (function_exists($function)) {
    $function($variables);
  }
}

/**
 * Implements template_preprocess_views_view_fields().
 */
function ampcms_preprocess_views_view_fields(&$variables) {
  $function = '__' . __FUNCTION__ . '__' . $variables['view']->name;
  if (function_exists($function)) {
    $function($variables);
  }
}

/*******************************************************************************
 * Helper functions for template_preprocess_HOOK() implementations.
 */

/**
 * Implements ampcms_preprocess_views_view() for homepage view.
 */
function __ampcms_preprocess_views_view__homepage(&$vars) {
  switch ($vars['view']->current_display) {
    case 'news_events':
      if (!empty($vars['view']->result)) {
        $vars['more'] = '<div class="more-link">' . l(t('see all'), 'blog/news-and-events') . '</div>';
      }
      break;
  }
}

/**
 * Implements ampcms_preprocess_views_view() for blog_listing view.
 */
function __ampcms_preprocess_views_view__blog_listing(&$vars) {
  switch ($vars['view']->current_display) {
    case 'listing':
      if ($vars['view']->query->pager->current_page == 0) {
        $vars['classes_array'][] = 'views-first-page';
      }
      break;
  }
}
