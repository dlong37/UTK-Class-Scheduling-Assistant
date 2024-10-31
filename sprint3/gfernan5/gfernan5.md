# Sprint 3
Gian Fernandez-Aleman
gfernan5
ClassSchedulingAssisstant

### What you planned to do
- Optimize with respect to location, #36, https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/36
- Randomly pick next classes, #51, https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/51
- Create schedule without time conflicts, #52, https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/52
- Print out class IDs, #53, https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/53

### What you did not do
* I planned to get issue 36 done for this sprint, and I was able to get it to work as intended, but due to some last minute debugging and plans to incorporate VC's next sprint, I left it out of this sprint. But the code is working, so it'll be easy to implement back in

### What problems you encountered
Because in this sprint we did not include VolCores, it is possible to exhaust the classes you can schedule when creating a junior schedule. Which you want to only happen for seniors, not juniors. For right now, I fixed it by having it break when it can no longer schedule core classes, but next sprint, the plan is to include volcores. Another issue I ran into was time conflicts. I was only comparing lecture times to lecture times and lab times to lab times, forgetting that one class's lab time could be another class's lecture time. So I needed to compare lecture and lab times aswell.

### Issues you worked on
* Issue #36, Location-based optimization: https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/36
* Issue #51, Randomly pick next semester classes: https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/51
* Issue #52, Create schedule without time conflicts: https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/52
* Issue #53, Print out class IDs: https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/53

### Files you worked on
* Support.h: backend/c_code/Support.h
* Support.cpp: backend/c_code/Support.cpp
* cgen.cpp: backend/c_code/cgen.cpp

### What you accomplished
The program is now able to determine what next semester classes are needed based on what still remains to take. It randomly does this, so everytime the program is run, the classes are random, provided you can take them. It then finds all sections for each class that needs to be scheduled, and schedules them without time conflicts. It then prints out class ID's to the console, which is used by frontend to print out the schedule.