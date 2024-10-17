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
    seq_1 = request.form.get('sequence-1')
    seq_2 = request.form.get('sequence-2')
    seq_3 = request.form.get('sequence-3')
    seq_4 = request.form.get('sequence-4')
    seq_5 = request.form.get('sequence-5')
    elective_credits = request.form.getlist('elective-credit')
    credit_hours = request.form.get('credit-hours')
    mwf_start_time = request.form.get('MWF-start-time')
    tr_start_time = request.form.get('TR-start-time')

    # Prepare data for CSV
    data_entries = [
        [core_class],
        [seq_1],
        [seq_2],
        [seq_3],
        [seq_4],
        [seq_5],
    ]

    # Add elective credits as separate entries
    for credit in elective_credits:
        data_entries.append([credit])
    
    # Add other data
    data_entries.append([credit_hours])
    data_entries.append([mwf_start_time])
    data_entries.append([tr_start_time])


    # Write to CSV file
    with open('data.csv', mode='a', newline='') as file:
        writer = csv.writer(file)
        for entry in data_entries:
            writer.writerow(entry)

    return 'Data saved successfully!'

if __name__ == '__main__':
    app.run(port=3000, debug=True)
