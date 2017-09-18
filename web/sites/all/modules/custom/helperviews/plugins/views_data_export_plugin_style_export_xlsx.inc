<?php

/**
 * @file
 * PDF style plugin.
 */

class views_data_export_plugin_style_export_xlsx extends views_data_export_plugin_style_export_amp {

  /**
   * Render the display in this style.
   */
  function render() {
    if ($this->uses_row_plugin() && empty($this->row_plugin)) {
      vpr('views_plugin_style_default: Missing row plugin');
      return;
    }

    $output = '';
    $output .= $this->render_body();
    return $output;
  }
}
