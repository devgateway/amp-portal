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
      if (_ampapi_amount_unit_get_label($this->query->query->metaData['amount_units']->id, 'long')) {
        $label_long = _ampapi_amount_unit_get_label($this->query->query->metaData['amount_units']->id, 'long');
        return $this->options['label'] . ' (' . check_plain($label_long) . ' ' . check_plain($currency) . ')';
      }
      return $this->options['label'] . ' (' . check_plain($currency) . ')';
    }
    return $this->options['label'];
  }
}
