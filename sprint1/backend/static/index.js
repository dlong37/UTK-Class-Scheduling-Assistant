function deleteSchedule(scheduleId) {
    fetch('/delete-schedule', {
        method: 'POST',
        body: JSON.stringify({ scheduleId: scheduleId})
    }).then((_res) => {
        window.location.href = "/main";
    })
}

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
});

// Add keypress listener for "Enter" key on the password field
document.querySelector('.password').addEventListener('keypress', function(event) {
    if (event.key === 'Enter') {
        document.querySelector('.submit-button').click();
    }
});