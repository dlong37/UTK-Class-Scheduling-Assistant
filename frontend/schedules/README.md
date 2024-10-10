# How to Run the Schedules Page
<b>1. Download Node.js</b>
* Go to the Node.js website
* Download the LTS (long Term Support) version for your operating system.

<b>2. Install Node.js</b>
* Run the installer and follow the prompts. Make sure to check the option to add Node.js to your system PATH during installation.

<b>3. Verify Installation</b>
* Open your terminal and check if Node.js and npm are installed with the following commands:
> node -v
> npm -v
* You should see version numbers for both commands if they are installed correctly.

<b>4. Initialize Project in the Directory</b>
* Whether you decide to do it in this git folder or download the files locally into another folder, go to that folder and run the following commands to initialize the project and install the necessary packages:
> npm init -y
> npm install express body-parser fs

<b>5. Start the Server</b>
* Start the server using the following command:
> node server.js
* Open your browser and navigate to http://localhost:3000 to see the form.

<br>
<b>NOTE:</b> If someone has already ran these commands in this git folder, then the project should already be initialized and the necessary packages should be already installed in the schedules sub-directory.