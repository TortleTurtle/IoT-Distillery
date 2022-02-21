//
// Created by danie on 10/02/2022.
//

#include "SerialCommunicationHandler.h"

SerialCommunicationHandler::SerialCommunicationHandler() {
    messagePosition = 0;
    receiving = false;
    newData = false;

    startMillis = millis();
    currentMillis = millis();
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
                break;
            case '>':
                //stop receiving and parse the incoming data.
                receiving = false;
                strcpy(receivedData, incomingData); //copy incoming data into receivedData for further parsing.
                memset(incomingData, 0, sizeof(incomingData)); //resetting incomingData array.
                messagePosition = 0; //setting position back to 0

                newData = true; //setting new data to true so parseData knows it has to parse.
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

        //log parsed serial data.
        Serial.print("Target Temp: ");
        Serial.println(parsedData.temperature);
        Serial.print("State: ");
        Serial.println(parsedData.state);

        //send parsed data to TemperatureController.
        TemperatureController::setTargetTemp_State(parsedData);

        newData = false;
    }
}

void SerialCommunicationHandler::sendTemperature(float temp) {
    Serial.println("[" + String(temp) + "]");
}

void SerialCommunicationHandler::update() {
    receiveData();
    parseData();

    //timer to send temperature every minute.
    currentMillis = millis();
    if (currentMillis - startMillis >= 1000 * 60) {
        sendTemperature(TemperatureController::getCurrentTemperature());
        startMillis = currentMillis;
    }
}