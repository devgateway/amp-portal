<?php

/**
 * @file
 * This file contains settings form functions.
 */

/**
 * Page callback for 'admin/settings/static-content/homepage'.
 */
function helpergeneric_homepage_content_settings_form($form, &$form_state) {
  $varname = 'contentblock_blockref_homepage';
  _helpergeneric_cbreference_settings_form($varname, $form, $form_state);

  return system_settings_form($form);
}

/**
 * Page callback for 'admin/settings/static-content/blog'.
 */
function helpergeneric_blog_content_settings_form($form, &$form_state) {
  $varname = 'contentblock_blockref_blog';
  _helpergeneric_cbreference_settings_form($varname, $form, $form_state);

  return system_settings_form($form);
}

/**
 * Helper function for "static-content" forms.
 */
function _helpergeneric_cbreference_settings_form($varname, &$form, &$form_state) {
  $form = array();

  $table_header = array(t('Content Blocks'), t('Weight'), t('Style'));
  $columns_count = count($table_header);

  $form_state['varname'] = $varname;

  $form[$varname] = array(
    '#type' => 'table',
    '#header' => $table_header,
    // Optionally, to add tableDrag support:
    '#tabledrag' => array(
      array('order', 'sibling', 'entry-weight'),
    ),
    '#prefix' => '<div id="referenced-contentblocks">',
    '#suffix' => '</div>',
  );


  $blockref = variable_get($varname, array());
  $blockref = array_values($blockref);

  $styles = array(
    '' => t('Default'),
    'cbstyle' => t('Content Block'),
  );

  $count = 2;
  if (!empty($form_state['values'][$varname]) && count($form_state['values'][$varname]) >= 2) {
    $count = count($form_state['values'][$varname]) + 1;
  }
  else if (!empty($blockref) && count($blockref) >= 2) {
    $count = count($blockref) + 1;
  }

  for ($delta = 0; $delta < $count; $delta++) {
    if (isset($blockref[$delta]) && empty($blockref[$delta])) {
      continue;
    }

    if (!empty($blockref[$delta]['contentblock'])) {
      $entry = $blockref[$delta];
      if (!empty($entry['contentblock']) && is_numeric($entry['contentblock'])) {
        $entity = entity_load_single('contentblock', $entry['contentblock']);
        if (!empty($entity)) {
          $contentblock_value = check_plain($entity->label()) . ' (' . $entity->identifier() . ')';
          $entry['contentblock'] = $contentblock_value;
        }
      }
    }
    else {
      $entry = array(
        'contentblock' => '',
        'style' => '',
        'weight' => $delta,
      );
    }

    // TableDrag: Sort the table row according to its existing/configured weight.
    $form[$varname][$delta]['#weight'] = $entry['weight'];
    // TableDrag: Mark the table row as draggable.
    $form[$varname][$delta]['#attributes']['class'][] = 'draggable';
    $form[$varname][$delta]['#attributes']['class'][] = 'entry-region-main';

    // We'll manually set the #parents property of these fields so that
    // their values appear in the $form_state['values'][$property] array.
    $form[$varname][$delta]['contentblock'] = array(
      '#type' => 'textfield',
      '#title' => t('Content Block'),
      '#title_display' => 'invisible',
      '#default_value' => $entry['contentblock'],
      '#autocomplete_path' => 'helpergeneric/contentblock/autocomplete',
      '#element_validate' => array('_helpergeneric_contentblock_element_validate'),
    );

    // Add tableDrag support.
    $form[$varname][$delta]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#title_display' => 'invisible',
      '#default_value' => $entry['weight'],
      '#attributes' => array('class' => array('entry-weight')),
    );

    $form[$varname][$delta]['style'] = array(
      '#type' => 'select',
      '#title' => t('Style'),
      '#title_display' => 'invisible',
      '#default_value' => $entry['style'],
      '#options' => $styles,
      '#weight' => -10,
    );
  }

  // We name our button 'fbc_add' to avoid conflicts with other modules.
  $form['helperadd'] = array(
    '#type' => 'submit',
    '#value' => t('Add another item'),
    '#attributes' => array(
      'title' => t("If the amount of boxes above isn't enough, click here to add more."),
    ),
    '#weight' => 1,
    '#limit_validation_errors' => array(
      array($varname), // Only validate the referenced entities when using AHAH to update the form.
    ),
    '#submit' => array('_helpergeneric_helperadd_submit'),
    '#ajax' => array(
      'callback' => '_helpergeneric_ajax_form_references',
      'wrapper' => 'referenced-contentblocks',
      'effect' => 'fade',
    ),
  );

  // array_unshift($form['#submit'], 'helpergeneric_contentblock_submit');
  $form['#submit'][] = 'helpergeneric_contentblock_submit';
}

/**
 * Process system_theme_settings form submissions.
 */
function helpergeneric_contentblock_submit($form, &$form_state) {
  $varname = $form_state['varname'];
  $ref_values = &$form_state['values'][$varname];

  foreach ($ref_values as $key => $value) {
    if (empty($value['contentblock'])) {
      unset($ref_values[$key]);
    }
  }
}

/**
 * Form element validation handler for default group audience elements.
 */
function _helpergeneric_contentblock_element_validate($element, &$form_state) {
  preg_match('/\(([0-9]+)\)$/', $element['#value'], $matches);
  if (!empty($matches[1]) && is_numeric($matches[1])) {

    // It's not used that often, so we can load entity.
    $entity = entity_load_single('contentblock', $matches[1]);
    if (!empty($entity)) {
      form_set_value($element, $entity->identifier(), $form_state);
    }
    else {
      $args = array(
        '%value' => $element['#value'],
      );
      form_error($element, t('Content Block %value does not exist.', $args));
    }
  }
  elseif (!empty($element['#value'])) {
    $args = array(
      '%value' => $element['#value'],
    );
    form_error($element, t('"%value" is not a valid reference.', $args));
  }
}

/**
 * Submit handler to add more questions to the form.
 */
function _helpergeneric_helperadd_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback in response to new categories being added to the form.
 *
 * This returns the new page content to replace the page content made obsolete
 * by the form submission.
 *
 * @see _helpergeneric_helperadd_submit()
 */
function _helpergeneric_ajax_form_references($form, $form_state) {
  $varname = $form_state['varname'];
  return $form[$varname];
}
