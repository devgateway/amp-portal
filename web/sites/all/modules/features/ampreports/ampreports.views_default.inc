<?php
/**
 * @file
 * ampreports.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ampreports_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'reports';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'efq_activity';
  $view->human_name = 'Reports';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Report by Department or Municipality';
  $handler->display->display_options['css_class'] = 'report-search-results';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Apply Filters';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Clear Filters';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '15';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '7';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: AMP Reports Result */
  $handler->display->display_options['header']['ampreports_result']['id'] = 'ampreports_result';
  $handler->display->display_options['header']['ampreports_result']['table'] = 'views';
  $handler->display->display_options['header']['ampreports_result']['field'] = 'ampreports_result';
  $handler->display->display_options['header']['ampreports_result']['chart_sectors'] = '8';
  $handler->display->display_options['header']['ampreports_result']['chart_projects_length'] = '10';
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = 'No projects matching search criteria.';
  /* Field: Activity: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 1;
  /* Field: Activity: Description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['description']['link_to_entity'] = 0;
  /* Field: Activity: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['status']['link_to_entity'] = 0;
  /* Field: Activity: Agence Donatrice */
  $handler->display->display_options['fields']['donor_agency']['id'] = 'donor_agency';
  $handler->display->display_options['fields']['donor_agency']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['donor_agency']['field'] = 'donor_agency';
  $handler->display->display_options['fields']['donor_agency']['label'] = 'Donor';
  $handler->display->display_options['fields']['donor_agency']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['donor_agency']['link_to_entity'] = 0;
  /* Field: Activity: Secteur Primaire */
  $handler->display->display_options['fields']['primary_sector']['id'] = 'primary_sector';
  $handler->display->display_options['fields']['primary_sector']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['primary_sector']['field'] = 'primary_sector';
  $handler->display->display_options['fields']['primary_sector']['label'] = 'Sector';
  $handler->display->display_options['fields']['primary_sector']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['primary_sector']['link_to_entity'] = 0;
  /* Field: Activity: Localisation */
  $handler->display->display_options['fields']['location']['id'] = 'location';
  $handler->display->display_options['fields']['location']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['location']['field'] = 'location';
  $handler->display->display_options['fields']['location']['label'] = 'Municipalities';
  $handler->display->display_options['fields']['location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['location']['link_to_entity'] = 0;
  /* Field: Activity: Actual Commitments */
  $handler->display->display_options['fields']['actual_commitments']['id'] = 'actual_commitments';
  $handler->display->display_options['fields']['actual_commitments']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['actual_commitments']['field'] = 'actual_commitments';
  $handler->display->display_options['fields']['actual_commitments']['label'] = 'Real Commitments';
  $handler->display->display_options['fields']['actual_commitments']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['actual_commitments']['link_to_entity'] = 0;
  /* Field: Activity: Actual Disbursements */
  $handler->display->display_options['fields']['actual_disbursements']['id'] = 'actual_disbursements';
  $handler->display->display_options['fields']['actual_disbursements']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['actual_disbursements']['field'] = 'actual_disbursements';
  $handler->display->display_options['fields']['actual_disbursements']['label'] = 'Real Disbursements';
  $handler->display->display_options['fields']['actual_disbursements']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['actual_disbursements']['link_to_entity'] = 0;
  /* Sort criterion: Activity: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'efq_activity';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Filter criterion: Localisation (Department) */
  $handler->display->display_options['filters']['location']['id'] = 'location';
  $handler->display->display_options['filters']['location']['table'] = 'efq_activity';
  $handler->display->display_options['filters']['location']['field'] = 'location';
  $handler->display->display_options['filters']['location']['ui_name'] = 'Localisation (Department)';
  $handler->display->display_options['filters']['location']['value'] = '';
  $handler->display->display_options['filters']['location']['group'] = 1;
  $handler->display->display_options['filters']['location']['exposed'] = TRUE;
  $handler->display->display_options['filters']['location']['expose']['operator_id'] = 'location_op';
  $handler->display->display_options['filters']['location']['expose']['label'] = 'Department';
  $handler->display->display_options['filters']['location']['expose']['operator'] = 'location_op';
  $handler->display->display_options['filters']['location']['expose']['identifier'] = 'location_dep';
  $handler->display->display_options['filters']['location']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    3 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['location']['group_info']['label'] = 'Localisation';
  $handler->display->display_options['filters']['location']['group_info']['identifier'] = 'location';
  $handler->display->display_options['filters']['location']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['location']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  $handler->display->display_options['filters']['location']['type'] = 'tokeninput';
  $handler->display->display_options['filters']['location']['amp_extra_options'] = array(
    'location_level' => '2',
  );
  /* Filter criterion: Localisation (Municipality) */
  $handler->display->display_options['filters']['location_1']['id'] = 'location_1';
  $handler->display->display_options['filters']['location_1']['table'] = 'efq_activity';
  $handler->display->display_options['filters']['location_1']['field'] = 'location';
  $handler->display->display_options['filters']['location_1']['ui_name'] = 'Localisation (Municipality)';
  $handler->display->display_options['filters']['location_1']['value'] = '';
  $handler->display->display_options['filters']['location_1']['group'] = 1;
  $handler->display->display_options['filters']['location_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['location_1']['expose']['operator_id'] = 'location_1_op';
  $handler->display->display_options['filters']['location_1']['expose']['label'] = 'Municipality';
  $handler->display->display_options['filters']['location_1']['expose']['operator'] = 'location_1_op';
  $handler->display->display_options['filters']['location_1']['expose']['identifier'] = 'location_mun';
  $handler->display->display_options['filters']['location_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    3 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['location_1']['type'] = 'tokeninput';
  $handler->display->display_options['filters']['location_1']['amp_extra_options'] = array(
    'location_level' => '0',
  );
  /* Filter criterion: Activity: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'efq_activity';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '63';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Only include projects that are in execution';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    3 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['status']['expose']['reduce'] = TRUE;
  $handler->display->display_options['filters']['status']['type'] = 'checkbox';
  $handler->display->display_options['filters']['status']['error_message'] = FALSE;

  /* Display: Report Page */
  $handler = $view->new_display('page', 'Report Page', 'report_page');
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: AMP Reports Result */
  $handler->display->display_options['header']['ampreports_result']['id'] = 'ampreports_result';
  $handler->display->display_options['header']['ampreports_result']['table'] = 'views';
  $handler->display->display_options['header']['ampreports_result']['field'] = 'ampreports_result';
  $handler->display->display_options['header']['ampreports_result']['chart_sectors'] = '8';
  $handler->display->display_options['header']['ampreports_result']['chart_projects_length'] = '15';
  $handler->display->display_options['defaults']['footer'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Activity: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 1;
  /* Field: Activity: Description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['description']['link_to_entity'] = 0;
  /* Field: Activity: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['status']['link_to_entity'] = 0;
  /* Field: Activity: Agence Donatrice */
  $handler->display->display_options['fields']['donor_agency']['id'] = 'donor_agency';
  $handler->display->display_options['fields']['donor_agency']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['donor_agency']['field'] = 'donor_agency';
  $handler->display->display_options['fields']['donor_agency']['label'] = 'Donor';
  $handler->display->display_options['fields']['donor_agency']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['donor_agency']['link_to_entity'] = 0;
  /* Field: Activity: Secteur Primaire */
  $handler->display->display_options['fields']['primary_sector']['id'] = 'primary_sector';
  $handler->display->display_options['fields']['primary_sector']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['primary_sector']['field'] = 'primary_sector';
  $handler->display->display_options['fields']['primary_sector']['label'] = 'Sector';
  $handler->display->display_options['fields']['primary_sector']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['primary_sector']['link_to_entity'] = 0;
  /* Field: Activity: Localisation */
  $handler->display->display_options['fields']['location']['id'] = 'location';
  $handler->display->display_options['fields']['location']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['location']['field'] = 'location';
  $handler->display->display_options['fields']['location']['label'] = 'Municipalities';
  $handler->display->display_options['fields']['location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['location']['link_to_entity'] = 0;
  /* Field: Activity: Actual Commitments */
  $handler->display->display_options['fields']['actual_commitments']['id'] = 'actual_commitments';
  $handler->display->display_options['fields']['actual_commitments']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['actual_commitments']['field'] = 'actual_commitments';
  $handler->display->display_options['fields']['actual_commitments']['label'] = 'Real Commitments';
  $handler->display->display_options['fields']['actual_commitments']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['actual_commitments']['link_to_entity'] = 0;
  $handler->display->display_options['fields']['actual_commitments']['override'] = TRUE;
  $handler->display->display_options['fields']['actual_commitments']['currency_settings'] = array(
    'set_precision' => 1,
    'precision' => '0',
    'decimal' => '.',
    'separator' => ',',
    'separator_remove' => ',',
  );
  /* Field: Activity: Actual Disbursements */
  $handler->display->display_options['fields']['actual_disbursements']['id'] = 'actual_disbursements';
  $handler->display->display_options['fields']['actual_disbursements']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['actual_disbursements']['field'] = 'actual_disbursements';
  $handler->display->display_options['fields']['actual_disbursements']['label'] = 'Real Disbursements';
  $handler->display->display_options['fields']['actual_disbursements']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['actual_disbursements']['link_to_entity'] = 0;
  $handler->display->display_options['fields']['actual_disbursements']['override'] = TRUE;
  $handler->display->display_options['fields']['actual_disbursements']['currency_settings'] = array(
    'set_precision' => 1,
    'precision' => '0',
    'decimal' => '.',
    'separator' => ',',
    'separator_remove' => ',',
  );
  /* Field: Path (Excluded) */
  $handler->display->display_options['fields']['external_url']['id'] = 'external_url';
  $handler->display->display_options['fields']['external_url']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['external_url']['field'] = 'external_url';
  $handler->display->display_options['fields']['external_url']['ui_name'] = 'Path (Excluded)';
  $handler->display->display_options['fields']['external_url']['label'] = '';
  $handler->display->display_options['fields']['external_url']['exclude'] = TRUE;
  $handler->display->display_options['fields']['external_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['external_url']['display_as_link'] = FALSE;
  $handler->display->display_options['fields']['external_url']['link_to_entity'] = 0;
  $handler->display->display_options['path'] = 'reports';

  /* Display: Export Page (Doc) */
  $handler = $view->new_display('views_data_export', 'Export Page (Doc)', 'views_data_export_doc');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_doc';
  $handler->display->display_options['style_options']['attach_text'] = 'DOC';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['filename'] = '%processed_filters-%timestamp-dd-%timestamp-mm-%timestamp-yyyy.doc';
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Activity: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Project Title';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 0;
  /* Field: Activity: Description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = 'Project Description';
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['description']['link_to_entity'] = 0;
  /* Field: Activity: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['status']['link_to_entity'] = 0;
  /* Field: Activity: Agence Donatrice */
  $handler->display->display_options['fields']['donor_agency']['id'] = 'donor_agency';
  $handler->display->display_options['fields']['donor_agency']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['donor_agency']['field'] = 'donor_agency';
  $handler->display->display_options['fields']['donor_agency']['label'] = 'Donor';
  $handler->display->display_options['fields']['donor_agency']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['donor_agency']['link_to_entity'] = 0;
  /* Field: Activity: Secteur Primaire */
  $handler->display->display_options['fields']['primary_sector']['id'] = 'primary_sector';
  $handler->display->display_options['fields']['primary_sector']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['primary_sector']['field'] = 'primary_sector';
  $handler->display->display_options['fields']['primary_sector']['label'] = 'Sector';
  $handler->display->display_options['fields']['primary_sector']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['primary_sector']['link_to_entity'] = 0;
  /* Field: Activity: Localisation */
  $handler->display->display_options['fields']['location']['id'] = 'location';
  $handler->display->display_options['fields']['location']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['location']['field'] = 'location';
  $handler->display->display_options['fields']['location']['label'] = 'Municipalities';
  $handler->display->display_options['fields']['location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['location']['link_to_entity'] = 0;
  /* Field: Activity: Actual Commitments */
  $handler->display->display_options['fields']['actual_commitments']['id'] = 'actual_commitments';
  $handler->display->display_options['fields']['actual_commitments']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['actual_commitments']['field'] = 'actual_commitments';
  $handler->display->display_options['fields']['actual_commitments']['label'] = 'Real Commitments';
  $handler->display->display_options['fields']['actual_commitments']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['actual_commitments']['link_to_entity'] = 0;
  /* Field: Activity: Actual Disbursements */
  $handler->display->display_options['fields']['actual_disbursements']['id'] = 'actual_disbursements';
  $handler->display->display_options['fields']['actual_disbursements']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['actual_disbursements']['field'] = 'actual_disbursements';
  $handler->display->display_options['fields']['actual_disbursements']['label'] = 'Real Disbursements';
  $handler->display->display_options['fields']['actual_disbursements']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['actual_disbursements']['link_to_entity'] = 0;
  $handler->display->display_options['path'] = 'reports/export/doc';
  $handler->display->display_options['displays'] = array(
    'report_page' => 'report_page',
    'default' => 0,
  );
  $handler->display->display_options['segment_size'] = '100';

  /* Display: Export Page (PDF) */
  $handler = $view->new_display('views_data_export', 'Export Page (PDF)', 'views_data_export_pdf');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_pdf';
  $handler->display->display_options['style_options']['attach_text'] = 'PDF';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['filename'] = '%processed_filters-%timestamp-dd-%timestamp-mm-%timestamp-yyyy';
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Activity: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Project Title';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 0;
  /* Field: Activity: Description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = 'Project Description';
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['description']['link_to_entity'] = 0;
  /* Field: Activity: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['status']['link_to_entity'] = 0;
  /* Field: Activity: Agence Donatrice */
  $handler->display->display_options['fields']['donor_agency']['id'] = 'donor_agency';
  $handler->display->display_options['fields']['donor_agency']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['donor_agency']['field'] = 'donor_agency';
  $handler->display->display_options['fields']['donor_agency']['label'] = 'Donor';
  $handler->display->display_options['fields']['donor_agency']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['donor_agency']['link_to_entity'] = 0;
  /* Field: Activity: Secteur Primaire */
  $handler->display->display_options['fields']['primary_sector']['id'] = 'primary_sector';
  $handler->display->display_options['fields']['primary_sector']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['primary_sector']['field'] = 'primary_sector';
  $handler->display->display_options['fields']['primary_sector']['label'] = 'Sector';
  $handler->display->display_options['fields']['primary_sector']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['primary_sector']['link_to_entity'] = 0;
  /* Field: Activity: Localisation */
  $handler->display->display_options['fields']['location']['id'] = 'location';
  $handler->display->display_options['fields']['location']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['location']['field'] = 'location';
  $handler->display->display_options['fields']['location']['label'] = 'Municipalities';
  $handler->display->display_options['fields']['location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['location']['link_to_entity'] = 0;
  /* Field: Activity: Actual Commitments */
  $handler->display->display_options['fields']['actual_commitments']['id'] = 'actual_commitments';
  $handler->display->display_options['fields']['actual_commitments']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['actual_commitments']['field'] = 'actual_commitments';
  $handler->display->display_options['fields']['actual_commitments']['label'] = 'Real Commitments';
  $handler->display->display_options['fields']['actual_commitments']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['actual_commitments']['link_to_entity'] = 0;
  /* Field: Activity: Actual Disbursements */
  $handler->display->display_options['fields']['actual_disbursements']['id'] = 'actual_disbursements';
  $handler->display->display_options['fields']['actual_disbursements']['table'] = 'efq_activity';
  $handler->display->display_options['fields']['actual_disbursements']['field'] = 'actual_disbursements';
  $handler->display->display_options['fields']['actual_disbursements']['label'] = 'Real Disbursements';
  $handler->display->display_options['fields']['actual_disbursements']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['actual_disbursements']['link_to_entity'] = 0;
  $handler->display->display_options['path'] = 'reports/export/pdf';
  $handler->display->display_options['displays'] = array(
    'report_page' => 'report_page',
    'default' => 0,
  );
  $handler->display->display_options['segment_size'] = '50';
  $translatables['reports'] = array(
    t('Master'),
    t('Report by Department or Municipality'),
    t('more'),
    t('Apply Filters'),
    t('Clear Filters'),
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
    t('No projects matching search criteria.'),
    t('Status'),
    t('Donor'),
    t('Sector'),
    t('Municipalities'),
    t('Real Commitments'),
    t('Real Disbursements'),
    t('Department'),
    t('Localisation'),
    t('Municipality'),
    t('Only include projects that are in execution'),
    t('Report Page'),
    t('.'),
    t(','),
    t('Export Page (Doc)'),
    t('Project Title'),
    t('Project Description'),
    t('Export Page (PDF)'),
  );
  $export['reports'] = $view;

  return $export;
}
