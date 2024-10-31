# Sprint 3 Reflection

**Name:** David Long <br>
**GitHubID:** dlong37 <br>
**Group Name:** UTK Class Scheduling Assistant

## What I Planned To Do
* Improve the Questionnaire Form and CSV Formatting for Lexy and Gian's program
* Change location of CSV file with form answers for Lexy and Gian's program to read
* Display the results of Lexy and Gian's program to the web page

## What I Didn't Do
* Didn't take care of displaying the generated schedule; Ethan took over on that.

## Problems I Encountered
I had problems with what to work on at a certain point. Because Ethan was taking care of designing the UI for the page the generated schedule would go on, I couldn't really work on displaying the generated schedule on there yet until he was finished. I had already finishing my other issues so I was assigned the task of adding VolCore elective courses to the database. Because I was doing this manually, it ate up a lot of my time, but it did keep me busy.

## Issues I Worked On
* [#37](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/37): Improve Questionnaire Form/CSV File Formatting
* [#38](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/38): Send CSV File to Proper Location for C++ Programs to read
* [#49](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/49): Update eecs_courses.csv with ALL possible elective courses

## Files I Worked On
#### Improving the Questionnaire Page
* UTK-Class-Scheduling-Assistant/backend/templates/questionnaire.html
* UTK-Class-Scheduling-Assistant/backend/views.py

#### Adding VolCore Elective Courses
* UTK-Class-Scheduling-Assistant/backend/courses_generator/eecs_courses.csv

## What I Accomplished
I was able to accomplish improving the questionnaire page with the necessary modifications for Lexy and Gian's program to get the necessary information they needed. I was also able to change how the data could be overwritten in the data.csv file each time the form was submitted, and where it went so Lexy and Gian's programs could read it easily. I was also able to add all the Arts & Humanities courses to our class database.