//
// Created by Daniël on 08/02/2022.
//

#include "TemperatureController.h"
#include "OneWire.h"
#include "DallasTemperature.h"
#include <Arduino.h>

TemperatureController::TemperatureController(float targetTemp, bool state, int oneWirePin) {
    targetTemperature = targetTemp;
    TemperatureController::state = state;

    //create OneWire object and pass reference to DallasTemperature.
    oneWire = OneWire(oneWirePin);
    sensor = DallasTemperature(&oneWire);
    sensor.begin();
}

float TemperatureController::getCurrentTemperature() {
    sensor.requestTemperatures();
    //returning index 0 because there is only one sensor attached.
    return sensor.getTempCByIndex(0);
}

void TemperatureController::setTargetTemperature(float targetTemp) {
    targetTemperature = targetTemp;
}

void TemperatureController::setState(bool newState) {
    state = newState;
}

void TemperatureController::update() {
    float currentTemp = getCurrentTemperature();
    Serial.print(currentTemp);
}