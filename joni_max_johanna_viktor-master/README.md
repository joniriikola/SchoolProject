## Software Design Exercise 2020

`Application name: Application`
`Target OS: Windows 10`

##### Team members:

- Joni Riikola
- Max Gratschew
- Johanna Hautala
- Viktor Mykrä

##### Prerequisite dependencies: 

- Qt 5.15.2 (https://www.qt.io/download) 
  - Required additional packages: `QtCharts`
  - Compiler: `MinGW 8.1.0 64-bit`
- OpenSSL 1.1.1i (https://slproweb.com/products/Win32OpenSSL.html) 
  - Note that OpenSSL binaries (libcrypto-1_1-x64.dll & libssl-1_1-x64.dll) must be in runtime path

## Compiling and running the program

This application can also be compiled using QtCreator.

1. Open the project.pro in QtCreator
2. Press the little hammer button to compile or little green arrow to run in the bottom left corner.
3. If application does not display any graphs, make sure your internet connection is working, you have installed the OpenSSL dependency and that the binaries of OpenSSL are in runtime path.

## User guide

Application is based on two main parts and which contains seven different components. These parts are left
and right elements that contains the components. Both of these elements are not dependent on each other and
left elements choices will not have an effect to the right elements choices. Two of the components  are
drop down menus, two control panels, two charts and preset options star on the left of the window. Drop down menus
include many different options to choose from. First eight of those options  from top are options to search
data from either Fingrid-API or FMI-API. User can choose one of these eight options. After user chose
any of the drop down menus options it will show control panel under the drop down menu. Every drop down menus option have
different information that is asked from the user.

Some of these will ask user to enter start date and end date. Pressing calendar-icon will show a pop up window
and user can choose the date from it. There are some restrictions to the user while choosing the date. End date
can't be chosen with earlier date than start date. Also end date must be either the day is going on or some
earlier date. Also user can't choose date from future. After user has fulfilled all the options from the control
panel, user can press "Search" button from the control panel. This will show a loading icon under the control
panel. After the data has been received from the called API it will be visible to the user in format of a chart.

In the application there are two types of charts. Other one is line chart and other one is pie chart. Pie chart
is created in drop down menus option "Electricity Production Method Distribution".

Chart has multiple features included in it. Every lines name and color are visible on top of the chart.
While hovering mouse on top of the graph user can zoom in and out. Scrolling out will make the chart go further
away and scrolling in will zoom closer to the chart. User is able to move the graphs while pressing left click
on the mouse and moving it into different ways.

Line charts have three features while user presses right click and is hovering the cursor on the chart. First
one is "Reset chart". This feature will reset the chart to its original format right after it was released after
the search. Second feature is "Save data set". This feature will show a pop up window that will ask user the filename.
File will be created using filename and it will save all the data from the chart. All saved datasets will be
available to view from drop down menus option "Saved Datasets". User can choose one of saved datasets and it will
show as a chart. Third and last feature of the chart is to "Save as image". This feature is also included in the
pie chart option. This will open a pop up window to the user and user can choose where the photo of the graph will
be saved. Also user needs to enter filename to save it. Line chart have all of the three features while
the pie chart only have feature "Save as image".

Application also have option to choose real time data that. These options are drop down menus options named
"Real Time Frequency", "Real Time Consumption" and "Real Time Import/Export". By real time data it means that
new data is searched every three minutes and this data will be added to the chart.

Application also have feature to save presets. Presets will have data of which drop down menu is selected and
all the fulfilled options from the control panel. Both left and right elements data is saved. This feature is
located on the right side of the application in the star button. Pressing it will pop up an option to show all
the saved presets that are already saved. Bottom of the pop up window it will show two options: "Save Current" and "Load Preset".
Save current option will pop up a window that asks user to give it a filename. Load preset will load already
saved preset that is visible on the list under "Presets". User must press one saved preset to make the button work.
It will make changes to the application so it will show the data from the search options that was saved in the preset that user chose. 


###### 2021 Tampere