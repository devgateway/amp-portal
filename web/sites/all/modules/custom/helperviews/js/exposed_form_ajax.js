/**
  * @file
  * Handles Views' exposed form AJAX data submission.
  */
(function($) {

  /*
   * Gets Form build info from settings and adds it to ajax data.
   *
   * @see views_exposed_form_ajax_enable().
   */
  Drupal.behaviors.ViewsExposedFormAjax = {
    attach: function(context, settings) {
      for (ajax_object in Drupal.ajax) {
        if (Drupal.ajax[ajax_object].options) {
          jQuery.extend(Drupal.ajax[ajax_object].options.data, Drupal.settings.exposed_form_info);
        }
      }
    }
  };
})(jQuery);