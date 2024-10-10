# Backend: Database stuff
from . import db
from flask_login import UserMixin
from sqlalchemy.sql import func
from enum import Enum
import json

class Weekdays(Enum):
    __bind_key__ = 'classes'
    Mon = "Mon"
    Tue = "Tue"
    Wed = "Wed"
    Thu = "Thu"
    Fri = "Fri"

class Course(db.Model):
    __bind_key__ = 'classes'    # comes from classes.db
    id = db.Column(db.Integer, primary_key=True)
    abbreviation = db.Column(db.String(4), nullable=False)
    number = db.Column(db.Integer, nullable=False)
    title = db.Column(db.String(50), nullable=False)
    hours = db.Column(db.Integer, nullable=False)
    class_days = db.Column(db.JSON)
#    time = db.Column(db.String(50), nullable=False)
#    credits = db.Column(db.Integer, nullable=False)


# Schema for 'Schedule' database object: have to add semester.
# Cannot establish direct relationship with Course object.
# Will try to hold array of class ids added to this schedule.
class Schedule(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    date = db.Column(db.DateTime(timezone=True), default=func.now())
    
    # Not sure which one will work yet: fix later!
    class_ids = db.Column(db.Integer)
    #class_ids = db.Column(db.JSON)
    
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