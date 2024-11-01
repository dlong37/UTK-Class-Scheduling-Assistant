# Sprint 3

> COSC 340 - Sprint 3 Reflection

**Name:** Ethan Miller <br>
**GitHub ID:** EthBeats <br>
**Group Name:** UTK-Class-Scheduling-Assistant


### What you planned to do
* Design a UI for the generated schedule page [#32](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/32)
* Improve the design of the main page [#40](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/40)
* Integrate the generated schedule page with the main page [#41](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/41)

### What you did not do
> I wasn't able to integrate the generated schedule page directly to the main page. Instead, I connected it to a schedule questionnaire. I also wasn't able to improve the main page as much as I had hoped this sprint.

### What problems you encountered
> I had problems displaying the class schedule correctly on the UI. More specifically, I had trouble with classes spanning incorrectly across the time slots on the table.

### Issues you worked on
* [#32](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/32) Design UI for Generated Schedule Page
* [#40](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/40) Improve Design of Main Page
* [#41](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/41) Integrate Generated Schedule Page with the Main Page

### Files you worked on
* UTK-Class-Scheduling-Assistant/backend/templates/generated_schedule.html
* UTK-Class-Scheduling-Assistant/backend/static/css/styles.css
* UTK-Class-Scheduling-Assistant/backend/static/generated_schedule.js
* UTK-Class_Scheduling_Assistant/backend/views.py

### What you accomplished
> I was successfully able to design the UI for our generated schedule page that shows users their generated schedule from the questionnaire. The schedule is displayed in a table (days as columns and rows as times) that gives users a visual of how their schedule spans each week. I was also able to connect this page with the questionnaire so that users are redirected to it after submitting the form. The generated schedule is also saved in the user database so users can view their schedules after logging back in.
