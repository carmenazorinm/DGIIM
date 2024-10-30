# Virtual Store Application - Practice

This project is a simple online store application built using Node.js, Express, and MongoDB. The application allows users to browse products, view product details, add items to their cart, and perform searches. The structure of the project is organized into different directories and files, each serving a specific purpose.

## Directory Structure and Contents

1. *model/*:

- *db.js*: manages the connection to the MongoDB database. It includes the configuration settings necessary to connect to the database using Mongoose and exports the connection for use in other parts of the application.

- *productos.js*: defines the schema for the products in the database. It uses Mongoose to create a model that represents the structure of product documents.

2. *node_modules/*:

- This directory contains all the dependencies and packages requires for the project, installed via npm. It is automatically generated when you run ``npm install```.

3. *public/css/*:

- *styles.css*: contains custom styles for the application. It defines the appearance of the product card and the buttons of the application.

4. *routes/*:

- *router_tienda.js*: defines the routes of the online store. It contains the logic for handling different HTTP requests (GET and POST) related to product browsing, searching and cart management. The routes interact with the models to fetch data and render the appropiate views.

5. *views/*:

- *base.html*: this is the main template file that provides the structure for other views. It includes the header with a category submenu, the search bar and its button.

- *carrito.html*: represents the shopping cart page, where users can view the products they have added to their cart, along with the total price.

- *detalle_producto.html*: displays detailed information about a specific product. It includes the product's image, title, description, price and an option to add the product to the cart.

- *portada.html*: this is the homepage of the online store. It showcases featured products.

6. *tienda.js*:

- This file serves as the entry point of the application. It sets up the Express server, configures middleware, and establishes the routes for the application.

## Running the Scripts

To get you online store up and running:

```
npm run tienda.js 
```

You should see a message indicating that the server is running. Open the browser and navigate to:

[Homepage](http://localhost:8000/portada)
