#include <OneWire.h>
#include <DallasTemperature.h>
 
// Define pins
#define TEMP_SENSOR 2
#define RELAIS 3

// Create oneWire instance and pass it to DallasTemperature. 
OneWire oneWire(TEMP_SENSOR);
DallasTemperature sensors(&oneWire);

//Timer
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long interval = 10000; //10 seconds

//boiling point of methanol
const float methanolTemp = 64.70;
//boiling point of ethanol
const float ethanolTemp = 78.37;

//variables for Serial Communication
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing
char reciever = "";
boolean newData = false;

char state = "false";
float currentTemp;
float targetTemp;

void setup(void) {
  // start serial port
  Serial.begin(9600);
  Serial.println("Expecting true or false for state and a float for temperature");
  Serial.println("Enter data in this style <false, 64.2>");
  Serial.println();

  //set Relais pin to output mode
  pinMode(RELAIS, OUTPUT);
  targetTemp = methanolTemp;

  // Start up the library
  sensors.begin();

  //start the interval timer
  startMillis = millis();  
}
 
void loop(void) {
  currentMillis = millis();

  //recieve data via Serial.
  recvWithStartEndMarkers();
  if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        showParsedData();
        newData = false;
  }
  
  //update current temperature
  sensors.requestTemperatures();
  currentTemp = sensors.getTempCByIndex(0);

  checkTemperature();
  //send temperature via serial to computer.
  sendTemperature();
}

//==========

void checkTemperature(void) {
  if (currentTemp > targetTemp && state == "false") {
    //turn off relais
    digitalWrite(RELAIS, HIGH); //relais is set to Normally Open, to close it you need to send a signal.
  } else {
    //turn on relais
    digitalWrite(RELAIS, LOW);
  }
}
//write the temperature to serial
void sendTemperature(void) {
  if (currentMillis - startMillis >= interval) {
    Serial.println("[" + String(currentTemp) + "]");
    startMillis = currentMillis;
  }
}

//==========

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index
 
    strtokIndx = strtok(tempChars, ","); // this continues where the previous call left off
    strcpy(state, strtokIndx);   // copy state to variable.integer

    strtokIndx = strtok(NULL, ",");
    targetTemp = atof(strtokIndx);     // convert this part to a float
}

void showParsedData() {
    Serial.println("State: " + state);
    Serial.println("Target Temp: " + String(targetTemp));
}
