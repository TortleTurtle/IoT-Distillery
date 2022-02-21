#include <Arduino.h>
#include "global.h"
#include "TemperatureController.h"
#include "RelayController.h"
#include "ICommunicationHandler.h"
#include "SerialCommunicationHandler.h"
#include "HTPP_CommunicationHandler.h"

TemperatureState startingTemp_State = {64.5, false};
TemperatureController* tempController = new RelayController(startingTemp_State, 1, 2);
ICommunicationHandler* communicationHandler;

void setup() {
    Serial.begin(9600);
    communicationHandler = new  HTPP_CommunicationHandler("HuizeKordaat", "CoronaKanjers1", "http://192.168.178.229:8000/arduino");
    tempController->begin();
    communicationHandler->receiveData();
    communicationHandler->sendTemperature(20);
}

void loop() {
    tempController->update();
}
