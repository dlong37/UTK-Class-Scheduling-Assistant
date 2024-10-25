/**
 * generated_schedule script
 */

// Course data for the schedule (just an example for now)
// const course_data = [
//     { day: 'Monday', time: '09:10 - 10:00', course: 'EF 151' },
//     { day: 'Wednesday', time: '09:10 - 10:00', course: 'EF 151' },
//     { day: 'Friday', time: '09:10 - 10:00', course: 'EF 151' },
//     { day: 'Monday', time: '10:20 - 11:10', course: 'EF 151' },
//     { day: 'Wednesday', time: '10:20 - 11:10', course: 'EF 151' },
//     { day: 'Friday', time: '10:20 - 11:10', course: 'EF 151' },
//     { day: 'Monday', time: '11:30 - 12:20', course: 'COSC 360'},
//     { day: 'Wednesday', time: '11:30 - 12:20', course: 'COSC 360'},
//     { day: 'Friday', time: '11:30 - 12:20', course: 'COSC 360'},
//     { day: 'Monday', time: '12:40 - 13:30', course: 'MUCO 120'},
//     { day: 'Wednesday', time: '12:40 - 13:30', course: 'MUCO 120'},
//     { day: 'Friday', time: '12:40 - 13:30', course: 'MUCO 120'},

//     { day: 'Tuesday', time: '08:10 - 09:25', course: 'COSC 340'},
//     { day: 'Thursday', time: '08:10 - 09:25', course: 'COSC 340'},
//     { day: 'Tuesday', time: '09:45 - 11:00', course: 'COSC 312'},
//     { day: 'Thursday', time: '09:45 - 11:00', course: 'COSC 312'},
// ];

// // Time slots for MWF and TR
// const mwfTimeSlots = ['08:00 - 08:50', '09:10 - 10:00', '10:20 - 11:10', '11:30 - 12:20',
//                       '12:40 - 13:30', '13:50 - 14:40', '15:00 - 15:50', '16:10 - 17:00'];

// const trTimeSlots = ['08:10 - 09:25', '09:45 - 11:00', '11:20 - 12:35',
//                      '12:55 - 14:10', '14:30 - 15:45', '16:05 - 17:20'];

// // Days for MWF and TR
// const mwfDays = ['Monday', 'Wednesday', 'Friday'];
// const trDays = ['Tuesday', 'Thursday'];

// // Function to create table rows and populate data for MWF
// function populateMWFTable() {
//     const mwfTableBody = document.getElementById('mwf-schedule-body');
//     mwfTimeSlots.forEach(time => {
//         const row = document.createElement('tr');

//         // Add time slot to first column
//         const timeCell = document.createElement('td');
//         timeCell.textContent = time;
//         row.appendChild(timeCell);

//         // Add empty cells for Monday, Wednesday, and Friday
//         mwfDays.forEach(day => {
//             const cell = document.createElement('td');
//             row.appendChild(cell);
//         });

//         mwfTableBody.appendChild(row);
//     });

//     // Populate the table with course data for MWF
//     course_data.forEach(item => {
//         if (mwfDays.includes(item.day)) {
//             const row = Array.from(mwfTableBody.rows).find(
//                 r => r.cells[0].textContent === item.time
//             );

//             if (row) {
//                 const dayIndex = mwfDays.indexOf(item.day) + 1; // Get index of day (starting from 1 for columns)
//                 const cell = row.cells[dayIndex];
//                 cell.textContent = item.course;
//                 cell.classList.add('occupied'); // Highlight occupied cells
//             }
//         }
//     });
// }

// // Function to create table rows and populate data for TR
// function populateTRTable() {
//     const trTableBody = document.getElementById('tr-schedule-body');
//     trTimeSlots.forEach(time => {
//         const row = document.createElement('tr');

//         // Add time slot to first column
//         const timeCell = document.createElement('td');
//         timeCell.textContent = time;
//         row.appendChild(timeCell);

//         // Add empty cells for Tuesday and Thursday
//         trDays.forEach(day => {
//             const cell = document.createElement('td');
//             row.appendChild(cell);
//         });

//         trTableBody.appendChild(row);
//     });

//     // Populate the table with course data for TR
//     course_data.forEach(item => {
//         if (trDays.includes(item.day)) {
//             const row = Array.from(trTableBody.rows).find(
//                 r => r.cells[0].textContent === item.time
//             );

//             if (row) {
//                 const dayIndex = trDays.indexOf(item.day) + 1; // Get index of day (starting from 1 for columns)
//                 const cell = row.cells[dayIndex];
//                 cell.textContent = item.course;
//                 cell.classList.add('occupied'); // Highlight occupied cells
//             }
//         }
//     });
// }

// // Populate both MWF and TR tables
// populateMWFTable();
// populateTRTable();

// JS CSV parser for now to design (maybe switch to flask parser)
document.getElementById('csvFile').addEventListener('change', function(event) {
    const file = event.target.files[0];
    if (file) {
      Papa.parse(file, {
        complete: function(results) {
          const data = results.data;
          generateSchedule(data);
        },
        header: true
      });
    }
  });
  
  function generateSchedule(data) {
    data.forEach(course => {
      const { Abbreviation, Number, Title, LcTime, LcDate, LaTime, LaDate } = course;
  
      // Lecture information
      if (LcTime !== 'none' && LcDate !== 'none') {
        const times = parseTime(LcTime);
        console.log(times);
        const days = LcDate.split('');
        days.forEach(day => {
          addClassToSchedule(day, times.start, times.end, `${Abbreviation} ${Number}`);
        });
      }
  
      // Lab information (optional)
      if (LaTime !== 'none' && LaDate !== 'none') {
        const labTimes = parseTime(LaTime);
        const labDays = LaDate.split('');
        labDays.forEach(day => {
          addClassToSchedule(day, labTimes.start, labTimes.end, `${Abbreviation} ${Number} Lab`);
        });
      }
    });
  }
  
  function parseTime(timeString) {
    const [start, end] = timeString.split('-');
    console.log(timeString);
    return {
      start: convertToGridTime(start),
      end: convertToGridTime(end)
    };
  }
  
  function convertToGridTime(time) {
    const hour = parseInt(time.slice(0, 2)); // Extract the hour
    const minute = parseInt(time.slice(2));   // Extract the minutes
    // Calculate the grid row: 
    // - (hour - 8) * 12 calculates the row based on the hour (12 slots for each hour)
    // - (minute / 5) adds the number of 5-minute increments within that hour
    // - + 2 offsets the grid to account for the starting row of 08:00
    const ret = (hour - 8) * 12 + (minute / 5) + 2;
    console.log(ret);
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
