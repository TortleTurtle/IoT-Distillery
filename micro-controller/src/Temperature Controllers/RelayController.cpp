//
// Created by danie on 09/02/2022.
//
#include <Arduino.h>
#include "RelayController.h"

//classes in C++ need to call parent constructor before being able to call own constructor.
RelayController::RelayController(TemperatureState temperatureState,DallasTemperature *dallasTemperature , int pin)
        : TemperatureController(temperatureState, dallasTemperature) {
    relayPin = pin;
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, HIGH);
}

void RelayController::update() {
    float currentTemp = getCurrentTemperature();
    if (targetTemp_State.temperature > currentTemp && targetTemp_State.state ==  1) {
        digitalWrite(relayPin, LOW);
        Serial.println("Heating");
    } else {
        digitalWrite(relayPin, HIGH);
    }
}
