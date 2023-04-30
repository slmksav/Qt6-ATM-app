# Video
https://www.youtube.com/watch?v=TrTP_JJx--8 (technical presentation, shows the backend deployed, QDebug etc.)
![image](https://user-images.githubusercontent.com/87731856/235370505-f55bb69d-74b0-46c7-8c5a-104581b7e93f.png)
Above can be seen the program after succesful deployment to the target machine.
# Credits

Sauli Savinainen - Serial port component development, Qt-development to all components (custom sum withdrawal, POST API functions...), Raspberry Pi cross-compilation, CRUD-table development, REST API deployment to web service and MySQL database hosting & administration, RabbitMQ integration, graphics and sound features

Mika Korkiakoski - Card-handling (PIN-code and related data) component development on Qt, backend development for related API functions, graphics and interface development

Miika Tiihonen - GUI and main executable structural/functional design and implementation in Qt (excluding PIN-code(dll), styles, sounds, visual clock, and custom sum withdrawal). Necessary functionality to our Qt dll handling http requests and backend/REST API to facilitate account swapping, transaction creation on withdrawal, email sending, and login. Table updates and troubleshooting in MySQL database.

Samuli Pylkkönen - API functions (HTTP GET) component development on Qt, data formatting

# ER-diagram of the ATM database
![image](https://user-images.githubusercontent.com/87731856/232758358-d00e9a1e-7811-4578-a3de-22a5dc6705fa.png)

# Showcase
![image](https://user-images.githubusercontent.com/87731856/233630613-7da6348a-46cf-4542-b7de-87d91f3a82c0.png)

# RabbitMQ queries for sending e-mails to reduce duplicates and bad times
![image](https://user-images.githubusercontent.com/87731856/234818853-652d5213-91e3-4ef6-8c15-ea7b9d147c94.png)
