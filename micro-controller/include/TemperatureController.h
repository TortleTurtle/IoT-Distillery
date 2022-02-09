//
// Created by Daniël on 08/02/2022.
//

#ifndef MICRO_CONTROLLER_TEMPERATURECONTROLLER_H
#define MICRO_CONTROLLER_TEMPERATURECONTROLLER_H

#include "OneWire.h"
#include "DallasTemperature.h"

class TemperatureController {
protected:
    float targetTemperature;
    bool state;
    OneWire oneWire;
    DallasTemperature sensor;
public:
    TemperatureController(float targetTemp, bool state, int oneWirePin);
    void setTargetTemperature(float targetTemp);
    float getCurrentTemperature();
    void setState(bool newState);
    virtual void update();
};


#endif //MICRO_CONTROLLER_TEMPERATURECONTROLLER_H