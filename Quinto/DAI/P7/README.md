# Virtual Store Application - Practice

This repository contains the solution for the first two practices of the Internet Application Development course. The project uses MongoDB, Node.js, and Docker.
Structure

    - P0: Contains the docker-compose.yml file to set up MongoDB and Mongo Express.
    - P1: Contains two JavaScript files, seed.js and download_images.js, used to populate the database and download product images, respectively.
    - dump/MyProject: Contains the backup of the database using mongodump.

## Step-by-step Instructions
### 1. Setup Docker Containers

    Navigate to the P0 folder where the docker-compose.yml file is located.

    Run the following command to start the MongoDB and Mongo Express containers:

    ```docker-compose up```

    - MongoDB will be available on port 27017.
    - Mongo Express will be available on port 8081 to allow graphical management of the database.

### 2. Populate the Database

    Go to the P1 folder. There is a script called seed.js which fetches product and user data from Fake Store API and inserts it into the MongoDB database.

    Run the script using:

    ```npm run seed```

    This will:
    - Fetch the product and user JSON data using fetch.
    - Insert the data into the MongoDB collections.

### 3. Download Product Images

    The download_images.js script in the P1 folder is used to download product images from the Fake Store API and save them into the imagenes folder.

    Run the script using:

    ```npm run download_images```

    The images will be saved in the folder imagenes/.

### 4. Database Backup

The database backup is stored in the dump/MyProject folder, created using the mongodump tool. To create the backup, we followed the steps outlined in the MongoDB documentation:

[Backup using mongodump](https://www.mongodb.com/docs/database-tools/mongodump/#mongodb-binary-bin.mongodump)
### 5. Environment Variables

The .env file is used to store sensitive credentials for MongoDB access. Make sure the .env file is correctly set up with your database username and password:

makefile

```USER_DB=root
PASS=example
```

The .env file is crucial as it allows the seed.js script to connect to the MongoDB database securely using these credentials.
## Running the Scripts

You can execute the scripts using npm run followed by the script name:

To populate the database:
```npm run seed```

To download product images:
 ```npm run download_images```
