#include <Arduino.h>
#include "global.h"
#include "TemperatureController.h"
#include "RelayController.h"
#include "ICommunicationHandler.h"
#include "SerialCommunicationHandler.h"

//using a pointer to declare
TemperatureState startingTemp_State = {64.5, false};
TemperatureController* tempController =new RelayController(startingTemp_State, 1, 2);
ICommunicationHandler* communicationHandler;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    communicationHandler = new SerialCommunicationHandler();
    tempController->begin();
}

void loop() {
    tempController->update();
    communicationHandler->receiveData();
    communicationHandler->parseData();
}
