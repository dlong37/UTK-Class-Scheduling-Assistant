# Sprint 1

Name: Lexy Andershock</br>
GitHub ID: acandershock</br>
Group Name: UTK-Class-Scheduling-Assistant</br>

### What you planned to do
- create a course csv file [#7](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/7)
- create README / documentation [#8](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/8)
- create BST for sorting [#9](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/9)
- color parent nodes for pre-req tracking [#10](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/10)
- remove duplicate courses when printing [#11](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/11)

### What you did not do
- I did not create a BST or color parent nodes. Instead we created a vector because there were multiple parent nodes (see next section)
- We did not generate an actual schedule; instead, we just listed the pre-reqs (which is a neccesary first step). We will focus on this in sprint 2.
- We did not expand the csv file beyond the computer science major. We might save this for later, since it's just data entry.

### What problems you encountered
- We had to pivot from creating a BST to creating a set since we ran into the issue of the course strucutre not following a BST format. For example, a course might need two pre-reqs, so it would need more than one parent, which violates the BST structure.
  * therefore, issues [#9](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/9) and [#10](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/10) were closed in favor of a different approach: creating a taken courses vector [#14](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/14)
- We had to punt the idea of weighing the classes based on difficulty, since we have no way of weighing classes we have not yet taken.

### Issues you worked on
- Create partial csv file for class data [#7](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/7)
- Create README for eecs.csv [#8](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/8)
- Remove Duplicates in Taken Courses List [#11](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/11)

### Files you worked on
- read_data.cpp: UTK-Class-Scheduling-Assistant/sprint1/backend/courses_generator/read_data.cpp
- eecs.csv: UTK-Class-Scheduling-Assistant/sprint1/backend/courses_generator/eecs_courses.csv
- README.md: UTK-Class-Scheduling-Assistant/sprint1/backend/courses_generator/README.md

### What you accomplished
- Created a csv file:
  * This portion probably took the longest. We listed all the courses required by the computer science major, then copied over every course offered in the Fall '22 and Spring '23
    course catalog.
  * This took several hours since we manually had to search the UT database for all of the attributes, including course abbreviation, number, title, hours, attributes, pre-requisites, co-requisites, lecture time, lecture date, lecture location, lab time, lab date, and lab location.
- Listed pre-reqs:
  * Then, we made a program that did something with this data.
  * My main contribution was writing the code that read in the data from the csv file into a vector that held custom class objects with all of the properties listed above.
  * Then, Gian searched the vector for the core major classes and listed out the pre-reqs by doing a linear search on the pre-req attribute.
  * So, the program now prints to the terminal all of the pre-reqs that are required for a user to have taken a class. They can specify which courses they want to list the pre-reqs for in a csv file which will be read in on the command line.
