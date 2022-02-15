//
// Created by Daniël on 08/02/2022.
//

#include "TemperatureController.h"
#include "OneWire.h"
#include "DallasTemperature.h"

TemperatureController::TemperatureController(TemperatureState temperatureState, int oneWirePin) {
    targetTemp_State = temperatureState;

    //create OneWire object and pass reference to DallasTemperature.
    oneWire = OneWire(oneWirePin);
    sensor = DallasTemperature(&oneWire);
}

float TemperatureController::getCurrentTemperature() {
    sensor.requestTemperatures();
    //returning index 0 because there is only one sensor attached.
    return sensor.getTempCByIndex(0);
}

void TemperatureController::setTargetTemp_State(TemperatureState newTemp_State) {
    targetTemp_State = newTemp_State;
}

void TemperatureController::begin() {
    sensor.begin();
}
