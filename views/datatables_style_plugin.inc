<?php
/**
 * @file
 * Contains the datatables style plugin.
 */

/**
 * Style plugin to render each item as a row in a datatables.
 *
 * @ingroup views_style_plugins
 */
class datatables_style_plugin extends views_plugin_style_table {
  /**
   * Implements parent::option_definition().
   */
  function option_definition() {
    $options = parent::option_definition();

    unset($options['sticky']);
    unset($options['override']);

    $options['elements'] = array(
      'default' => array(
        'search_box' => TRUE,
        'table_info' => TRUE,
        'save_state' => FALSE,
      ),
    );
    $options['layout'] = array(
      'default' => array(
        'autowidth' => FALSE,
        'themeroller' => FALSE,
        'sdom' => '',
      ),
    );
    $options['pages'] = array(
      'default' => array(
        'pagination_style' => 0,
        'length_change' => 0,
        'display_length' => 10,
      ),
    );
    $options['hidden_columns'] = array(
      'default' => array(),
    );
    $options['defer_load'] = array(
      'default' => array(),
    );

    return $options;
  }

  /**
   * Implements parent::options_form().
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Check if fields have been added.  Table style plugin will set
    // error_markup if fields are not added.
    // @see views_plugin_style_table::options_form()
    if (isset($form['error_markup'])) {
      return;
    }

    unset($form['sticky']);
    unset($form['override']);

    $form['description_markup']['#markup'] = '<div class="description form-item">' . t('DataTables works best if you set the pager to display all items, since DataTabels contains its own pager implementation.<br/><br/>Place fields into columns; you may combine multiple fields into the same column. If you do, the separator in the column specified will be used to separate the fields. Check the sortable box to make that column click sortable, and check the default sort radio to determine which column will be sorted by default, if any. You may control column order and field labels in the fields section.') . '</div>';


    $form['elements'] = array(
      '#type' => 'fieldset',
      '#title' => t('Widgets & Elements'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['elements']['search_box'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable the search filter box.'),
      '#default_value' => !empty($this->options['elements']['search_box']),
      '#description' => 'The search filter box allows users to dynamically filter the results in the table.  Disabling this option will hide the search filter box from users.',
    );
    $form['elements']['table_info'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable the table information display.'),
      '#default_value' => !empty($this->options['elements']['table_info']),
      '#description' => t('This shows information about the data that is currently visible on the page, including information about filtered data if that action is being performed.'),
    );
    $form['elements']['save_state'] = array(
      '#type' => 'checkbox',
      '#title' => t('Save State'),
      '#default_value' => !empty($this->options['elements']['save_state']),
      '#description' => t("DataTables can use cookies in the end user's web-browser in order to store it's state after each change in drawing. What this means is that if the user were to reload the page, the table should remain exactly as it was (length, filtering, pagination and sorting)"),
    );
    // Table tools is now retired, replaced by buttons and select.
    if (_datatables_is_new_version()) {
      $form['elements']['table_tools'] = array(
        '#type' => 'checkbox',
        '#title' => t('Table Tools'),
        '#default_value' => 0,
        '#attributes' => array('readonly' => 'readonly', 'disabled' => 'disabled'),
        '#description' => t('TableTools has been retired, please use Buttons and Select extensions in Advanced section.'),
      );
    }
    else {
      $form['elements']['table_tools'] = array(
        '#type' => 'checkbox',
        '#title' => t('Table Tools'),
        '#default_value' => !empty($this->options['elements']['table_tools']),
        '#description' => t('Table Tools is a plugin that adds a powerful button toolbar with copy, save, and print capabilities. See <a href="http://datatables.net/extras/tabletools/">TableTools Help</a> for more information.  Note that if you have custom sDom settings, TableTools can be included by inserting the "T" character.'),
      );
    }

    $form['layout'] = array(
      '#type' => 'fieldset',
      '#title' => t('Layout and Display'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['layout']['autowidth'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable auto-width calculation.'),
      '#default_value' => !empty($this->options['layout']['autowidth']),
      '#description' => t('Enable or disable automatic column width calculation. This can be disabled as an optimisation (it takes some time to calculate the widths).'),
    );

    $form['layout']['themeroller'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable jQuery UI ThemeRoller Support'),
      '#default_value' => !empty($this->options['layout']['themeroller']),
      '#description' => t("Create markup and classes to support jQuery UI's ThemeRoller"),
    );

    $form['layout']['sdom'] = array(
      '#type' => 'textfield',
      '#title' => t('Set sDOM Initialization Parameter'),
      '#default_value' => $this->options['layout']['sdom'],
      '#description' => t("Use the sDOM parameter to rearrange the interface elements. See the <a href='@sdom_documentation_url'>Datatables sDOM documentation</a> for details on how to use this feature", array('@sdom_documentation_url' => 'http://www.datatables.net/examples/basic_init/dom.html')),
    );

    $form['pages'] = array(
      '#type' => 'fieldset',
      '#title' => t('Pagination and Page Length'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['pages']['pagination_style'] = array(
      '#type' => 'select',
      '#title' => t('Pagination Style'),
      '#default_value' => isset($this->options['pages']['pagination_style']) ? $this->options['pages']['pagination_style'] : 0,
      '#options' => array(
        0 => t('Two-Button (Default)'),
        'full_numbers' => t('Full Numbers'),
        'no_pagination' => t('No Pagination'),
      ),
      '#description' => t('Selects which pagination style should be used.'),
    );

    $form['pages']['length_change'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable Length Change Selection Box'),
      '#default_value' => !empty($this->options['pages']['length_change']),
      '#description' => t('Enable or page length selection menu'),
    );
    $form['pages']['display_length'] = array(
      '#type' => 'select',
      '#title' => t('Default Page Length'),
      '#default_value' => isset($this->options['pages']['display_length']) ? $this->options['pages']['display_length'] : 10,
      '#options' => array(10 => 10, 25 => 25, 50 => 50, 100 => 100),
      '#description' => t('Default number of records to show per page. May be adjusted by users if Length Selection is enabled'),
    );

    $columns = $this->display->handler->get_field_labels();
    $form['hidden_columns'] = array(
      '#type' => 'fieldset',
      '#title' => t('Hidden and Expandable Columns'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    foreach ($columns as $column_name => $column_label) {
      $form['hidden_columns'][$column_name] = array(
        '#type' => 'select',
        '#title' => check_plain($column_label),
        '#default_value' => isset($this->options['hidden_columns'][$column_name]) ? $this->options['hidden_columns'][$column_name] : 0,
        '#options' => array(
          0 => 'Visible',
          'hidden' => 'Hidden',
          'expandable' => 'Hidden and Expandable',
        ),
      );
    }

    // Datatables 1.10 has new options.
    if (_datatables_is_new_version())  {
      // @TODO Remove TableTools and Add Buttons & Select... sigghhh.
      // Advanced settings for 1.10.
      $form['advanced'] = array(
        '#type' => 'fieldset',
        '#title' => t('Advanced'),
        '#description' => t(''
          . ''
        ),
        '#description' => t('Datatables has many options, some which conflict with Views functionality. Depending on your needs, some of these options'
          . '  may benefit your specific use case.'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      // Whether to initialize the plugin, allows for custom JS.
      $form['advanced']['do_not_init'] = array(
        '#type' => 'checkbox',
        '#title' => t('Disable Initialization?'),
        '#description' => t('You can choose for this module to NOT intialize '
          . 'datatables, meaning you must initialize it yourself!<br>'
          . 'The benefit of doing this is to allow you to attach custom JS to '
          . 'the intialization array. (Developer use only)'),
        '#default_value' => isset($this->options['advanced']['do_not_init']) ? $this->options['advanced']['do_not_init'] : 0,
      );
      // Ajax sourced rather than DOM sourced.
      $form['advanced']['json_source_enabled'] = array(
        '#type' => 'checkbox',
        '#title' => t('ajax and deferRender'),
        '#description' => t('Instead of printing the entire HTML from View - create a JSON file to use as the data source (datatables:ajax:url).'
          . ' The file name is based on your result set, so different views filters applied will create a new file.'
          . ' This is best used when you set View pager to 0 and use Views caching (which will prevent the large query operation and file creation).'),
        '#default_value' => isset($this->options['advanced']['json_source_enabled']) ? $this->options['advanced']['json_source_enabled'] : 0,
      );
      // Defer Loading / serverSide hacked.
      $form['advanced']['defer_loading_enabled'] = array(
        '#type' => 'checkbox',
        '#attributes' => array('readonly' => 'readonly', 'disabled' => 'disabled'),
        '#title' => t('deferLoading and serverSide'),
        '#description' => t("Using DataTables deferLoading requires serverSide - however this causes us some problems as we're not using "
          . " Views for serverSide."
          . " Instead we use the datatable API to return the requested results from our JSON file which has the full record set."
          . " This is not ready for release yet... Feel free to contribute!"),
        '#default_value' => isset($this->options['advanced']['defer_loading_enabled']) ? $this->options['advanced']['defer_loading_enabled'] : 0,
      );
      // Bootstrap.
      $form['advanced']['bootstrap'] = array(
        '#type' => 'checkbox',
        '#title' => t('Bootstrap Integration'),
        '#description' => t("You must download the Bootstrap integration files from https://cdn.datatables.net/ and place them in a 'bootstrap/' sub folder in "
          . "your Datatables folder."),
        '#description' => t("You must download the Bootstrap integration files:<br>"
          . "Please see the README provided with this module.<br>"),
        '#default_value' => isset($this->options['advanced']['bootstrap']) ? $this->options['advanced']['bootstrap'] : 0,
      );
      // Extensions Integration.
      $form['responsive'] = array(
        '#type' => 'fieldset',
        '#title' => t('Responsive'),
        '#description' => t("You must download the Responsive integration files<br>
         Please see the README provided with this module.<br>"
         . "<strong>Note: You MUST use datatables 1.10.8 in order for Responsive to work effectively "
         . "and be using jQuery 1.9 or later.</strong>"),
        '#collapsed' => TRUE,
        '#collapsible' => TRUE,
      );
      // Responsive extension.
      $form['responsive']['enabled'] = array(
        '#type' => 'checkbox',
        '#description' => t('Enable Responsive?'),
        '#title' => t('Responsive Extension Integration'),
        '#default_value' => isset($this->options['responsive']['enabled']) ? $this->options['responsive']['enabled'] : 0,
      );
      // Responsive options per field.
      $form['responsive']['breakpoints'] = array(
        '#type' => 'fieldset',
        '#title' => t('Breakpoints per Field'),
        '#description' => 'Here you can set classes on each column, which can control visibility for a specific breakpoint.<br>'
          . 'You can apply any variation of the following classes:<br>'
          . "<dl>
          <dt>none</dt>
           <dd>Hides column but shows in child row.</dd>
          <dt>never</dt>
            <dd>Hides the column and never shows it.</dd>
          <dt>all</dt>
           <dd>Always show the column.</dd>
          <dt>mobile-p</dt>
           <dd>Show in Mobile Portrait.</dd>
          <dt>mobile-l</dt>
            <dd>Show in Mobile Landscape.</dd>
          <dt>tablet-p</dt>
            <dd>Show in Tablet Portrait.</dd>
          <dt>tablet-l</dt>
            <dd>Show in Tablet Landscape.</dd>
          <dt>desktop</dt>
            <dd>Show in Desktop</dd>
          </dl><br>"
          . '<strong>For more information on the viewport sizes and options, see http://datatables.net/extensions/responsive/classes</strong>',
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
      );
      foreach ($columns as $column_name => $column_label) {
        $form['responsive']['breakpoints'][$column_name] = array(
          '#type' => 'textfield',
          '#title' => check_plain($column_label),
          '#default_value' => isset($this->options['responsive']['breakpoints'][$column_name]) ? $this->options['responsive']['breakpoints'][$column_name] : '',
          '#size' => 60,
        );
      }
    }

  }
}
