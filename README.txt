
This module provides views integration for the DataTables jQuery plugin, which 
provides advanced interaction controls to HTML tables such as dynamic
pagination, on-the-fly filtering, and column sorting.

For full documentation and examples, visit the DataTables jQuery plugin page:
  http://plugins.jquery.com/project/DataTables


-- Installation --

* Copy the datatables module to sites/all/modules directory.

* Download the latest DataTables jQuery plugin 1.9 package from:
    http://datatables.net/download/

* Extract the archive and move the dataTables-1.9/media folder to the 
  sub-directory called dataTables in the datatables folder:

    sites/all/modules/datatables/dataTables/

  The final path to the media folder should be:

    sites/all/modules/datatables/dataTables/media

* Alternatively, if you are using the Libraries API module
  (http://drupal.org/project/libraries), you can place the dataTables folder in
  sites/all/libraries/ so final path is sites/all/libraries/datatables (note the
  lower case directory name).  See http://drupal.org/node/1440066 for more
  information.

* Enable the module at Administer >> Site building >> Modules.

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

* A new fieldset DEFER LOADING OF ADDITIONAL RECORDS has been added, this
  setting takes advantage of DataTables deferLoading, deferRender and ajax
  options by only rendering HTML for rows up to 'Default Page Length'. The rest
  of the rows will be made available over ajax - greatly reducing page weight
  and memory usage.

-- Extensions --

* Currently only Responsive, Select and Buttons are implemented, to keep in line
  with the previous module capabilities.

* To enable any or all of the three available extensions, you need to download
  either the regular or bootstrap versions of both CSS and JS files.

* First you need to create a folder called "extensions" in the same place you
  put the datatables folder, so it will look like this:
    datatables/media/js/jquery.dataTables.js
    datatables/extensions

* Then for you place each extension into a subfolder of extension, named after
  the extension itself:
    datatables/extensions/responsive/
    datatables/extensions/responsive/dataTables.responsive.min.js
    datatables/extensions/responsive/responsive.bootstrap.min.css

* Bootstrap is different to extensions and as such should be placed in
  a bootstrap subfolder:
    datatables/media/js/jquery.dataTables.js
    datatables/bootstrap
    datatables/bootstrap/dataTables.bootstrap.min.js
    datatables/bootstrap/dataTables.bootstrap.min.css

-- Notes --

* Awaiting development:
    - CDN Sourced files and Datatables own bundling.
    - Minified DataTables JS, currently only the full file.
