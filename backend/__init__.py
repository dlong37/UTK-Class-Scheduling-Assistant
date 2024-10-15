from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager
from flask_migrate import Migrate

from os import path

db = SQLAlchemy()
DB_NAME = "database.db"
CLASSES_DB_NAME = "classes.db"

# Initialize web app
def create_app():
    app = Flask(__name__)
    # Used for password hashing
    app.config['SECRET_KEY'] = 'bdqjfbkwbfjknjkwn'

    # Database is created in backend/instance directory
    app.config['SQLALCHEMY_DATABASE_URI'] = f'sqlite:///{DB_NAME}'
    app.config['SQLALCHEMY_BINDS'] = {'classes': f'sqlite:///{CLASSES_DB_NAME}'}

    db.init_app(app)
    migrate = Migrate(app, db)

    from .views import views
    from .auth import auth

    app.register_blueprint(views, url_prefix='/')
    app.register_blueprint(auth, url_prefix='/')

    # Import database objects: may need to add more
    from .models import User, Schedule, Course

    create_database(app)

    login_manager = LoginManager()
    login_manager.login_view = 'auth.login'
    login_manager.init_app(app)

    @login_manager.user_loader
    def load_user(id):
        return User.query.get(int(id))

    return app

def create_database(app):
    # Check if user database exists
    if not path.exists('instance/' + DB_NAME):
        with app.app_context():
            db.create_all()
            print('New User Database Created.')
