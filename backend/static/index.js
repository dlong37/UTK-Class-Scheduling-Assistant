/*
 * index.js
 */

/*
 * button clicks
 */
const menu = document.querySelector('#mobile-menu');
const menuLinks = document.querySelector('.navbar__menu');

menu.addEventListener('click', function() {
    menu.classList.toggle('is-active');
    menuLinks.classList.toggle('active');
});

/*
 * deletes schedules from main page
 */
function deleteSchedule(scheduleId) {
    fetch('/delete-schedule', {
        method: 'POST',
        body: JSON.stringify({ scheduleId: scheduleId })
    }).then((_res) => {
        window.location.href = "/main";
    });
}

/*
 * stagger animation for login/register forms
 */
window.addEventListener('DOMContentLoaded', () => {
    const form = document.querySelector('.form');
    const formElements = document.querySelectorAll('.form input, .form .submit-button');

    // show the form container
    form.classList.add('show');

    // delay showing form elements for a staggered effect
    formElements.forEach((element, index) => {
        setTimeout(() => {
            element.classList.add('show');
        }, 200 * index);
    });

    // adds "enter" keypress listener to submit login/register forms
    document.querySelector('.password').addEventListener('keypress', function(event) {
        if (event.key === 'Enter') {
            document.querySelector('.submit-button').click();
        }
    });
});

/*
 * stagger animation for schedule page
 */
window.addEventListener('DOMContentLoaded', () => {
    const form = document.querySelector('.schedules__container');
    const formElements = document.querySelectorAll('.schedules__container input[type="checkbox"], .schedules__container select, .schedules__container input[type="submit"], .schedules__container label')

    // show form container
    form.classList.add('show');

    // delay showing form elements for a staggered effect
    formElements.forEach((element, index) => {
        setTimeout(() => {
            element.classList.add('show');
        }, 25 * index);
    });
})

/*
 * stagger animation for main page
 */
window.addEventListener('DOMContentLoaded', () => {
    const listItems = document.querySelectorAll('#schedules .list-group-item');
    const form = document.querySelector('form');
    const additionalButtons = document.querySelectorAll('button.class_search, button.schedules');

    // Animate each list item with staggered delay
    listItems.forEach((item, index) => {
        setTimeout(() => {
            item.classList.add('show');
        }, 200 * index); // Delay of 100ms between each item
    });

    // Animate the form
    setTimeout(() => {
        form.classList.add('show');
    }, 100 * listItems.length); // Delay after the last list item

    // Animate additional buttons (Search Classes, Schedule Questionnaire)
    additionalButtons.forEach((button, index) => {
        setTimeout(() => {
            button.classList.add('show');
        }, 200 * (listItems.length + index + 1)); // Delay after the form
    });
});


/*
 * submit form with success message
 */
document.getElementById('schedules-form').addEventListener('submit', function(event) {
    event.preventDefault(); // prevent the default form submission

    const formData = new FormData(this);

    fetch('/submit', {
        method: 'POST',
        body: formData
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        return response.text();
    })
    .then(data => {
        // show the success message
        document.getElementById('success-message').style.display = 'block';

        // optionally clear the form fields after submission
        this.reset();
    })
    .catch(error => {
        console.error('There was a problem with the fetch operation:', error);
    });
});
