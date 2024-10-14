// Button code from app.js for the welcome page.
const menu = document.querySelector('#mobile-menu');
const menuLinks = document.querySelector('.navbar__menu');

menu.addEventListener('click', function() {
    menu.classList.toggle('is-active');
    menuLinks.classList.toggle('active');
})

document.getElementById('schedules-form').addEventListener('submit', function(event) {
    event.preventDefault(); // Prevent the default form submission

    const formData = new FormData(this); // Gather form data

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
        // Show the success message
        document.getElementById('success-message').style.display = 'block';

        // Optionally clear the form fields after submission
        this.reset();
    })
    .catch(error => {
        console.error('There was a problem with the fetch operation:', error);
    });
});
