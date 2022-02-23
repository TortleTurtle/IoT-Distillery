#include <Arduino.h>
#include "TemperatureController.h"
#include "RelayController.h"
#include "ServoController.h"
#include "ICommunicationHandler.h"
#include "SerialCommunicationHandler.h"
#include "HTPP_CommunicationHandler.h"

TemperatureController* tempController;
ICommunicationHandler* communicationHandler;

//analog sensor
OneWire oneWire(D5);
DallasTemperature dallasTemperature(&oneWire);

//functions for interrupts.
IRAM_ATTR void useSerial(){
    Serial.println("UseSerial");
    communicationHandler = new SerialCommunicationHandler();
    detachInterrupt(D1);
    detachInterrupt(D2);
}
IRAM_ATTR void useHTTP(){
    Serial.println("UseHTTP");
    communicationHandler = new HTPP_CommunicationHandler("HuizeKordaat", "CoronaKanjers1", "http://192.168.178.229:8000/arduino");
    detachInterrupt(D1);
    detachInterrupt(D2);
}
IRAM_ATTR void useRelay(){
    Serial.println("UseRelay");
    tempController = new RelayController({40, false}, &dallasTemperature, D6);
    tempController->begin();
    detachInterrupt(D3);
    detachInterrupt(D4);
}
IRAM_ATTR void useServo(){
    Serial.println("UseServo");
    tempController = new ServoController({40, false}, &dallasTemperature, D6);
    tempController->begin();
    detachInterrupt(D3);
    detachInterrupt(D4);
}

void setupKeypadInterrupt() {
    pinMode(D0, OUTPUT); //Row
    pinMode(D1, INPUT_PULLUP); //collumn 1
    pinMode(D2, INPUT_PULLUP); //collumn 2
    pinMode(D3, INPUT_PULLUP); //collumn 3
    pinMode(D4, INPUT_PULLUP); //collumn 4
    digitalWrite(D0, LOW);

    attachInterrupt(digitalPinToInterrupt(D1), useSerial, FALLING);
    attachInterrupt(digitalPinToInterrupt(D2), useHTTP, FALLING);
    attachInterrupt(digitalPinToInterrupt(D3), useRelay, FALLING);
    attachInterrupt(digitalPinToInterrupt(D4), useServo, FALLING);
}

void setup() {
    Serial.begin(9600);
    setupKeypadInterrupt();
}

void loop() {
    //Block updating if pointers are not set.
    if (tempController && communicationHandler) {
        tempController->update();
        communicationHandler->update();
    }
}