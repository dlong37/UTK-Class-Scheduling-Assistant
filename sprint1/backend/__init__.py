from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from os import path
from flask_login import LoginManager

db = SQLAlchemy()
DB_NAME = "database.db"

# Initialize web app
def create_app():
    app = Flask(__name__)
    # Used for password hashing
    app.config['SECRET_KEY'] = 'bdqjfbkwbfjknjkwn'

    # Database is created in backend/instance directory
    app.config['SQLALCHEMY_DATABASE_URI'] = f'sqlite:///{DB_NAME}'
    db.init_app(app)

    from .views import views
    from .auth import auth

    app.register_blueprint(views, url_prefix='/')
    app.register_blueprint(auth, url_prefix='/')

    # Import database objects: may need to add more
    from .models import User, Schedule

    create_database(app)

    login_manager = LoginManager()
    login_manager.login_view = 'auth.login'
    login_manager.init_app(app)

    @login_manager.user_loader
    def load_user(id):
        return User.query.get(int(id))

    return app

# Check if database exists. If not - create one.
def create_database(app):
    if not path.exists('backend/' + DB_NAME):
        with app.app_context():
            db.create_all()
            print('New Database Created.')