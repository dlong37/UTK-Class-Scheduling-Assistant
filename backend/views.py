# Backend for routes to other pages

from flask import Blueprint, render_template, request, flash, jsonify
from flask_login import login_required, current_user
from .models import Schedule, Course
from . import db
import json
import csv

views = Blueprint('views', __name__)

@views.route('/')
def home():
    return render_template("welcome.html", user=current_user)

@views.route('/main', methods=['GET', 'POST'])
@login_required                   # can only be accessed if user is logged in
def main():
    # if request.method == 'POST':
    #     schedule = request.form.get('schedule')
        
    #     if len(schedule) < 1:
    #         flash('Nothing added.', category='error')
    #     else:
    #         new_schedule = Schedule(data=schedule, user_id = current_user.id)
    #         db.session.add(new_schedule)
    #         db.session.commit()
    #         flash('Schedule added!', category='success')

    return render_template("main.html", user=current_user)

@views.route('/delete-schedule', methods=['POST'])
def delete_schedule():
    schedule = json.loads(request.data)
    scheduleId = schedule['scheduleId']
    schedule = Schedule.query.get(scheduleId)
    if schedule:
        if schedule.user_id == current_user.id:
            db.session.delete(schedule)
            db.session.commit()
    
    return jsonify({})

@views.route('/class_search', methods=['GET', 'POST'])
@login_required
def class_search():
    search_term = request.args.get('search')
    # For debugging: remove later
    print(f"Search term: '{search_term}'")
    classes = Course.query

    if (search_term):
        classes = classes.filter(Course.abbreviation.ilike(f'%{search_term}%'))  # Filter the query

    results = classes.limit(10).all()  # Limit to 10 results and execute
    # For debugging: remove later
    print(f"Classes found: {len(results)}")

    return render_template("class_search.html", classes=results, user=current_user)

@views.route('/schedules')
@login_required
def index():
    return render_template('schedules.html')

# Handle form submission
@views.route('/submit', methods=['POST'])
@login_required
def submit():
    core_class = request.form.get('core-class')
    elective_credits = request.form.getlist('elective-credit')

    # Prepare data for CSV
    data = [core_class, ','.join(elective_credits)]

    # Write to CSV file
    with open('data.csv', mode='a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(data)

    return 'Data saved successfully!'