#include "Arduino.h"
#include "common.h"

class SerialHandler {
  private:
    boolean newData = false;
    static const byte numChars = 32;
    char startMarker = '<';
    char endMarker = '>';

    void recieveData() {
      static boolean recvInProgress = false;
      static byte ndx = 0;
      char rc;
      
      while (Serial.available() > 0 && newData == false) {
          Serial.print(" Listening ");
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
      if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        char * strtokIndx; // this is used by strtok() as an index
   
        strtokIndx = strtok(tempChars, ","); // this continues where the previous call left off
        parsedData.state = atoi(strtokIndx);  // convert to integer
    
        strtokIndx = strtok(NULL, ",");
        parsedData.targetTemp = atof(strtokIndx);     // convert this part to a float

        newData = false;
      }
    }

  public:
    CommonData parsedData;

    //public for strcopy()
    char receivedChars[numChars];
    char tempChars[numChars];        // temporary array for use when parsing

    void updateLoop() {
      recieveData();
      parseData();
      //showParsedData();
    }
    
    void showParsedData() {
      Serial.println("State: " + String(parsedData.state));
      Serial.println("Target Temp: " + String(parsedData.targetTemp));
    }

    //write the temperature to serial
    void sendTemperature(float temperature) {
        Serial.println("[" + String(temperature) + "]");
    }
};
