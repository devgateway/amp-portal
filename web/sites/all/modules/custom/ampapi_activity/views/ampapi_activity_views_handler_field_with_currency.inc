<?php

/**
 * Field handler for entity properties.
 */
class ampapi_activity_views_handler_field_with_currency extends entity_views_handler_field_text {
  /**
   * Get this field's label taken into account particular heading rules.
   */
  function label() {
    if (!isset($this->options['label'])) {
      return '';
    }
    if (isset($this->query->query->metaData['report_currency'])) {
      $currency = $this->query->query->metaData['report_currency'];
      if (isset($this->query->query->metaData['amount_units']['label long'])) {
        $label_long = $this->query->query->metaData['amount_units']['label long'];
        return $this->options['label'] . ' (' . check_plain($label_long) . ' ' . check_plain($currency) . ')';
      }
      return $this->options['label'] . ' (' . check_plain($currency) . ')';
    }
    return $this->options['label'];
  }

  /**
   * Defines extra options.
   *
   * Inspired from views_handler_field_numeric.inc.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['override'] = array('default' => FALSE, 'bool' => TRUE);
    $options['currency_settings']['set_precision'] = array('default' => FALSE, 'bool' => TRUE);
    $options['currency_settings']['precision'] = array('default' => 0);
    $options['currency_settings']['decimal'] = array('default' => '.', 'translatable' => TRUE);
    $options['currency_settings']['separator'] = array('default' => ',', 'translatable' => TRUE);
    $options['currency_settings']['separator_remove'] = array('default' => ',', 'translatable' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['override'] = array(
      '#type' => 'checkbox',
      '#title' => t('Override the AMP formatting'),
      '#default_value' => $this->options['override'],
    );
    $form['currency_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('Overridden settings'),
      '#dependency' => array('edit-options-override' => array(TRUE)),
    );
    $form['currency_settings']['set_precision'] = array(
      '#type' => 'checkbox',
      '#title' => t('Round'),
      '#description' => t('If checked, the number will be rounded.'),
      '#default_value' => $this->options['currency_settings']['set_precision'],
    );
    $form['currency_settings']['precision'] = array(
      '#type' => 'textfield',
      '#title' => t('Precision'),
      '#default_value' => $this->options['currency_settings']['precision'],
      '#description' => t('Specify how many digits to print after the decimal point.'),
      '#dependency' => array('edit-set-precision' => array(TRUE)),
      '#size' => 2,
    );
    $form['currency_settings']['decimal'] = array(
      '#type' => 'textfield',
      '#title' => t('Decimal point'),
      '#default_value' => $this->options['currency_settings']['decimal'],
      '#description' => t('What single character to use as a decimal point.'),
      '#size' => 2,
    );
    $form['currency_settings']['separator'] = array(
      '#type' => 'select',
      '#title' => t('Thousands marker'),
      '#options' => array(
        '' => t('- None -'),
        ',' => t('Comma'),
        ' ' => t('Space'),
        '.' => t('Decimal'),
        '\'' => t('Apostrophe'),
      ),
      '#default_value' => $this->options['currency_settings']['separator'],
      '#description' => t('What single character to use as the thousands separator.'),
      '#size' => 2,
    );

    $form['currency_settings']['separator_remove'] = array(
      '#type' => 'select',
      '#title' => t('Thousands marker to remove from original'),
      '#options' => array(
        '' => t('- None -'),
        ',' => t('Comma'),
        ' ' => t('Space'),
        '.' => t('Decimal'),
        '\'' => t('Apostrophe'),
      ),
      '#default_value' => $this->options['currency_settings']['separator_remove'],
      '#description' => t('What character should be removed from the original API rendering.'),
      '#size' => 2,
    );

    parent::options_form($form, $form_state);
  }

  /**
   * Render a single field value.
   */
  public function render_single_value($value, $values) {
    // Extra formatting.
    if (!empty($this->options['currency_settings']['set_precision'])) {
      $value = str_replace($this->options['currency_settings']['separator_remove'], '', $value);
      $value = floatval($value);
      $value = number_format($value, $this->options['currency_settings']['precision'], $this->options['currency_settings']['decimal'], $this->options['currency_settings']['separator']);
    }

    return $value;
  }

}
