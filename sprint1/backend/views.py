# Backend for routes to other pages

from flask import Blueprint, render_template
from flask_login import login_required, current_user

views = Blueprint('views', __name__)

@views.route('/')
def home():
    return render_template("welcome.html")

@views.route('/main')
@login_required         # can only be accessed if user is logged in
def main():
    return render_template("main.html")