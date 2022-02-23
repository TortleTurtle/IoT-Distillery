//
// Created by Daniël on 08/02/2022.
//

#include "TemperatureController.h"
#include "OneWire.h"
#include "DallasTemperature.h"

//initialise static member variables.
TemperatureState TemperatureController::targetTemp_State = {};
DallasTemperature *TemperatureController::sensor = {};

TemperatureController::TemperatureController(TemperatureState temperatureState, DallasTemperature *dallasTemperature) {
    targetTemp_State = temperatureState;
    sensor = dallasTemperature;
}

float TemperatureController::getCurrentTemperature() {
    sensor->requestTemperatures();
    //returning index 0 because there is only one sensor attached.
    return sensor->getTempCByIndex(0);
}

void TemperatureController::setTargetTemp_State(TemperatureState newTemp_State) {
    targetTemp_State = newTemp_State;
    Serial.println("new temperature " + String(targetTemp_State.temperature) + "new state: " + String(targetTemp_State.state));
}

void TemperatureController::begin() {
    sensor->begin();
}
