//
// Created by danie on 09/02/2022.
//

#include "RelayController.h"
#include <Arduino.h>

//classes in C++ need to call parent constructor before being able to call own constructor.
RelayController::RelayController(float targetTemp, bool state, int oneWirePin, int relayPin)
        : TemperatureController(targetTemp, state, oneWirePin) {
    RelayController::relayPin = relayPin;
}

void RelayController::update() {
    float currentTemp = getCurrentTemperature();
    if (targetTemperature > currentTemp) {
        digitalWrite(relayPin, HIGH);
    } else {
        digitalWrite(relayPin, LOW);
    }
}
