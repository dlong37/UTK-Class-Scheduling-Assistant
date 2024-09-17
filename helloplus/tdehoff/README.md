# Simple Task Manager Web App

## Overview

This is a simple task manager web application built using Flask, a lightweight and flexible web framework for Python. Flask supports various databases, including SQLite, which makes it suitable for our project implementation. I built this following the tutorial provided by [Traversy Media](https://youtu.be/Z1RJmh_OqeA?si=Hd55xoKd9kO500FF).

## Setup and Installation

1. Clone the repository
1. Install virtualenv using pip:  
``pip install virtualenv``  
1. Inside the **tdehoff** directory, create and activate a virtual environment:  
``virtualenv env``  
``source env/bin/activate``  
1. Install dependencies:  
``pip install -r requirements.txt``  
1. Initialize the database:  
``python init_db.py``  
1. Run the app:  
``python app.py``  
1. Access the web page:  
Open your browser and go to ``http://localhost:5000/``  

## Note

I really hope this works! I looked for MySQL tutorials and found this Flask approach. If you have any suggestions for other tools or technologies, I’m more than open to use them.
