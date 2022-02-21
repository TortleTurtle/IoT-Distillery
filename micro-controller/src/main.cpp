#include <Arduino.h>
#include "global.h"
#include "TemperatureController.h"
#include "RelayController.h"
#include "ICommunicationHandler.h"
#include "SerialCommunicationHandler.h"
#include "HTPP_CommunicationHandler.h"

TemperatureController* tempController = new RelayController({64.5, false}, D1, D4);
ICommunicationHandler* communicationHandler;

void setup() {
    Serial.begin(9600);
    //communicationHandler = new HTPP_CommunicationHandler("HuizeKordaat", "CoronaKanjers1", "http://192.168.178.229:8000/arduino");
    //communicationHandler = new SerialCommunicationHandler();
    tempController->begin();
}

void loop() {
    tempController->update();
    communicationHandler->update();
}
