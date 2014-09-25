<?php
/**
 * @file
 * amphomepage.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function amphomepage_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'homepage';
  $page->task = 'page';
  $page->admin_title = 'Homepage';
  $page->admin_description = '';
  $page->path = 'homepage';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_homepage_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'homepage';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Homepage';
  $display->uuid = 'b19fafba-6766-4546-8297-028cdc1d8e00';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-8e12b315-2f57-4144-86eb-3e5963449bab';
    $pane->panel = 'middle';
    $pane->type = 'cbreference';
    $pane->subtype = 'cbreference';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'variable_name' => 'contentblock_blockref_homepage',
      'template' => '',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '8e12b315-2f57-4144-86eb-3e5963449bab';
    $display->content['new-8e12b315-2f57-4144-86eb-3e5963449bab'] = $pane;
    $display->panels['middle'][0] = 'new-8e12b315-2f57-4144-86eb-3e5963449bab';
    $pane = new stdClass();
    $pane->pid = 'new-d07c4bc0-ca31-41ee-88ef-befce66b63d9';
    $pane->panel = 'middle';
    $pane->type = 'views_panes';
    $pane->subtype = 'homepage-news_events';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'News And Events',
    );
    $pane->cache = array();
    $pane->style = array(
      'style' => 'cbstyle',
      'settings' => array(
        'pane_classes' => array(
          'layout-block' => 'layout-block',
          'layout-separator' => 'layout-separator',
        ),
      ),
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'homepage-news-events-block two-columns-grid',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'd07c4bc0-ca31-41ee-88ef-befce66b63d9';
    $display->content['new-d07c4bc0-ca31-41ee-88ef-befce66b63d9'] = $pane;
    $display->panels['middle'][1] = 'new-d07c4bc0-ca31-41ee-88ef-befce66b63d9';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['homepage'] = $page;

  return $pages;

}
