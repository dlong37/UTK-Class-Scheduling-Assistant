# Script to read courses from csv file to database

import csv
import os
from backend import create_app, db
import logging
from backend.models import Course
from datetime import datetime

app = create_app()
CLASSES_DB_NAME = "classes.db"

# Format time string before recording it in the database
def format_time(time_str):
    start_time, end_time = time_str.split('-')
    start = datetime.strptime(start_time, "%H%M")
    end = datetime.strptime(end_time, "%H%M")
    formatted_time = f"{start.strftime('%I:%M %p')} - {end.strftime('%I:%M %p')}"
    return formatted_time

# Write courses from csv to db
def read_classes_from_csv():
    with app.app_context():
        # classes.csv must be in the same directory with read_classes.py
        base_dir = os.path.dirname(os.path.abspath(__file__))
        csv_file_path = os.path.join(base_dir, 'classes.csv')

        with open(csv_file_path, mode='r') as csvfile:
            reader = csv.DictReader(csvfile)

            for row in reader:
                new_class = Course(
                    abbreviation=row['Abbreviation'],
                    number=row['Number'],
                    title=row['Title'],
                    credit_hours=row['Hours'],
                    lecture_time=format_time(row['LcTime']) if row['LcTime'] != 'none' else "",
                    lecture_days=row['LcDate'] if row['LcDate'] != 'none' else "",
                    lecture_location=row['LcLocation'] if row['LcLocation'] != 'none' else "",
                    lab_time=format_time(row['LaTime']) if row['LaTime'] != 'none' else "",
                    lab_days=row['LaDate'] if row['LaDate'] != 'none' else "",
                    lab_location=row['LaLocation'] if row['LaLocation'] != 'none' else ""
                )

                db.session.add(new_class)

            db.session.commit()

if __name__ == "__main__":
    # Check if the classes database already exists
    if not os.path.exists(f'instance/{CLASSES_DB_NAME}'):
        with app.app_context():
            db.create_all(bind_key="classes")
            print('New Classes Database Created.')
     
        read_classes_from_csv()
        print('Classes populated from CSV.')
    else:
        print(f"Database {CLASSES_DB_NAME} already exists.")