# Script to read courses from csv file to database

import csv
import os
from backend import create_app, db
import logging
from backend.models import Course, Weekdays

app = create_app()

days_mapping = {
     'M': Weekdays.Mon,
     'T': Weekdays.Tue,
     'W': Weekdays.Wed,
     'R': Weekdays.Thu,
     'F': Weekdays.Fri,
}

def read_classes_from_csv():
    with app.app_context():
        # classes.csv must be in the same directory with read_classes.py
        base_dir = os.path.dirname(os.path.abspath(__file__))
        csv_file_path = os.path.join(base_dir, 'classes.csv')

        with open(csv_file_path, mode='r') as csvfile:
            reader = csv.DictReader(csvfile)

            for row in reader:
                class_days = row['LcDate']
                parsed_days = []
                for day in class_days:
                    if day in days_mapping:
                        parsed_days.append(days_mapping[day])
                    else:
                        logging.warning(f"Invalid day '{day}' in row {row['name']}. Skipping.")
                          
                new_class = Course(
                    id=row['Id'],
                    abbreviation=row['Abbreviation'],
                    number=row['Number'],
                    title=row['Title'],
                    hours=row['Hours'],
                    class_days=parsed_days,
                )

                db.session.add(new_class)

            db.session.commit()

if __name__ == "__main__":
        read_classes_from_csv()
        print('Classes populated from CSV.')