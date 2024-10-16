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
    sequence_classes = [
        request.form.get('sequence-1'),
        request.form.get('sequence-2'),
        request.form.get('sequence-3'),
        request.form.get('sequence-4'),
        request.form.get('sequence-5'),
    ]
    elective_credits = request.form.getlist('elective-credit')
    credit_hours = request.form.get('credit-hours')
    mwf_start_time = request.form.get('MWF-start-time')
    tt_start_time = request.form.get('TT-start-time')

    # Prepare data for CSV
    data = [
        core_class,
        *sequence_classes,
        ','.join(elective_credits),
        credit_hours,
        mwf_start_time,
        tt_start_time
    ]

    # Write to CSV file
    with open('data.csv', mode='a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(data)

    return 'Data saved successfully!'

if __name__ == '__main__':
    app.run(port=3000, debug=True)
