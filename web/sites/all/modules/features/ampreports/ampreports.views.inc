<?php

/**
 * Implements hook_views_data_alter().
 */
function ampreports_views_data() {
  $data['views']['ampreports_result'] = array(
    'title' => t('AMP Reports Result'),
    'help' => t('A custom reports result handler.'),
    'area' => array(
      'handler' => 'ampreports_views_handler_area_result',
    ),
  );
  return $data;
}
