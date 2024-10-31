# Sprint 3 Reflection

**Name:** Tatiana Dehoff <br>
**GitHubID:** tdehoff <br>
**Group Name:** UTK Class Scheduling Assistant

## What I Planned To Do
* Deploy the web app  
* Implement course sections search  
* Explore data scraping to expand our classes database with VolCore courses  
* Add functionality to distinguish schedules by semesters (Fall, Sprint, Winter, Summer)  

## What I Didn't Do
* I looked into data scraping, but it turned out to be more complex than I expected and I didn't have time to implement it during this sprint.  
* Add functionality to distinguish schedules by semesters: this would affect our csv files, databases, and C++ code. Our group left is as a "maybe" for the next sprint, as there are higher priority issues we have to resolve first.    

## Problems I Encountered
* The link with class search results that I hoped to use for data scraping doesn't work. I would have to use additional tools that allow enter user input required to go to the desired webpage.  
* It took me some time and several tries to find a free tool for app deployment that's not too limited in resources and supports SQLite databases.  

## Issues I Worked On
* Implement course sections search [#42](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/42)  
* Allow users replace old class section with a new one from class_search page [#47](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/47)  
* Execute backend code with flask [#46](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/46) 
* Explore data scraping to potentially expand classes.db [#43](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/43)  
* Deploy web app [#21](https://github.com/utk-cs340-fall24/UTK-Class-Scheduling-Assistant/issues/21)

## Files I Worked On
* requirements.txt  
* backend/__init\__.py  
* backend/views.py  
* backend/models.py  
* backend/templates/main.html  
* backend/templates/class_search.html 
* backend/templates/view_schedule.html  
* backend/static/index.js  
* backend/static/css/styles.css  
* backend/static/images/search_img.png  


## What I Accomplished
I deployed our web app and made sure it worked exactly the same with what each of us had running locally. Additionally, I helped connecting the Flask part of our application with what Gian and Lexy worked on in C++. I added functionality that allows user to save the generated schedule and apply minor tweaks to it later.  