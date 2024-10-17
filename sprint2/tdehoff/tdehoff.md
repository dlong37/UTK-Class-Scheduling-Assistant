# Sprint 2 Reflection

**Name:** Tatiana Dehoff <br>
**GitHubID:** tdehoff <br>
**Group Name:** UTK Class Scheduling Assistant

## What I Planned To Do
* Deploy the web app  
* Create a separate static database that holds courses information  
* Populate the courses database with data from a csv file  
* Add functionality to allow users add and view classes in their schedules  
* Allow users perform simple class search and update their schedules from their search results  

## What I Didn't Do
* Web app deployment: still don't have access to forking our repository  
* Didn't fully implement the search feature since it's still unclear whether the rest of our group wants it to be included in the final product

## Problems I Encountered
We don’t have a clear plan for what we need to do and how to do it. There were days when I set aside time for this project but didn’t know what to work on. I also need access to forking our repo or find an alternative (free!) way to deploy our web app.  

## Issues I Worked On
* Deploy web app [#21](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/21)  
* Add new database to store info about all available classes [#6](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/6) [#26](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/26)  
* Populate the database with data from a csv file [#29](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/29) [#30](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/30)  
* Implement search for classes [#27](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/27)  

## Files I Worked On
* backend/models.py  
* backend/views.py  
* backend/__init\__.py  
* backend/read_classes.py  
* backend/classes.csv
* backend/templates/class_search.html  
* backend/templates/main.html  
* backend/templates/view_schedule.html  
* backend/static/css/styles.css  
* backend/static/index.js  

## What I Accomplished
I learned more about SQLite and Flask and successfully connected our web app to a courses database, allowing us to read from and write data to it. I also made progress in implementing basic features for managing class information, which would provide a solid foundation for further development of our project.