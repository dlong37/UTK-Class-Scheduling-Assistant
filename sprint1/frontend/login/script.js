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

document.querySelector('.submit-button').addEventListener('click', function(event) {
    event.preventDefault(); // Prevent form from submitting automatically

    const nameField = document.querySelector('.name');
    const email = document.querySelector('.email').value;
    const password = document.querySelector('.password').value;
    const alertBox = document.querySelector('.alert-box');
    const alertMessage = document.querySelector('.alert');

    if (nameField) {
        const name = nameField.value;
        // register page
        if (!name || !email || !password) {
            alertMessage.textContent = 'All fields are required!';
            alertBox.style.background = 'rgb(255, 110, 110)';
            alertBox.style.borderTopColor = 'rgb(255, 37, 37)';
        } else {
            alertMessage.textContent = 'Registration successful!';
            alertBox.style.background = 'rgb(110, 200, 110)'; // Success color
            alertBox.style.borderTopColor = 'rgb(37, 200, 37)'; // Success border

            // redirect to welcome page for now...
            setTimeout(function() {
                window.location.href = '../welcome/welcome.html';
            }, 1000);
        }
    } else {
        // login page
        if (!email || !password) {
            alertMessage.textContent = 'All fields are required!';
            alertBox.style.background = 'rgb(255, 110, 110)';
            alertBox.style.borderTopColor = 'rgb(255, 37, 37)';
        } else if (email === 'admin@email.com' && password === 'password') {
            alertMessage.textContent = 'Login successful!';
            alertBox.style.background = 'rgb(110, 200, 110)'; // Success color
            alertBox.style.borderTopColor = 'rgb(37, 200, 37)'; // Success border

            // redirect to welcome page for now...
            setTimeout(function() {
                window.location.href = '../welcome/welcome.html';
            }, 1000);
        } else {
            alertMessage.textContent = 'Invalid Credentials!';
            alertBox.style.background = 'rgb(255, 110, 110)';
            alertBox.style.borderTopColor = 'rgb(255, 37, 37)';
        }
    }

    // Show alert box with grow effect
    alertBox.classList.add('show');

    // Hide the alert box after 3 seconds with shrink effect
    setTimeout(function() {
        alertBox.classList.remove('show');
        alertBox.classList.add('hide'); // Shrink and hide

        // Remove the hide class after animation completes
        setTimeout(() => {
            alertBox.classList.remove('hide');
        }, 400); // 400ms matches the CSS transition duration
    }, 2000);
});

// Add keypress listener for "Enter" key on the password field
document.querySelector('.password').addEventListener('keypress', function(event) {
    if (event.key === 'Enter') {
        document.querySelector('.submit-button').click();
    }
});
