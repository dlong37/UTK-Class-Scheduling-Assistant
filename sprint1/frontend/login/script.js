// form loading animation

const form = [...document.querySelector('.form').children];

form.forEach((item, i) => {
    setTimeout(() => {
        item.style.opacity = 1;
    }, i*100);
})

// form validation

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
            alertBox.classList.add('show');
        } else {
            alertMessage.textContent = 'Registration successful!';
            alertBox.style.background = 'rgb(110, 200, 110)'; // Success color
            alertBox.style.borderTopColor = 'rgb(37, 200, 37)'; // Success border
            alertBox.classList.add('show');
        }
    } else {

        // login page
        if (!email || !password) {
            alertMessage.textContent = 'All fields are required!';
            alertBox.style.background = 'rgb(255, 110, 110)';
            alertBox.style.borderTopColor = 'rgb(255, 37, 37)';
            alertBox.classList.add('show');
        } else if (email === 'admin@email.com' && password === 'password') {
            alertMessage.textContent = 'Login successful!';
            alertBox.style.background = 'rgb(110, 200, 110)'; // Success color
            alertBox.style.borderTopColor = 'rgb(37, 200, 37)'; // Success border
            alertBox.classList.add('show');
        } else {
            alertMessage.textContent = 'Invalid Credentials!';
            alertBox.style.background = 'rgb(255, 110, 110)';
            alertBox.style.borderTopColor = 'rgb(255, 37, 37)';
            alertBox.classList.add('show');
        }
    }

    // Hide the alert box after 3 seconds
    setTimeout(function() {
        alertBox.classList.remove('show');
    }, 3000);
});
