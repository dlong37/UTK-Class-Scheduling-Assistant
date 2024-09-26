# Backend: Database stuff
from . import db
from flask_login import UserMixin
from sqlalchemy.sql import func

# Schema for 'Schedule' database object: what do we want to store?
# We might populate 'Schedule' object with some other kind of objects, like 'Class'
class Schedule(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    # Data string for testing
    data = db.Column(db.String(1000))
    # In case we need to store the current date and time for anything:
    date = db.Column(db.DateTime(timezone=True), default=func.now())
    # Associate with a user object:
    user_id = db.Column(db.Integer, db.ForeignKey('user.id'))
    # classes = db.relationship('Class')

# Lookup how many-to-one/many-to-many?? relationship is set up: many schedules may have the same class
# class Class(db.Model):
#    id = db.Column(....)
#    ....
#    schedule_id = db.Column(db.Integer, db.ForeignKey('schedule.id'))


# Schema for 'User' database object: what user info do we want to store?
class User(db.Model, UserMixin):
    id = db.Column(db.Integer, primary_key=True)    # Unique for each object
    email = db.Column(db.String(150), unique=True)  # 150 chars max, must be unique
    password = db.Column(db.String(150))
    name = db.Column(db.String(150))
    # List of created schedules
    schedules = db.relationship('Schedule')