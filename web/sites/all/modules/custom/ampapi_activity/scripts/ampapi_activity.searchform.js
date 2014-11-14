(function ($) {

/**
 * Setup the jQuery Token Input autocomplete behavior.
 *
 * @TODO: Cleanup!
 */
Drupal.behaviors.projectsSearchFormModalDialog = {
  attach: function (context, settings) {
    if ($('.view-filters form', context).length === 0) {
      return;
    }

    // console.log($('.view-filters form .form-text#edit-da', context), 'here2');
    // $('.view-filters form .form-text#edit-search', context).tokenInput();

    // console.log(endpoint, 'endpoint');

    $('.view-filters form .tokeninput-textfield', context).each(function() {
      var field_name = $(this).attr('data-name');
      var endpoint = settings.basePath + 'ampapi/autocomplete/' + field_name;

      $(this).tokenInput(endpoint, {
        theme: 'ampcms',
        // theme: 'facebook',
        method: 'get',
        minChars: '2',
        queryParam: 'string',
        prePopulate: settings.viewsTokeninput[field_name]['values'],

        // Update the search form info when the values have changed.
        // onAdd: function() {
        //   Drupal.ampp.updateSearchFormInfo(Drupal.ampp.delay);
        // },
        // onDelete: function() {
        //   Drupal.ampp.updateSearchFormInfo(Drupal.ampp.delay);
        // },
      });
    });
  }
};

})(jQuery);
