# Sprint 3

Name: Lexy Andershock</br>
GitHub ID: acandershock</br>
Group Name: UTK-Class-Scheduling-Assistant</br>

### What you planned to do
- finish the implementation of the gaps/no gaps course scheduler (check for conflicts, make priority queues, etc.)
- schedule all reaming COSC classes based on the user's desired number of credit hours - even the co-reqs!
- print out schedule information to a csv file.

### What you did not do
- work with frontend to add program implementation to UI
- add morning/evening time preferences - this was just if I had extra time, anyways!
- adjust program to read from a file instead of the terminal

### What problems you encountered
- Rewriting the program to split it up into different files was hard!
- I had to adjust some code, such as:
  * making sure I was creating gaps between classes all on the same day (at first, I was not considering this, I just gapped from the class that was last scheduled).
  * printing out scheduled classes - this was difficult because there was a lot of data manipulation (vectors popping and pushing classes, temp and permanent schedules, etc.)
  * making the schedule. It required a lot of temporary storage, since a class might fail to be scheduled for many reasons. I had to save a lot of "temporary schedules" so that I could revert to a previous state in case a class failed to be scheduled.
- Motivation. It was hard to make myself sit down and actually write the code sometimes.

### Issues you worked on
- finish the gaps program [#20](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/20)
- schedule co-reqs, taking into account the same gap preferences [#45](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/45)
- print out the courses to the user [#19](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/19)

### Files you worked on
- cgen.cpp: UTK-Class-Scheduling-Assistant/backend/c_code/cgen.cpp
- Support.cpp: UTK-Class-Scheduling-Assistant/backend/c_code/Support.cpp
- Support.h: UTK-Class-Scheduling-Assistant/backend/c_code/Support.h
- lexy_schedule.csv UTK-Class-Scheduling-Assistant/backend/c_code/lexy_schedule.csv

### What you accomplished
- cgen.cpp:
  * This is driver code: all of my functions are wrapped up in here nicely.
- Support.cpp:
  * This was my main contribution!!
  * Last sprint, I left off after checking the pre-reqs. For this sprint, I actually had to finish scheduling the courses.
  * I started by creating a 2D matrix that stored all the times a class was currently scheduled for (0 means the minute is free, 1 means it is taken).
  * Then, I checked to see if the class I wanted to schedule had any time conflicts with any other courses I might've scheduled already.
  * If it didn't, I then checked if other co-reqs needed to be scheduled.
  * If they did - rinse and repeat the program (check for pre-reqs, pass in the last class to determine the time to gap, etc.)
  * If everything passed, hooray! We scheduled a class.
  * If it didn't, move to the next class in the prioirity queue and try to schedule that one. Revert back to the last permanent schedule and try to add on.
  * After scheduling, I popped the class off all vectors where it was stored so that it will not be scheduled again in the future.
  * Once a certain number of credit hours were fulfilled (or we ran out of courses to schedule), it stopped scheduling and printed your schedule to lexy_schedule.csv.
- Support.h:
  * added all my functions here. Had to pass more arguments than expected since I was using global variables at first!
- lexy_schedule.csv
  * This is your schedule, based on what time you want to start, how long you want the time between classes to be, and your current classes!
