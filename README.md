# IoT-Distillery
The IoT-Distillery is a remote controlled distillery set-up using a ESP8266, a Express.js api and an React controll panel.

This is a hobby project that I pick up from time to time. Used for multiple school projects and expanded on outside those. For a video demo click [here](https://youtu.be/6Cbey2tjaiA), audio is in Dutch.

## Micro Controller
I'm using an ESP8266. This board has an inbuild WiFi-module. Code has been written using C++ and PlatformIO. Code has been rewritten from a single Arduino script to one making use of PlatformIO. Allows for easier use of interface and inheritance. Can be configured to communicate over serial or directly make request to the API.

## API
The bridge between the Control Panel and the Micro Controller. Uses two routes "/arduino" and "/admin". "/admin" contains all requests that can be accesed through the admin panel such as:
- GET "/:id", fetches temperature data with timestamps from a specific session.
- PUT "/", used to update the state (start or stop) and set target temperature.
- POST "/", used to create a new session.

"/arduino" contains all request that are required for the microcontroller the function:
- GET "/", fetches state and target temperature.
- POST "/", posts temperature data to the database.

## Control Panel
Visual user interface made using react. Creates a graph using temperature data and their timestamps.

## SerialListener
script that can recieve and send serial data to the Micro Controller. Handy if your board doesnt have WiFi capability. Connect your Micro Controller to a computer and run this script.
