const express = require('express');
const bodyParser = require('body-parser');
const fs = require('fs');
const path = require('path');

const app = express();

// Middleware to parse form data
app.use(bodyParser.urlencoded({ extended: true }));

// Serve static files from the current directory
app.use(express.static(__dirname));

// Serve the HTML file
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'schedules.html')); // Make sure the filename matches your HTML file
});

// Handle form submission
app.post('/submit', (req, res) => {
    console.log('Received data', req.body); // Log incoming data for debugging

    const coreClass = req.body['core-class'];
    const electiveCredits = req.body['elective-credit'];

    // Handle multiple elective credits
    const electiveCreditsList = Array.isArray(electiveCredits) ? electiveCredits : [electiveCredits];

    // Prepare data for CSV
    const data = `${coreClass},"${electiveCreditsList.join(',')}"\n`;

    // Write to CSV file
    fs.appendFile('data.csv', data, (err) => {
        if (err) {
            console.error(err);
            return res.status(500).send('Error saving data');
        }
        res.send('Data saved successfully!');
    });
});

// Start the server
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
