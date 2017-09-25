/**
 * Google Chart Tools Overridden version javascript
 */

// Load the Visualization API and the chart package.
google.load("visualization", "1", {packages:["corechart"]});

(function($) {
  Drupal.behaviors.customGoogleChart = {
    attach: function(context, settings) {
      google.setOnLoadCallback(drawChart);
      // Callback that creates and populates a data table,
      // instantiates the chart, passes in the data and
      // draws it.
      function drawChart() {
        // Loop on the charts in the settings.
        for (var chartId in settings.chart) {
          // Create the data table.
          var data = new google.visualization.DataTable();
          data.addColumn('string', 'Label');

          // Adding the columns.
          // These are graphs titles.
          for (var col in settings.chart[chartId].columns) {
            data.addColumn('number', settings.chart[chartId].columns[col]);
          }

          // Custom: add the tooltip column if required.
          if (settings.chart[chartId].use_tooltips_column === true) {
            data.addColumn({type: 'string', role: 'tooltip'});
          }

          // Custom: add the style column if required.
          if (settings.chart[chartId].use_style_column === true) {
            data.addColumn({type: 'string', role: 'style'});
          }

          // Adding the headers.
          // The rows titles.
          for (var i in settings.chart[chartId].header) {
            var row = new Array();
            // Adding the rows.
            // The points of the column for each row.
            for (var j in settings.chart[chartId].rows) {
              row[j] = settings.chart[chartId].rows[j][i];
            }
            row.unshift(settings.chart[chartId].header[i]);
            data.addRows([row]);
          }

          // Set chart options
          var options = settings.chart[chartId].options;

          // Instantiate and draw our chart, passing in some options.
          var chart = new Object;
          var element = document.getElementById(settings.chart[chartId].containerId);
          if (element) {
            chart[settings.chart[chartId]] = new google.visualization[settings.chart[chartId].chartType](element);

            // Wait for the chart to finish drawing before calling the getImageURI() method.
            google.visualization.events.addListener(chart[settings.chart[chartId]], 'ready', function () {
              settings.chart[chartId].finalImage = chart[settings.chart[chartId]].getImageURI();
            });
            chart[settings.chart[chartId]].draw(data, options);
          }
        }
      }
    }
  };

  Drupal.behaviors.ampReports = {
    attach: function(context, settings) {
      $('.feed-icon a', context).click(function(evObj) {
        evObj.preventDefault();
        var image = settings.chart.projects_chart.finalImage,
            $link = $(this);
        if (image !== undefined) {
          var wrapper = $link.closest('.feed-wrapper'),
              $ajax_throbber = $('<div class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div></div>');
          $ajax_throbber.appendTo($link.parent());
          $.ajax({
            type: 'POST',
            url: '/ampreports/chart/' + settings.chart.projects_chart.input_hash,
            dataType: 'json',
            success: function(data, status) {
              if (data === 'saved') {
                window.location = $link.attr('href');
                $ajax_throbber.remove();
              }
            },
            data: {
               image: image
            }
          });
        }
      });
    }
  };
})(jQuery);

