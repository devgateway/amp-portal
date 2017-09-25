(function ($) {

  /**
   * Setup the jQuery Token Input autocomplete behavior.
   *
   * Inspired from ampapi_activity.searchform.js
   * @TODO: Cleanup!
   */
  Drupal.behaviors.projectsReportFormModalDialog = {
    attach: function (context, settings) {
      if ($('.tokeninput-textfield', context).length === 0) {
        return;
      }

      $('.tokeninput-textfield', context).each(function() {
        if ($(this).hasClass('token-input-processed')) {
          return;
        }
        var field_name = $(this).data('name');
        var identifier = $(this).data('identifier');
        var extra_filter = $(this).data('extra-filter');
        var level = $(this).data('level');

        // @HACK: Add language code to requests, to prevent caching issues.
        // var lang_code = settings.viewsTokeninput['language'];
        var endpoint = settings.basePath + 'ampapi/autocomplete/' + field_name;
        if (level) {
          endpoint += '/' + level;
        }
        if (extra_filter) {
          endpoint += '/' + extra_filter;
        }

        $(this).tokenInput(endpoint, {
          theme: 'ampcms',
          method: 'get',
          queryParam: 'string',
          prePopulate: settings.viewsTokeninput[identifier]['values'],
          hintText: Drupal.t('Type in a search location'),
          noResultsText: Drupal.t('No results'),
          searchingText: Drupal.t('Searching...'),
          tokenLimit: 1,

          // Update the search form info when the values have changed.
          onAdd: function (item) {
            $(this).closest('.views-accordion-widget-wrapper').addClass('has-values');
          },
          onDelete: function(item) {
            var saved_tokens = this.tokenInput('get');
            if (saved_tokens.length == 0) {
              $(this).closest('.views-accordion-widget-wrapper').removeClass('has-values');
            }
          },
        });
        $(this).addClass('token-input-processed');
      });
    }
  };

})(jQuery);
