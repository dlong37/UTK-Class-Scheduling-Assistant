# Backend for routes to other pages

from flask import Blueprint, render_template, request, flash, jsonify, redirect, url_for
from flask_login import login_required, current_user
from .models import Schedule, Course
from . import db
import json
import csv
import os
import subprocess

views = Blueprint('views', __name__)

# Welcome page
@views.route('/')
def home():
    return render_template("welcome.html", user=current_user)

# Main: user's schedules list
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

# Display classes in selected schedule
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

# Delete schedule from the main page
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

# Search selected course sections
@views.route('/class_search', methods=['GET', 'POST'])
@login_required
def class_search():
    abbreviation = request.args.get('abbreviation')
    number = request.args.get('number')
    schedule_id = request.args.get('schedule_id')
    class_id = request.args.get('class_id')
    # For debugging: remove later
    print(f"Search term: '{abbreviation}{number}', class_id: {class_id}")
    classes = Course.query

    if abbreviation and number:
        results = classes.filter(Course.abbreviation == abbreviation, Course.number == number)

    return render_template("class_search.html", classes=results, user=current_user, schedule_id=schedule_id, class_id=class_id)

# Update schedule course with a search result
@views.route('/replace_class', methods=['POST'])
@login_required
def replace_class():
    data = json.loads(request.data)

    schedule_id = int(data['scheduleId'])
    old_class_id = int(data['oldClassId'])
    new_class_id = int(data['newClassId'])

    schedule = Schedule.query.get(schedule_id)
    
    if schedule:
        if schedule.user_id == current_user.id:
            # For debugging: remove later
            print(f"Class ids: {schedule.class_ids}")
            if old_class_id in schedule.class_ids:
                # For debugging: remove later
                print(f"Old class id: {old_class_id}, new class id: {new_class_id}")

                schedule.class_ids.remove(old_class_id)
                schedule.class_ids.append(new_class_id)
                
                # For debugging: remove later
                print(f"Class ids: {schedule.class_ids}")

                db.session.commit()
                return jsonify(success=True)

    return jsonify(success=False)

# Schedule Questionnaire
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
    directory = 'backend/c_code'

    # Create the directory if it doesn't exist
    if not os.path.exists(directory):
        os.makedirs(directory)

    # Write to CSV file
    with open(os.path.join(directory, 'data.csv'), mode='w', newline='') as file:
        writer = csv.writer(file)
        for entry in data_entries:
            writer.writerow(entry)

    cpp_executable_path = os.path.join('backend', 'c_code', 'loc')
    file1_path = os.path.join('backend', 'c_code', 'eecs_courses.csv')
    file2_path = os.path.join('backend', 'c_code', 'major_courses.csv')
    file3_path = os.path.join('backend', 'c_code', 'taken_courses.csv')

    command = [cpp_executable_path, file1_path, file2_path, file3_path]

    try:
        result = subprocess.run(command, capture_output=True, text=True)
        
        # Collect output and error
        if result.returncode == 0:
            output = result.stdout
            error = None
        else:
            output = None
            error = result.stderr

        # Render a new HTML page with output as context variable
        return redirect(url_for('views.generate'))
        #return render_template('output.html', output=output, error=error)

    except Exception as e:
        return render_template('output.html', output=None, error=str(e))

@views.route('/generated_schedule', methods=['GET'])
@login_required
def generate():
    return render_template('generated_schedule.html')
