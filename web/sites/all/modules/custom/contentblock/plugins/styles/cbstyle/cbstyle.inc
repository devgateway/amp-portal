<?php


/**
 * @file
 * Definition of the 'PanelTabs' region style. Inspired by the "Panels Tabs" module.
 */

// Plugin definition.
$plugin = array(
  'title' => t('CB Style'),
  'description' => t('Display the panes as a Content Block.'),
  'render region' => 'cbstyle_style_render_region',
  'render pane' => 'cbstyle_style_render_pane',
  'settings form' => 'contentblock_cbstyle_style_settings_form',
);

/**
 * Settings form callback.
 */
function contentblock_cbstyle_style_settings_form($style_settings) {
  $form['css_id'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($style_settings['css_id']) ? $style_settings['css_id'] : '',
    '#title' => t('CSS ID'),
    '#description' => t('CSS ID to apply to this pane. This may be blank.'),
  );

  module_load_include('inc', 'ds', 'includes/ds.field_ui');
  $ds_classes = _ds_classes('ds_classes_regions');
  if (isset($ds_classes[''])) {
    unset($ds_classes['']);
  }
  $form['region_classes'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#options' => $ds_classes,
    '#title' => t('Choose additional CSS classes for the region'),
    '#default_value' => isset($style_settings['region_classes']) ? $style_settings['region_classes'] : array(),
  );


  $form['extra_classes'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($style_settings['extra_classes']) ? $style_settings['extra_classes'] : '',
    '#title' => t('Extra CSS class'),
    '#description' => t('CSS class to apply to this pane. This may be blank.'),
  );

  return $form;
}

/**
 * Render region callback.
 */
function theme_cbstyle_style_render_region($vars) {
  $panel_content = $vars['display']->content;

  $contentblock_attributes = array();
  if (!empty($vars['settings']['css_id'])) {
    // Make sure the provided CSS ID is really unique.
    $contentblock_attributes['id'] = drupal_html_id($vars['settings']['css_id']);
  }
  else {
    // Create a unique ID for the contentblock widget.
    $contentblock_attributes['id'] = drupal_html_id('contentblock-' . $vars['region_id']);
  }

  // Add a class to the wrapper.
  $contentblock_attributes['class'][] = 'panel-contentblock';
  if (!empty($vars['settings']['region_classes'])) {
    $contentblock_attributes['class'] += $vars['settings']['region_classes'];
  }

  if (!empty($vars['settings']['extra_classes'])) {
    // Sanitize the provided list of classes.
    $class_list = explode(' ', $vars['settings']['extra_classes']);
    foreach ($class_list as $class) {
      $contentblock_attributes['class'][] = drupal_html_class($class);
    }
  }

  $elements = array(
    '#tree' => TRUE,
    '#prefix' => '<div' . drupal_attributes($contentblock_attributes) . '>',
    '#suffix' => '</div>',
  );

  // Process the rendered panes.
  $delta = 0;
  foreach ($vars['panes'] as $pane_id => $pane_html_content) {
    // Make sure we have some content.
    if (empty($pane_html_content)) {
      // $pane_html_content = '';
      continue;
    }

    // Determine the title for the current pane.
    $title = '';
    if (!empty($vars['display']->content[$pane_id]->configuration['title'])) {
      $title = check_plain($vars['display']->content[$pane_id]->configuration['title']);
    }

    // Create a class for the current contentblock.
    $item_css_class = drupal_html_class('contentblock-content-' . $title);

    // Add the section content.
    $elements[$pane_id . '_content'] = array(
      '#tag' => 'div',
      '#theme' => 'html_tag',
      '#value' => $pane_html_content,
      '#attributes' => array(
        'class' => array(
          'contentblock-section-content',
          $item_css_class,
        ),
      ),
      '#weight' => 2 * $delta + 2,
    );

    $delta++;
  }

  return drupal_render($elements);
}

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_cbstyle_style_render_pane($vars) {
  return render($vars['content']->content);
}
