# Backend for routes to other pages

from flask import Blueprint, render_template, request, flash, jsonify
from flask_login import login_required, current_user
from .models import Schedule, Course
from . import db
import json
import csv
import os

views = Blueprint('views', __name__)

@views.route('/')
def home():
    return render_template("welcome.html", user=current_user)

@views.route('/main', methods=['GET', 'POST'])
@login_required                   # can only be accessed if user is logged in
def main():
    if request.method == 'POST':
        input = request.form.get('class_ids')
        if not input:
            flash('Nothing added.', category='error')
        else:
            class_ids = list(map(int, input.split(',')))
            new_schedule = Schedule(class_ids=class_ids, user_id = current_user.id)
            db.session.add(new_schedule)
            db.session.commit()
            flash('Schedule added!', category='success')

    return render_template("main.html", user=current_user)

@views.route('/schedule/<int:schedule_id>', methods=['GET'])
@login_required
def view_schedule(schedule_id):
    # Fetch the schedule and verify it belongs to the current user
    schedule = Schedule.query.filter_by(id=schedule_id, user_id=current_user.id).first()

    if not schedule:
        flash('Error loading schedule.', category='error')
        return render_template("main.html", user=current_user)
    
    class_ids = schedule.class_ids
    courses = Course.query.filter(Course.id.in_(class_ids)).all()
    return render_template('view_schedule.html', schedule=schedule, courses=courses, user=current_user)


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
    seq_1 = request.form.get('sequence-1')
    seq_2 = request.form.get('sequence-2')
    seq_3 = request.form.get('sequence-3')
    seq_4 = request.form.get('sequence-4')
    seq_5 = request.form.get('sequence-5')
    elective_credits = request.form.getlist('elective-credit')
    credit_hours = request.form.get('credit-hours')
    mwf_start_time = request.form.get('MWF-start-time')
    tr_start_time = request.form.get('TR-start-time')

    # Prepare data for CSV
    data_entries = [
        [core_class],
        [seq_1],
        [seq_2],
        [seq_3],
        [seq_4],
        [seq_5],
    ]

    # Add elective credits as separate entries
    for credit in elective_credits:
        data_entries.append([credit])
    
    # Add other data
    data_entries.append([credit_hours])
    data_entries.append([mwf_start_time])
    data_entries.append([tr_start_time])

    # Defines the directory where the csv file will be saved
    directory = 'courses_generator'

    # Create the directory if it doesn't exist
    if not os.path.exists(directory):
        os.makedirs(directory)

    # Write to CSV file
    with open(os.path.join(directory, 'data.csv'), mode='a', newline='') as file:
        writer = csv.writer(file)
        for entry in data_entries:
            writer.writerow(entry)

    return 'Data saved successfully!'