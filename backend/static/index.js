/*
 * index.js
 *
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

    // Show the form container
    form.classList.add('show');

    // Delay showing form elements for a staggered effect
    formElements.forEach((element, index) => {
        setTimeout(() => {
            element.classList.add('show');
        }, 200 * index); // Adjust the delay for each element
    });

    // Adds "enter" keypress listener to submit login/register forms
    document.querySelector('.password').addEventListener('keypress', function(event) {
        if (event.key === 'Enter') {
            document.querySelector('.submit-button').click();
        }
    });
});
