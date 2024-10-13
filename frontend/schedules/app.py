from flask import Flask, request, render_template
import csv

app = Flask(__name__)

# Serve the HTML file
@app.route('/')
def index():
    return render_template('schedules.html')

# Handle form submission
@app.route('/submit', methods=['POST'])
def submit():
    core_class = request.form.get('core-class')
    elective_credits = request.form.getlist('elective-credit')

    # Prepare data for CSV
    data = [core_class, ','.join(elective_credits)]

    # Write to CSV file
    with open('data.csv', mode='a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(data)

    return 'Data saved successfully!'

if __name__ == '__main__':
    app.run(port=3000, debug=True)
