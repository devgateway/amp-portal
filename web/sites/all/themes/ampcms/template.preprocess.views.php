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

/**
 * Implements template_preprocess_views_view_table().
 */
function ampcms_preprocess_views_view_table(&$variables) {
  $function = '__' . __FUNCTION__ . '__' . $variables['view']->name;
  if (function_exists($function)) {
    $function($variables);
  }
}

/*******************************************************************************
 * Helper functions for template_preprocess_HOOK() implementations.
 */

/**
 * Implements ampcms_preprocess_views_view() for reports view.
 */
function __ampcms_preprocess_views_view__reports(&$vars) {
  $contact_link = l(t('Please leave a Message.'), 'contact', array('attributes' => array('class' => array('contact-link'))));
  $footer = array(
    '#markup' => '<div class="report-contact">' . t('Do you want to comment or provide feedback on this data?') . $contact_link . '</div>',
  );
  $vars['footer'] .= render($footer);
}

/**
 * Implements ampcms_preprocess_views_view_fields() for reports view.
 */
function __ampcms_preprocess_views_view_fields__reports(&$vars) {
  // Specify which fields do we want to opt-in and create the small tables (like in design).
  $table_fields = array('status', 'donor_agency', 'primary_sector', 'location', 'actual_commitments', 'actual_disbursements');
  $header = array();
  $rows = array();
  $row = array();

  foreach ($table_fields as $field) {
    $header[] = array(
      'data' => $vars['fields'][$field]->label_html,
      'class' => array(drupal_html_class($field)),
    );
    $row[] = array('data' => $vars['fields'][$field]->content);
  }
  $rows[] = $row;
  $vars['table'] = theme('table', array('header' => $header, 'rows' => $rows, 'empty' => t('No data available')));
}

/**
 * Implements ampcms_preprocess_views_view() for homepage view.
 */
function __ampcms_preprocess_views_view__homepage(&$vars) {
  switch ($vars['view']->current_display) {
    case 'news_events':
      if (!empty($vars['view']->result)) {
        // @HACK: Remove views contextual links, needed for more-link next to contentblock header.
        $vars['title_suffix']['contextual_links'] = array();
        if (in_array('contextual-links-region', $vars['classes_array'])) {
          $key = array_search('contextual-links-region', $vars['classes_array']);
          unset($vars['classes_array'][$key]);
        }

        $vars['more'] = '<div class="more-link">' . l(t('see all'), 'blog/news-and-events') . '</div>';
      }

      // @HACK: Change the title, This is a way to avoid needing panels translation.
      $vars['view']->set_title(t('News And Events'));
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

      // @HACK: Change the title, This is a way to avoid needing panels translation.
      if (!empty($vars['view']->args) && reset($vars['view']->args) == 'news+events') {
        $vars['view']->set_title(t('News And Events'));
      }
      else {
        $vars['view']->set_title(t('Blog'));
      }

      break;
  }
}

/**
 * Implements ampcms_preprocess_views_view() for activities view.
 */
function __ampcms_preprocess_views_view__activities(&$vars) {
  switch ($vars['view']->current_display) {
    case 'search_page':
      // @HACK: Change the title, This is a way to avoid views translation issue.
      $vars['view']->set_title(t('Activities'));

      if (!empty($vars['view']->query->pager->total_items)) {
        // TODO: Use built in "Result summary".
        $info = array(
          'current_page' => $vars['view']->query->pager->current_page,
          'items_per_page' => $vars['view']->query->pager->options['items_per_page'],
          'total_items' => $vars['view']->query->pager->total_items,
        );
        $vars['attachment_before'] .= theme('amp_report_info', $info);
      }

      if (!empty($vars['view']->query->query->metaData['report_totals'])) {
        $report_totals = $vars['view']->query->query->metaData['report_totals'];
        if (isset($vars['view']->query->query->metaData['report_currency'])) {
          $report_currency = $vars['view']->query->query->metaData['report_currency'];
          // Let's add the amount units to the currency.
          if (!empty($vars['view']->query->query->metaData['report_amount_units'])) {
              $amount_used = $vars['view']->query->query->metaData['report_amount_units'];
              $amount_units_settings = _ampapi_activity_get_api_settings('amount-units');
              $amount_unit_used_settings = $amount_units_settings[$amount_used];
              if (!empty($amount_unit_used_settings['label long'])) {
                $report_currency = $amount_unit_used_settings['label long'] . ' ' . $report_currency;
              }
           }
        }

        $vars['attachment_after'] .= theme('amp_report_totals', array('totals' => $report_totals, 'currency' => $report_currency));
      }

      break;
  }
}

/**
 * Implements ampcms_preprocess_views_view_table() for activities view.
 */
function __ampcms_preprocess_views_view_table__activities(&$vars) {
  switch ($vars['view']->current_display) {
    case 'search_page':
      $mappers = ampapi_get_mappers();
      foreach ($mappers as $key => $plugin) {
        if (empty($plugin['property name'])) {
          continue;
        }
        if (empty($plugin['report field type'])) {
          continue;
        }

        $extra_class = drupal_clean_css_identifier(drupal_strtolower(' type-' . $plugin['report field type']));
        if (isset($vars['header_classes'][$plugin['property name']])) {
          $vars['header_classes'][$plugin['property name']] .= $extra_class;
        }
        if (isset($vars['field_classes'][$plugin['property name']])) {
          foreach ($vars['field_classes'][$plugin['property name']] as &$class_attribute) {
            $class_attribute .= $extra_class;
          }
        }
      }
      break;
  }
}
