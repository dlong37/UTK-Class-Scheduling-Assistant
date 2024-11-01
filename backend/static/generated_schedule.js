/**
 * generated_schedule script
 */

// Function to handle the CSV file upload
// Replace 'path/to/your/csv/schedule.csv' with the actual URL to your CSV file
const csvFilePath = '/static/schedule.csv';

fetch(csvFilePath)
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok ' + response.statusText);
        }
        return response.text(); // Get the response as text
    })
    .then(data => {
        Papa.parse(data, {
            header: true, // Use the first row as header
            complete: function(results) {
                console.log(results.data); // Log the parsed data
                generateSchedule(results.data); // Pass the data to your schedule generation function
            },
            error: function(error) {
                console.error("Error parsing CSV:", error);
            }
        });
    })
    .catch(error => {
        console.error("Error fetching CSV file:", error);
    });


// Your existing generateSchedule function
function generateSchedule(data) {
  data.forEach(course => {
      const { Abbreviation, Number, Title, Lecture_Time, Lecture_Days, Lab_Time, Lab_Days } = course;
      
      // Lecture information
      if (Lecture_Time) {
          const times = parseTime(Lecture_Time);
          const days = Lecture_Days.split('');
          days.forEach(day => {
              addClassToSchedule(day, times.start, times.end, `${Abbreviation} ${Number}`);
          });
      }

      // Lab information (optional)
      if (Lab_Time) {
          const labTimes = parseTime(Lab_Time);
          const labDays = Lab_Days.split('');
          labDays.forEach(day => {
              addClassToSchedule(day, labTimes.start, labTimes.end, `${Abbreviation} ${Number} Lab`);
          });
      }
  });
}

function parseTime(timeString) {
  const [start, end] = timeString.split(' - '); // Split by ' - '
  return {
      start: convertToGridTime(start.trim()), // Use trim() to remove any leading/trailing spaces
      end: convertToGridTime(end.trim())
  };
}

function convertToGridTime(time) {
  // Split the time and the period (AM/PM)
  const [timePart, period] = time.split(' ');
  const [hour, minute] = timePart.split(':').map(Number); // Split hour and minute and convert to numbers

  let gridHour;
  // Convert hour to 24-hour format
  if (period === 'PM' && hour < 12) {
      gridHour = hour + 12; // Convert PM hour to 24-hour format
  } else if (period === 'AM' && hour === 12) {
      gridHour = 0; // Midnight case
  } else {
      gridHour = hour; // No conversion needed for AM hours (except 12)
  }

  // Calculate the grid row: 
  // - (gridHour - 8) * 12 calculates the row based on the hour (12 slots for each hour)
  // - (minute / 5) adds the number of 5-minute increments within that hour
  // - + 2 offsets the grid to account for the starting row of 08:00
  const ret = (gridHour - 8) * 12 + (minute / 5) + 2;
  return ret;
}


  function addClassToSchedule(day, start, end, className) {
    const scheduleGrid = document.querySelector('.schedule-grid');
    const dayColumn = { M: 2, T: 3, W: 4, R: 5, F: 6 }[day];
    const classElement = document.createElement('div');
    classElement.classList.add('class');
    classElement.style.gridColumn = dayColumn;
    classElement.style.gridRow = `${start} / span ${end - start + 1}`;
    classElement.textContent = className;
    scheduleGrid.appendChild(classElement);
  }
