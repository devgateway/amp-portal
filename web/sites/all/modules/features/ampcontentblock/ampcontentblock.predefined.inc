<?php
/**
 * @file
 * ampcontentblock.predefined.inc
 */

/**
 * Implements hook_field_formatter_view() for adcontentblock_widget_callback.
 */
function ampcontentblock_render_news_events() {
  $view_name = 'homepage';
  $view_display_id = 'news_events';

  return views_embed_view($view_name, $view_display_id);
}
