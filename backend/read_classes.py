# Script to read courses from csv file to database

import csv
import os
from backend import create_app, db

app = create_app()

def read_classes_from_csv():
    from backend.models import Course
    with app.app_context():
        # classes.csv must be in the same directory with read_classes.py
        base_dir = os.path.dirname(os.path.abspath(__file__))
        csv_file_path = os.path.join(base_dir, 'classes.csv')

        with open(csv_file_path, mode='r') as csvfile:
            reader = csv.DictReader(csvfile)

            for row in reader:
                new_class = Course(
                    id=row['id'],
                    name=row['name'],
                    description=row['description'],
                )

                db.session.add(new_class)

            db.session.commit()

if __name__ == "__main__":
        read_classes_from_csv()
        print('Classes populated from CSV.')