<?php
/**
 * @file
 * Provides developer information for hooks provided by the datatables module.
 */


/**
 * Implements hook_datatables_pre_view_alter().
 *
 * Preprocessing the datatables theme function is too later if you wish to add
 * to the datatable_options array.
 *
 * This alter hook provides overrides for all datatable views.
 *
 * @param $vars
 */
function hook_datatables_pre_view_alter(&$vars) {
  $datatable_options = &$vars['datatable_options'];
  // Any options changed will take effect.
}

/**
 * Implements hook_datatables_VIEWNAME_alter().
 *
 * Preprocessing the datatables theme function is too later if you wish to add
 * to the datatable_options array.
 *
 * This alter hook provides overrides for the named datatable view.
 *
 * @param $vars
 */
function hook_datatables_VIEWNAME_alter(&$vars) {
  $datatable_options = &$vars['datatable_options'];
  // Any options changed will take effect and override
  // hook_datatables_pre_view_alter().
}

/**
 * Using the Disable Initialization option.
 *
 * This is a Javascript example:
 *

  // Get the passed in Drupal settings for this instance.
  $(document).ready(function() {
    var selector = "#datatable-1";
    var drupal_settings = Drupal.settings.datatables[selector];
    // When rendering field 1 (title), include field 2 also (country).
    drupal_settings.columns[1].render = function(data, type, full, meta) {
      var country = full.field_country;
      var ret = data;
      if (type == 'display') {
        ret = data + '<div class="country">' +  country + '</div>';
      }
      return ret;
    };

    // Tnitialize DataTables with our new column handler.
    datatable = $(selector).DataTable(drupal_settings);
  });

 *
 */
