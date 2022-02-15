//
// Created by danie on 09/02/2022.
//
#include <Arduino.h>
#include "RelayController.h"

//classes in C++ need to call parent constructor before being able to call own constructor.
RelayController::RelayController(TemperatureState temperatureState, int oneWirePin, int relayPin)
        : TemperatureController(temperatureState, oneWirePin) {
    RelayController::relayPin = relayPin;
}

void RelayController::update() {
    float currentTemp = getCurrentTemperature();
    if (targetTemp_State.temperature > currentTemp && targetTemp_State.state) {
        digitalWrite(relayPin, HIGH);
    } else {
        digitalWrite(relayPin, LOW);
    }
}
