# Sprint 2 Reflection

**Name:** David Long <br>
**GitHubID:** dlong37 <br>
**Group Name:** UTK Class Scheduling Assistant

## What I Planned To Do
* Create a questionnaire form for the user
* Transfer answers from question form to CSV file
* Improve the overall aesthetic look of the schedules page

## What I Didn't Do
* Not sure if there are more questions that need to be added to the form.
* Wasn't able to connect with Gian and Lexy's program since they aren't finished with it.

## Problems I Encountered
I had problems when it came to how to transfer the HTML form answers to a CSV file. I initially was using Node.js as my backend to do this process, but I had forgotten that Tatiana had set up Flask as our overall environment. I had to work on doing this same procedure with Flask then, which wasn't hard but it ate up more of my time. I also ran into issues of formatting the data in the CSV file, but with time I was able to figure it out.

## Issues I Worked On
* [#23](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/23): Develop Questionnaire for UI
* [#24](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/24): Improve Schedules Page
* [#31](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/31): Transfer Answers to Questionnaire Form to CSV File

## Files I Worked On
#### Designing the Schedule Questionnaire Page on Frontend
* UTK-Class-Scheduling-Assistant/sprint1/frontend/schedules/templates/schedules.html
* UTK-Class-Scheduling-Assistant/sprint1/frontend/schedules/static/schedules.css
* UTK-Class-Scheduling-Assistant/sprint1/frontend/schedules/static/schedules.js
* UTK-Class-Scheduling-Assistant/sprint1/frontend/schedules/app.py

## What I Accomplished
I was able to accomplish producing a fully functional question form prompting the user for answers, and I was able to transfer these answers to a CSV file for the backend C++ programs to use when filtering out classes to be generated. I also was able to gain more experience with JavaScript and Python/Flask in this process.