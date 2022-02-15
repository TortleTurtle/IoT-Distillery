//
// Created by danie on 10/02/2022.
//

#include <Arduino.h>
#include "SerialCommunicationHandler.h"
#include "global.h"

SerialCommunicationHandler::SerialCommunicationHandler() {
    messagePosition = 0;
    receiving = false;
    newData = false;
}

void SerialCommunicationHandler::receiveData() {
    //check if there are bytes in the serial buffer.
    while (Serial.available() > 0){
        char inByte = Serial.read();
        //check if the byte is a starting or ending character;
        switch (inByte) {
            case '<':
                //start receiving characters
                receiving = true;
                digitalWrite(LED_BUILTIN, HIGH);
                break;
            case '>':
                //stop receiving and parse the incoming data.
                digitalWrite(LED_BUILTIN, LOW);
                receiving = false;
                newData = true;
                strcpy(receivedData, incomingData); //copy incoming data into receivedData for further parsing.
                memset(incomingData, 0, sizeof(incomingData)); //resetting incomingData array.
                messagePosition = 0;
                break;
            default:
                if (receiving) {
                    incomingData[messagePosition] = inByte; //add incoming byte to array.
                    messagePosition++;
                }
                break;
        }
    }
}

void SerialCommunicationHandler::parseData() {
    if (newData) {
        TemperatureState parsedData = {}; // struct to store parsed data.
        char * strtokIndx; //used by strtok() as an index

        strtokIndx = strtok(receivedData, ","); //split the string at the first ",".
        parsedData.temperature = atof(strtokIndx); //convert string to float

        strtokIndx = strtok(NULL, ","); //passing null because the original string is still in the buffer of strtok.
        parsedData.state = atoi(strtokIndx); // convert string to int.

        Serial.print("Target Temp: ");
        Serial.println(parsedData.temperature);
        Serial.print("State: ");
        Serial.println(parsedData.state);

        newData = false;
    }
}

void SerialCommunicationHandler::showParsedData() {

}

void SerialCommunicationHandler::sendTemperature(float temp) {

}

void SerialCommunicationHandler::update() {

}