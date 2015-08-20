
This module provides views integration for the DataTables jQuery plugin, which 
provides advanced interaction controls to HTML tables such as dynamic
pagination, on-the-fly filtering, and column sorting.

For full documentation and examples, visit the DataTables jQuery plugin page:
  http://plugins.jquery.com/project/DataTables


-- Installation datatables v1.9 --

* Copy the datatables module to sites/all/modules directory.

* Download the latest DataTables jQuery plugin package from:
    http://datatables.net/download/

* Extract the archive and move the dataTables-1.9/media folder to the 
  sub-directory called dataTables in the datatables folder:

    sites/all/modules/datatables/dataTables/

  The final path to the media folder for 1.9 should be:

    sites/all/modules/datatables/dataTables/media

  The final path to the media folder for 1.10 should be:

    sites/all/modules/datatables/dataTables/js

* Alternatively, if you are using the Libraries API module
  (http://drupal.org/project/libraries), you can place the dataTables folder in
  sites/all/libraries/ so final path is sites/all/libraries/datatables/media
  (note the lower case directory name).  See http://drupal.org/node/1440066 for
  more information.

* Enable the module at Administer >> Site building >> Modules.

-- Installation datatables v1.10 additional notes--

* In DataTables 1.10 the media folder has been removed, it is replaced with
  separate css, js and images folders. Location examples:

   sites/all/modules/datatables/dataTables/js
   sites/all/modules/datatables/dataTables/css
   sites/all/modules/datatables/dataTables/images

   sites/all/libraries/datatables/dataTables/js
   sites/all/libraries/datatables/dataTables/css
   sites/all/libraries/datatables/dataTables/images

-- Bootstrap notes --

* The complexity of multiple files working together has been greatly eased by
  the datatables package builder http://datatables.net/download/ - I have only
  tested bootstrap using the contributed theme from
  http://drupal.org/project/bootstrap.

* If using the bootstrap theme, do not download these libraries:
    jQueryUI
    jQuery
    Bootstrap Styling library
    Foundation Styling library
  You can include:
      Datatables *Required
      Bootstrap (optional, requires bootstrap theme)
      Foundation (optional, requires foundation theme)
      Responsive
      ..more coming!

* Make sure you use the following packaging options:
    Minify
    Single file
    Local files

* Files will be auto-discovered and that are found will be added, so only choose
  what you intend to use, you can of course add more later.

-- Usage --

* Create a new view at admin/build/views/add

* Add fields to show in the table.

* Select DataTables as the view style.

-- Configuration --

* A basic DataTables configuration will use the rendered HTML as a datasource.
  This means that in most cases you will want to select all rows needed in
  Views and configure the pagination within the DataTables style settings.
  For example: You have 100 rows, you want to display 25 items per page.
    - Set Views Pager to show all 100 rows;
    - Set DataTables style plugin setting 'Default Page Length' in the fieldset
      PAGINATION AND PAGE LENGTH to 25.

* DataTables also allows for columns to be either visible, hidden or expandable.
  You can select these options under the fieldset HIDDEN AND EXPANDABLE COLUMNS.

-- Extensions --

* More to come on extensions but it's worth looking at
  datatables_datatables_alter() if you have further requirements.

* IMPORTANT: If you want to install select, buttons or responsive you should
  manually copy all of the files in the respective folders (yes there's a lot)
  into the css and js folders that you put everything else into.


-- Notes --

* Awaiting development:
    - CDN Sourced files and Datatables own bundling.
    - Minified DataTables JS, currently only the full file.