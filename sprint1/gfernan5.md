# Sprint 1
Gian Fernandez-Aleman
gfernan5
ClassSchedulingAssisstant

### What you planned to do

- Create vectors for major courses and taken courses, #12, https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/12
- Error Checking command line arguments and file opening, #13, https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/13
- expand taken courses vector, #14, https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/14

### What you did not do
We did everything we for sure wanted to get completed in this sprint, but there were two things on our list that were optional
for this sprint and that was
* Expand the csv file to include all of EECS
* Have the program print out a basic schedule

### What problems you encountered
We initially wanted to have some sort of website crawler fetch all the class data from the UTK dynamic schedule, but the data from
there had some slight errors that would've meant that the data we scraped would've had slight errors, which could've
thrown off the whole program. So we dropped the idea

### Issues you worked on

* Issue #7: https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/7
* Issue #12: https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/12
* Issue #13: https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/13
* Issue #14: https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/14

### Files you worked on
* eecs_courses.csv: sprint1/backend/courses_generator/eecs_courses.csv
* read_data.cpp: sprint1/backend/courses_generator/read_data.cpp

### What you accomplished
The program is now able to look at a list of classes you took, and figure out which classes you took and no longer need.
For example, if the user enters COSC 202, the taken_courses vector expands from just COSC 202, and includes COSC 102 and COSC 101.
This is useful for generating a schedule, because based on that, the program can look at list of classes needed for the major and remove the ones already fulfilled, which will leave it with the classes that are still needed, which is useful for generating a schedule. The program also error checks command line arguments and files not opening which is useful for smooth running of operations.