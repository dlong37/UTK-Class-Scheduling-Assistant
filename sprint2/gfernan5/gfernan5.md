# Sprint 2
Gian Fernandez-Aleman
gfernan5
ClassSchedulingAssisstant

### What you planned to do
- Error checking to file instead of console, #15, https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/15
- Calculate distances between any two buildings, #16, https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/16
- Identify next courses needed in a schedule, #17, https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/17
- Make functions for different program needs, #33, https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/33
- Optimize schedule based on location, #36, https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/36

### What you did not do
* I planned to get issue 36 done for this sprint, however, I was not able to, so it will be an issue to get done for sprint 3
* However, I do have it planned out how I want to complete the issue so I think it should be easier to get done this next sprint

### What problems you encountered
The main issue we encountered was how to deal with multiple pre-reqs for a course where you only needed 1 out of several. It took a little brainstorming to figure out how to get that working. Another issue I encountered was determining distances between two buildings. I forgot to convert from degrees to radians which was throwing off the sin and cos functions used in the haversine function, which was fun figuring out how to solve.

### Issues you worked on
* Issue #15: https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/15
* Issue #16: https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/16
* Issue #17: https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/17
* Issue #33: https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/33

### Files you worked on
* Support.h: backend/generator_location/Support.h
* Support.cpp: backend/generator_location/Support.cpp
* loc.cpp: backend/generator_location/loc.cpp

### What you accomplished
The program is now able to print errors to a file instead of the console. This is useful because we want to keep command line interactions between front end and back end to a minimum (front end should only need to call our program once, everything will be inputted through files and all output will be in files). It's now able to determine what classes still need to be scheduled from the course catalog. And it is now able to determine the distance in miles between any two buildings (which will be needed to create a location based schedule). Finally, the code is now neatly packaged into functions across 3 different files, instead of it all being in one giant main file that had no functions.