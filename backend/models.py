# Backend: Database stuff
from . import db
from flask_login import UserMixin
from sqlalchemy.sql import func
from enum import Enum
#import json

# class Weekdays(Enum):
#     __bind_key__ = 'classes'
#     Mon = "Mon"
#     Tue = "Tue"
#     Wed = "Wed"
#     Thu = "Thu"
#     Fri = "Fri"

class Course(db.Model):
    __bind_key__ = 'classes'    # comes from classes.db
    id = db.Column(db.Integer, primary_key=True)
    abbreviation = db.Column(db.String(4), nullable=False)
    number = db.Column(db.Integer, nullable=False)
    title = db.Column(db.String(50), nullable=False)
    credit_hours = db.Column(db.Integer, nullable=False)
    lecture_time = db.Column(db.String(10))
    lecture_days = db.Column(db.String(5))
    lecture_location = db.Column(db.String(5))
    lab_time = db.Column(db.String(10))
    lab_days = db.Column(db.String(5))
    lab_location = db.Column(db.String(5))


# Schema for 'Schedule' database object: have to add semester.
class Schedule(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    date = db.Column(db.DateTime(timezone=True), default=func.now())
    class_ids = db.Column(db.JSON, nullable=False)
    
    # Associate with a user object:
    user_id = db.Column(db.Integer, db.ForeignKey('user.id'))


# Schema for 'User' database object: what user info do we want to store?
class User(db.Model, UserMixin):
    id = db.Column(db.Integer, primary_key=True)    # Unique for each object
    email = db.Column(db.String(150), unique=True)  # 150 chars max, must be unique
    password = db.Column(db.String(150))
    name = db.Column(db.String(150))
    # List of created schedules
    schedules = db.relationship('Schedule')