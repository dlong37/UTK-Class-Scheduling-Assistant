# Backend for routes to other pages

from flask import Blueprint, render_template, request, flash, jsonify, redirect, url_for, send_from_directory
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
            if old_class_id in schedule.class_ids:
                schedule.class_ids.remove(old_class_id)
                schedule.class_ids.append(new_class_id)

                db.session.commit()
                return jsonify(success=True)

    return jsonify(success=False)

# Schedule Questionnaire
@views.route('/new_schedule')
@login_required
def index():
    return render_template('questionnaire.html')

# Handle form submission
@views.route('/submit', methods=['POST'])
@login_required
def submit():
    print(f"SUBMIT start")
    default = 'MATH 130'
    core_class = request.form.get('core-class')
    seq_1 = request.form.get('sequence-1')
    seq_2 = request.form.get('sequence-2')
    math_credits = request.form.getlist('math-credit')
    seq_3 = request.form.get('sequence-3')
    seq_4 = request.form.get('sequence-4')
    cs_credits = request.form.getlist('cs-credit')
    cs361_credit = request.form.get('cs361-credit')
    elective_credits = request.form.getlist('elective-credit')
    credit_hours = request.form.get('credit-hours')
    start_time = request.form.get('start-time')

    # Prepare data for CSV
    data_entries = [
        [default],
        [core_class],
        [seq_1],
        [seq_2],
    ]

    # Add all math credits as separate entries
    for credit in math_credits:
        data_entries.append([credit])

    data_entries.append([seq_3])
    data_entries.append([seq_4])

    # Add CS credits as separate entries
    for credit in cs_credits:
        data_entries.append([credit])

    # Add elective credits as separate entries
    for credit in elective_credits:
        data_entries.append([credit])
    
    # Add other data
    data_entries.append([cs361_credit])
    data_entries.append([credit_hours])
    data_entries.append([start_time])

    # Defines the directory where the csv file will be saved
    directory = 'backend/c_code'

    # Create the directory if it doesn't exist
    if not os.path.exists(directory):
        os.makedirs(directory)

    # Write to CSV file
    with open(os.path.join(directory, 'data.csv'), mode='w', newline='') as file:
        writer = csv.writer(file, lineterminator='\n')
        for entry in data_entries:
            writer.writerow(entry)

    if os.path.exists("backend/c_code/cgen"):
        cpp_executable_path = 'backend/c_code/cgen'
    else:
        cpp_executable_path = os.path.abspath('UTK-Class-Scheduling-Assistant/backend/c_code/cgen')
    file1_path = os.path.join('backend', 'c_code', 'eecs_courses.csv')
    file2_path = os.path.join('backend', 'c_code', 'major_courses.csv')
    file3_path = os.path.join('backend', 'c_code', 'data.csv')
    mode = 'location'

    command = [cpp_executable_path, file1_path, file2_path, file3_path, mode]

    try:
        result = subprocess.run(command, capture_output=True, text=True)
        
        # Collect output and error
        if result.returncode == 0:
            output = result.stdout.strip()
            print(f"Raw output from C++ program: {output}")
            error = None

            class_ids = list(map(int, output.splitlines()))
            print(f"Parsed Class IDs: {class_ids}")

            # Instead of writing output into a csv file, I create a new Schedule object with 
            # returned class ids
            # new_schedule = Schedule(class_ids=class_ids, user_id=current_user.id)
            # db.session.add(new_schedule)
            # db.session.commit()

            # courses = Course.query.filter(Course.id.in_(class_ids)).all()
            # return render_template('view_schedule.html', schedule=new_schedule, courses=courses, user=current_user)

            courses = Course.query.filter(Course.id.in_(class_ids)).all()

            # Specify the directory to save the CSV file
            directory = 'backend/static'

            # Write the course data to a CSV file
            with open(os.path.join(directory, 'schedule.csv'), mode='w', newline='') as file:
                writer = csv.writer(file)
                # Write the header
                writer.writerow(['ID', 'Abbreviation', 'Number', 'Title', 'Credit_Hours', 
                                'Lecture_Time', 'Lecture_Days', 'Lecture_Location', 
                                'Lab_Time', 'Lab_Days', 'Lab_Location'])
                
                # Write the data for each course
                for entry in courses:
                    writer.writerow([
                        entry.id,
                        entry.abbreviation,
                        entry.number,
                        entry.title,
                        entry.credit_hours,
                        entry.lecture_time,
                        entry.lecture_days,
                        entry.lecture_location,
                        entry.lab_time,
                        entry.lab_days,
                        entry.lab_location
                    ])
        else:
            output = None
            error = result.stderr

        # Render a new HTML page with output as context variable
        return redirect(url_for('views.generate'))
        # return render_template('output.html', courses=courses, error=error)
        # return render_template('output.html', courses=courses, error=error)

    except Exception as e:
        return render_template('output.html', output=None, error=str(e))

@views.route('/generated_schedule', methods=['GET'])
@login_required
def generate():
    return render_template('generated_schedule.html')
