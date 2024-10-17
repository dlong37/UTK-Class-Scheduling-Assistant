# Sprint 2

Name: Lexy Andershock</br>
GitHub ID: acandershock</br>
Group Name: UTK-Class-Scheduling-Assistant</br>

### What you planned to do
- update the major.csv file to include more classes (like EF + MATH, not just COSC) [#18](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/18)
- create a class scheduler that optimizes + schedules courses based on the gaps between classes (the duration of which is specified by the user) [#20](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/20)
- print out a schedule to a csv file [#19](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/19)

### What you did not do
- I was not able to complete issue [#20](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/20) in its entirety or issue [#19](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/19). However, I was able to make progress on both of the issues and took several steps towards these goals. As a result, they have now been pushed back as sprint 3's goals.

### What problems you encountered
- I realized I needed a vector that sorted out all of the remaining courses for scheduling from the original major_courses vector, which had not been done in the previous sprint. I also needed to store all the data from eecs_courses.csv to actually schedule the classes, so I did that as well.
- Originally, I had wanted to make a weighted graph and use Dijkstra's algorithm to schedule the classes; however, I realized this was not possible since some courses have co-reqs which require them to be scheduled concurrently. To fix this, I implemented a minium priority queue to weight courses based on their availibity + scheduled them that way (issue [#34](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/34)). This also required me to create a formula to prioritize the classes based on time, and I also needed to add a priority attribute to the course class.
- I had to update our eecs_courses.csv file to create a grammar for distinguishing between pre-reqs that must be explicity satisified ('&') or pre-reqs in a sequence where only one course had to be satisfied ('|').

### Issues you worked on
- update the major.csv file to include more classes (like EF + MATH, not just COSC) [#18](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/18)
- implemented a minium priority queue to weight courses [#34](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/34)
- checked classes for satisfaction of pre-reqs [#35](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/35)
  * Even though a course might have a high priority, I might not be able to take it due to pre-reqs, so I checked for that

### Files you worked on
- eecs_courses.csv: UTK-Class-Scheduling-Assistant/backend/generator_gaps/eecs_courses.csv
- major_courses.csv: UTK-Class-Scheduling-Assistant/backend/generator_gaps/major_courses.csv
- taken_courses.csv: UTK-Class-Scheduling-Assistant/backend/generator_gaps/taken_courses.csv
- taken_courses_2.csv: UTK-Class-Scheduling-Assistant/backend/generator_gaps/taken_courses_2.csv
- taken_courses_3.csv: UTK-Class-Scheduling-Assistant/backend/generator_gaps/taken_courses_3.csv
- gaps.cpp: UTK-Class-Scheduling-Assistant/backend/generator_gaps/gaps.cpp

### What you accomplished
- eecs_courses.csv: UTK-Class-Scheduling-Assistant/backend/generator_gaps/eecs_courses.csv
   * added a grammar to account for types of pre-reqs - those that must be explicity satisified ('&') or pre-reqs in a sequence where only one course had to be satisfied ('|').
- major_courses.csv: UTK-Class-Scheduling-Assistant/backend/generator_gaps/major_courses.csv
  * updated major_courses to include more required classes in the major, like MATH + EF (not just COSC).
  * also wrote new code that no longer needs this list to be in order (orginally, we were going to automatically schedule the course in the first index of major_vector, but I modified it so now any class can be scheduled as long as its pre-reqs are satisifed.
- taken_courses.csv: UTK-Class-Scheduling-Assistant/backend/generator_gaps/taken_courses.csv
- taken_courses_2.csv: UTK-Class-Scheduling-Assistant/backend/generator_gaps/taken_courses_2.csv
- taken_courses_3.csv: UTK-Class-Scheduling-Assistant/backend/generator_gaps/taken_courses_3.csv
  * All of these files are example schedules that students might input into the program. They demonstrate the scope of the course scheduler.
- gaps.cpp: UTK-Class-Scheduling-Assistant/backend/generator_gaps/gaps.cpp
  * This was my major contribution to the project. Within this program, the ideas are described above are implemented, such as:
     * sorting and pulling data from eecs_courses.csv for all remaining courses
     * asking the user for their desired start time + amount of the time they would like between classes
     * creating a priority ranking system to organize courses in a minimum priority queue, based on how closely they align with the user's desired starting time + already scheduled courses
     * checking courses to ensure their pre-reqs have been satisfied before attempting to schedule them
