<?php

/**
 * @file
 * Plugin to handle the 'entity' content type which allows individual entities
 * to be embedded into a panel.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'category' => t('Custom'),
  'title' => t('CB Reference'),
  'description' => t('Add a entity from your site as content stored in a variable.'),
  'defaults' => array(
    'variable_name' => '',
    'machine_name' => '',
    'style' => 'normal',
  ),
);

/**
 * Output function for the 'entity' content type.
 *
 * Outputs a entity based on the module and delta supplied in the configuration.
 */
function contentblock_cbreference_content_type_render($subtype, $conf, $panel_args) {
  $block = new stdClass();
  $block->module = 'contentblock';
  $block->css_class = '';

  $block->delta = NULL;
  if (!empty($conf['variable_name'])) {
    $delta = substr($conf['variable_name'], strlen('contentblock_blockref_'));
    $block->delta = $delta;
    $block->subtype = 'cbreference_variable_name';

    // Get the settings.
    $contentblocks = variable_get($conf['variable_name'], NULL);
    if (empty($contentblocks) || !is_array($contentblocks)) {
      return;
    }
  }
  else if (!empty($conf['machine_name'])) {
    $block->delta = $conf['machine_name'];
    $block->subtype = 'cbreference_machine_name';

    $block->css_class .= ' ' . drupal_html_class('cbreference-' . $block->delta);
    $info = contentblock_get_hidden_types($conf['machine_name']);
    if (!empty($info['is section'])) {
      $block->css_class .= ' cbreference-section';
    }

    $contentblocks = entity_load('contentblock', array(), array('machine_name' => $conf['machine_name']));
    if (empty($contentblocks)) {
      return;
    }
  }

  if (isset($block->delta)) {
    $block->content['#contextual_links'] = array(
      'contentblock' => array('admin/settings/static-content', array($block->delta)),
    );
  }

  module_load_include('inc', 'contentblock', 'contentblock.cbreference');
  foreach ($contentblocks as $info) {
    if (is_object($info)) {
      $entity = $info;
    }
    else if (is_array($info) && isset($info['contentblock']) && is_numeric($info['contentblock'])) {
      $entity = entity_load_single('contentblock', $info['contentblock']);
    }
    else {
      continue;
    }

    $view_mode = 'default';
    if (is_array($info) && !empty($info['view_mode'])) {
      $view_mode = $info['view_mode'];
    }

    if (!entity_access('view', 'contentblock', $entity)) {
      continue;
    }

    if (!empty($conf['template'])) {
      $entity->ctools_template_identifier = $conf['template'];
    }

    // @TODO: Add language support.
    $language = NULL;
    if (!empty($entity->machine_name)) {
      $info = contentblock_get_hidden_types($entity->machine_name);
      if (!empty($info['is section'])) {
        $function = 'contentblock_cbreference_render__section';
      }
      else {
        $function = 'contentblock_cbreference_render__' . $entity->machine_name;
      }

      if (function_exists($function)) {
        $return = $function($entity, $conf);
        if (isset($return['#view_mode'])) {
          $block->css_class .= ' ' . drupal_html_class('cbreference-view-mode-' . $return['#view_mode']);
        }
        $block->content[] = $return;
      }
    }
    else {
      $block->content[] = $entity->view($view_mode, $language);
    }
  }

  return $block;
}

/**
 * The form to add or edit a entity as content.
 */
function contentblock_cbreference_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['reference_type'] = array(
    '#title' => t('Reference Type'),
    '#type' => 'radios',
    '#options' => array(
      'single' => t('Single value, by machine_name'),
      'multiple' => t('Multiple values, by variable_name'),
    ),
    '#default_value' => (empty($conf['variable_name']) ? 'single' : 'multiple'),
    '#weight' => -30,
  );

  $form['machine_name'] = array(
    '#title' => t('Machine Name'),
    '#description' => t('The machine_name of the referenced content.'),
    '#type' => 'textfield',
    '#default_value' => $conf['machine_name'],
    '#maxlength' => 512,
    '#weight' => -20,
    '#states' => array(
      'visible' => array(
        ':input[name="reference_type"]' => array('value' => 'single'),
      ),
    ),
  );

  $form['variable_name'] = array(
    '#title' => t('Variable Name'),
    '#description' => t('The variable containing the ID of the referenced content.'),
    '#type' => 'textfield',
    '#default_value' => $conf['variable_name'],
    '#maxlength' => 512,
    '#weight' => -10,
    '#states' => array(
      'visible' => array(
        ':input[name="reference_type"]' => array('value' => 'multiple'),
      ),
    ),
  );

  $form['style'] = array(
    '#type' => 'radios',
    '#title' => t('Style'),
    '#default_value' => $conf['style'],
    '#options' => array(
      'normal' => 'Normal',
      'wide' => 'Wide',
    ),
  );

  return $form;
}

/**
 * Validate the entity selection.
 */
function contentblock_cbreference_content_type_edit_form_submit($form, &$form_state) {
  foreach (array('variable_name', 'machine_name', 'style') as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/**
 * Returns the administrative title for a entity.
 */
function contentblock_cbreference_content_type_admin_title($subtype, $conf) {
  if (!empty($conf['variable_name'])) {
    $variable_name = $conf['variable_name'];
    return t('CB Reference, variable_name: %variable_name', array('%variable_name' => $variable_name));
  }
  else if (!empty($conf['machine_name'])) {
    $machine_name = $conf['machine_name'];
    return t('CB Reference, machine_name: %machine_name', array('%machine_name' => $machine_name));
  }
}
