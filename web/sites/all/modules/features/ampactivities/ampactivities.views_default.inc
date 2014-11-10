<?php
/**
 * @file
 * ampactivities.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ampactivities_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'activities';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'efq_activity';
  $view->human_name = 'Activities';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Activities';
  $handler->display->display_options['css_class'] = 'activities-search-results layout-block layout-separator';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'external_url' => 'external_url',
    'title' => 'title',
    'beneficiary_agency' => 'beneficiary_agency',
    'primary_sector' => 'primary_sector',
    'actual_start_date' => 'actual_start_date',
    'actual_completion_date' => 'actual_completion_date',
    'actual_commitments' => 'actual_commitments',
    'actual_disbursements' => 'actual_disbursements',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'external_url' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'beneficiary_agency' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'primary_sector' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'actual_start_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'actual_completion_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'actual_commitments' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'actual_disbursements' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Activity: Activity Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['link_to_entity'] = 0;
  /* Field: Activity: Actual Commitments */
  $handler->display->display_options['fields']['actual_commitments']['id'] = 'actual_commitments';
  $handler->display->display_options['fields']['actual_commitments']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['actual_commitments']['field'] = 'actual_commitments';
  $handler->display->display_options['fields']['actual_commitments']['link_to_entity'] = 0;
  /* Field: Activity: Actual Disbursements */
  $handler->display->display_options['fields']['actual_disbursements']['id'] = 'actual_disbursements';
  $handler->display->display_options['fields']['actual_disbursements']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['actual_disbursements']['field'] = 'actual_disbursements';
  $handler->display->display_options['fields']['actual_disbursements']['link_to_entity'] = 0;

  /* Display: Search Page */
  $handler = $view->new_display('page', 'Search Page', 'search_page');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Activity: External URL */
  $handler->display->display_options['fields']['external_url']['id'] = 'external_url';
  $handler->display->display_options['fields']['external_url']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['external_url']['field'] = 'external_url';
  $handler->display->display_options['fields']['external_url']['label'] = '';
  $handler->display->display_options['fields']['external_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['external_url']['link_to_entity'] = 0;
  $handler->display->display_options['fields']['external_url']['display_as_link_text'] = 'View';
  /* Field: Activity: Activity Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['link_to_entity'] = 0;
  /* Field: Activity: Primary Program */
  $handler->display->display_options['fields']['primary_program']['id'] = 'primary_program';
  $handler->display->display_options['fields']['primary_program']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['primary_program']['field'] = 'primary_program';
  $handler->display->display_options['fields']['primary_program']['link_to_entity'] = 0;
  /* Field: Activity: Beneficiary Agency */
  $handler->display->display_options['fields']['beneficiary_agency']['id'] = 'beneficiary_agency';
  $handler->display->display_options['fields']['beneficiary_agency']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['beneficiary_agency']['field'] = 'beneficiary_agency';
  $handler->display->display_options['fields']['beneficiary_agency']['link_to_entity'] = 0;
  /* Field: Activity: Donor Agency */
  $handler->display->display_options['fields']['donor_agency']['id'] = 'donor_agency';
  $handler->display->display_options['fields']['donor_agency']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['donor_agency']['field'] = 'donor_agency';
  $handler->display->display_options['fields']['donor_agency']['link_to_entity'] = 0;
  /* Field: Activity: Primary Sector */
  $handler->display->display_options['fields']['primary_sector']['id'] = 'primary_sector';
  $handler->display->display_options['fields']['primary_sector']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['primary_sector']['field'] = 'primary_sector';
  $handler->display->display_options['fields']['primary_sector']['link_to_entity'] = 0;
  /* Field: Activity: Actual Start Date */
  $handler->display->display_options['fields']['actual_start_date']['id'] = 'actual_start_date';
  $handler->display->display_options['fields']['actual_start_date']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['actual_start_date']['field'] = 'actual_start_date';
  $handler->display->display_options['fields']['actual_start_date']['link_to_entity'] = 0;
  /* Field: Activity: Actual Completion Date */
  $handler->display->display_options['fields']['actual_completion_date']['id'] = 'actual_completion_date';
  $handler->display->display_options['fields']['actual_completion_date']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['actual_completion_date']['field'] = 'actual_completion_date';
  $handler->display->display_options['fields']['actual_completion_date']['link_to_entity'] = 0;
  /* Field: Activity: Actual Commitments */
  $handler->display->display_options['fields']['actual_commitments']['id'] = 'actual_commitments';
  $handler->display->display_options['fields']['actual_commitments']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['actual_commitments']['field'] = 'actual_commitments';
  $handler->display->display_options['fields']['actual_commitments']['link_to_entity'] = 0;
  /* Field: Activity: Actual Disbursements */
  $handler->display->display_options['fields']['actual_disbursements']['id'] = 'actual_disbursements';
  $handler->display->display_options['fields']['actual_disbursements']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['actual_disbursements']['field'] = 'actual_disbursements';
  $handler->display->display_options['fields']['actual_disbursements']['link_to_entity'] = 0;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Activity: Activity Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'efq_activity';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 's';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    3 => 0,
  );
  $handler->display->display_options['path'] = 'activities';
  $translatables['activities'] = array(
    t('Master'),
    t('Activities'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Activity Title'),
    t('Actual Commitments'),
    t('Actual Disbursements'),
    t('Search Page'),
    t('Primary Program'),
    t('Beneficiary Agency'),
    t('Donor Agency'),
    t('Primary Sector'),
    t('Actual Start Date'),
    t('Actual Completion Date'),
    t('Search'),
  );
  $export['activities'] = $view;

  return $export;
}
