# IoT-Distillery
The IoT-Distillery is a remote controlled distillery set-up using a ESP8266, a Express.js api and an React controll panel.

This is a hobby project that I pick up from time to time. Used for multiple school projects and expanded on outside those. For a video demo click [here](https://youtu.be/6Cbey2tjaiA), audio is in Dutch.

## Folders
- Micro Controller, contains all the code to control the physical set-up. Written using PlatformIO.
- Control Panel, a user interface to start or stop a distillery session it also shows current temperature and creates a graph of the current session. Connected to a database so older sessions can also be viewed.
- API, the bridge between the Control Panel and the Micro Controller.
- SerialListener, script that can recieve and send serial data to the Micro Controller. Handy if your board doesnt have WiFi capability. Connect your Micro Controller to a computer and run this script.
