# Backend for user authentication functionality

from flask import Blueprint, render_template, request, flash, redirect, url_for
from .models import User
from werkzeug.security import generate_password_hash, check_password_hash
from . import db
from flask_login import login_user, login_required, logout_user, current_user

auth = Blueprint('auth', __name__)

# Log in
@auth.route('/login', methods=['GET', 'POST'])
def login():
    # Get user credentials from the log in form
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')

        # Search the database for a user with the provided email
        user = User.query.filter_by(email=email).first()    # use first result
        # If user found, compare passwords:
        if user:
            if check_password_hash(user.password, password):
                # Notify the user and go to the main page if successful
                flash('Logged in successfully!', category='success')
                login_user(user, remember=True)             # remember the user is logged in
                return redirect(url_for('views.main'))      # main route inside of views file
            else:
                flash('Incorrect password, try again.', category='error')
        else:
            flash('Email does not exist.', category='error')

    return render_template("login.html")

# Log out
@auth.route('/logout')
@login_required         # can only be accessed if user is logged in
def logout():
    logout_user()
    # Return to the log in page
    return redirect(url_for('auth.login'))

# Register
@auth.route('sign_up', methods=['GET', 'POST'])
def sign_up():
    if request.method == 'POST':
        email = request.form.get('email')
        name = request.form.get('name')
        password = request.form.get('password')

        # Error check if there is a user with the same email
        user = User.query.filter_by(email=email).first()
        if user:
            flash('User with this email already exists.', category='error')
        # Add more error checks
        elif len(email) < 4:
            flash('Email must be greater than 3 characters.', category='error')
        elif len(name) < 2:
            flash('Name must be greater than 1 character.', category='error')
        else:
            # Create a new user.
            # sha256 is a hashing algorithm, can be replaced.
            new_user = User(email=email, name=name, password=generate_password_hash(password, method='pbkdf2:sha256'))
            db.session.add(new_user)
            db.session.commit()
            # Notify the user and return to the welcome page if successful
            flash('Account created!', category='success')
            return redirect(url_for('views.home'))    # home route inside of views file

    return render_template("register.html")
