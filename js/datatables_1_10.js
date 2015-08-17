(function ($) {
  Drupal.behaviors.datatables = {
    attach: function (context, settings) {
      $.each(settings.datatables, function (selector) {
        $(selector, context).once('datatables', function() {
          // Get the passed in Drupal settings for this instance.
          var drupal_settings = Drupal.settings.datatables[selector];

          // From advanced style plugin settings.
          if(drupal_settings.ajax) {
            /**
             * Slice the JSON result as we've already got that data sourced by
             * DOM.
             *
             * @param json
             * @returns {*}
             */
            drupal_settings.ajax.dataSrc = function ( json ) {
              // Removing the .views-row within drupal_settings.drawCallback()
              // means we're missing rows. Better to remove them from the JSON.
              if (drupal_settings.pageLength) {
                //json.data = json.data.slice(drupal_settings.pageLength, drupal_settings.recordsTotal);
              }
              return json.data;
            };

            // Option deferRender is very complicated without serverSide
            // processing. @todo maybe later.
            if (drupal_settings.serverSide) {
              // We need to provide return params with data.
              var _params = function() {
                var extend = {
                  draw: 1,
                  recordsTotal: drupal_settings.recordsTotal,
                  recordsFiltered: drupal_settings.pageLength
                };
                return extend;
              };
              // Remember the url, we'll be rewriting ajax.
              url = drupal_settings.ajax.url;
              // Rewrite the ajax function, suggested as localstorage.. but
              // does not search/order data for us?
              drupal_settings.ajax = function(data, callback, settings) {
                cid = settings.sTableId;
                // var api = this.api();
                // Load new data?
                // api.row().data(data);
                // Set sorting?
                // api.column().order(settings.aaSorting[0]).data();
                // Reset
                // localStorage.removeItem(cid);

                var rows = JSON.parse(localStorage.getItem(cid));
                // If Cached.
                if(rows) {
                  // console.log('cached');
                  $.extend(rows, _params(), data, settings);
                  if (settings.start) {
                    rows.data = rows.data.slice(settings.start, settings.length);
                  }
                  callback(rows);
                }
                else {
                  //console.log("ajax'ing");
                  $.ajax({
                    dataType: "json",
                    url: url,
                    /*data: data,*/
                    success: function(result, status, xhr) {
                      //console.log(cid);
                      //console.log(result);
                      localStorage.setItem(cid, JSON.stringify(result));
                      //rows = JSON.parse(localStorage.getItem(cid));
                      $.extend(result, _params(), data, settings);
                      callback(result);
                    }
                  });
                }
              }
            }

          }

          // Initialize DataTables 1.10+.
          datatable = $(selector).DataTable(drupal_settings);

          /**
           * As we're mixing JSON and DOM sources without real serverSide,
           * the initial items will be duplicated, simply remove here.
           */
          datatable.on( 'xhr', function () {
            //console.log('naopw');
            $('tbody tr.views-row').remove();
          });

          // Check if table should contain expandable hidden row feature.
          if (settings.expandable) {
            $(selector + ' tbody tr td:first-child:not(.details-control)').addClass('details-control').on('click', function() {
              var datatable = $(selector).DataTable();
              var tr = $(this).closest('tr');
              var row = datatable.row( tr );
              // isShown() - thanks Datatables 1.10!
              if ( row.child.isShown() ) {
                // This row is already open - close it.
                row.child.hide();
                tr.removeClass('shown');
              }
              else {
                // Open this row, theme the previous way.
                var showValue = Drupal.theme('datatablesExpandableRow', settings, row.data());
                row.child( showValue ).show();
                tr.addClass('shown');
              }
            });
          }
/*
          $(selector + ' tbody').on('click', 'td.details-control', function () {
          });
*/
        });
      });
    }
  };

  /**
  * Theme an expandable hidden row.
  *
  * @param settings
  *   The datatable settings.
  * @param rowData
  *   The row array for which the hidden row is being displayed.
  * @return
  *   The formatted text (html).
  */
  Drupal.theme.prototype.datatablesExpandableRow = function(settings, rowData) {

    var output = '<table style="padding-left: 50px">';
    $.each(rowData, function(index, value) {
      if (!settings.columns[index].visible) {
        //console.log(value);
        output += '<tr><td style="text-align: left">' + value + '</td></tr>';
      }
    });
    output += '</table>';

    return output;
  };
})(jQuery);
