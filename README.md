# Presentation (video)
https://www.youtube.com/watch?v=TrTP_JJx--8 (technical presentation, shows the backend deployed, QDebug etc.)
![image](https://user-images.githubusercontent.com/87731856/235370505-f55bb69d-74b0-46c7-8c5a-104581b7e93f.png)
Above can be seen the program after succesful deployment to the target machine.
# Deployment
To deploy the application and run it, you will need:
1. **Qt 6.4.3** and the submodules that the Qmake file has listed as necessary for the libraries
2. A **Node.js** runtime environment, this can be in the localhost or on a server as long as you **change the address for the REST API** (in Qt). Use a package manager such as npm to install all the necessary packages for the API and remember to **insert all the tokens and host/login info** for the database, RabbitMQ etc.
3. The **MySQL database** hosted somewhere and the server setup so that it responds to the HTTP requests. Use the **dump file** to deploy the database.

When you have taken care of the above:

4. **Run the Qt Widget application** on your desired platform

If you are seriously trying out the application (for educational purposes) and need some help, don't hesitate to contact me.

# ER-diagram of the ATM database
![image](https://user-images.githubusercontent.com/87731856/232758358-d00e9a1e-7811-4578-a3de-22a5dc6705fa.png)

# Showcase
![image](https://user-images.githubusercontent.com/87731856/233630613-7da6348a-46cf-4542-b7de-87d91f3a82c0.png)

# RabbitMQ queries for sending e-mails to reduce duplicates and bad times
![image](https://user-images.githubusercontent.com/87731856/234818853-652d5213-91e3-4ef6-8c15-ea7b9d147c94.png)

# Credits

**Sauli Savinainen** - Serial port component development, Qt-development to all components (custom sum withdrawal, POST API functions...), Raspberry Pi cross-compilation, CRUD-table development, REST API deployment to web service and MySQL database hosting & administration, RabbitMQ integration, graphics and sound features

**Mika Korkiakoski** - Card-handling (PIN-code and related data) component development on Qt, backend development for related API functions, graphics and interface development

**Miika Tiihonen** - GUI and main executable structural/functional design and implementation in Qt (excluding PIN-code(dll), styles, sounds, visual clock, and custom sum withdrawal). Necessary functionality to our Qt dll handling http requests and backend/REST API to facilitate account swapping, transaction creation on withdrawal, email sending, and login. Table updates and troubleshooting in MySQL database.
