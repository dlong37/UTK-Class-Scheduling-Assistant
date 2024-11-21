# UTK Class Scheduling Assistant
![Alt text](frontend/logo.png)

## Group member names & github ID's
* David Long: dlong37
* Ethan Miller: EthBeats
* Tatiana Dehoff: tdehoff
* Alexa Andershock: acandershock
* Gian Fernandez-Aleman: gfernan5

## Product Description
The UTK Class Scheduling Assistant (CSA) simplifies the stressful class scheduling process by automatically generating a personalized schedule based on a student's degree path. It takes into account core coursework, time conflicts, credit hours, electives, and factors like class location and preferred class timings. It creates efficient schedules with classes close to each other if the user specifies location based generation. If the user specifies time based generation it allows students to customize start times and breaks between classes.

## How to Run (Local)
1. Install dependencies:  
```pip install -r requirements.txt```
1. If you don't have a database with classes:   
``` python3 -m backend.read_classes ```
1. Start the server:
```python3 main.py```
1. Open your browser and navigate to http://localhost:5000 to access the web app.

## How to Run (Website)
1. Navigate to https://utkclassscheduler.pythonanywhere.com

## How to Use

* Start by hitting the "Get Started" button or the "Login/Register" Button
* Click on "Don't Have An Account? Register Here" button
* Sign up with your name, email and password
* You'll be redirected to the home page, click on the "Get Started" button or the "Login/Register" Button, and log in using your email and password
* Click the "Create Now" button under "Generate a New Schedule"
* Use the drop downs and check boxes to select any classes you've already taken
* Select the amount of credit hours you're looking to take
* Select location or time generation preference (if you select time, select the time you want to start classes and how long you want your breaks to be)
* Hit "Submit"
* You can hit regenerate as many times as you'd like
* Once you have a schedule you're satisfied with, hit "Save"
* You can now view or delete your saved schedule
* Hit "View" on the schedule you saved to view section information
* You can hit the magnifying glass to look at other sections for that class and swap it out if you'd like by hitting the "Replace with this Section" button
* You can continue messing around with it if you'd like :)

## License
This project is licensed under the [LICENSE](License.txt) file.
