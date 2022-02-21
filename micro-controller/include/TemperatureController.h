//
// Created by Daniël on 08/02/2022.
//

#ifndef MICRO_CONTROLLER_TEMPERATURECONTROLLER_H
#define MICRO_CONTROLLER_TEMPERATURECONTROLLER_H

#include "OneWire.h"
#include "DallasTemperature.h"
#include "global.h"


class TemperatureController {
public:
    //pure virtual function. This makes it an abstract class.
    virtual void update() = 0;

    TemperatureController(TemperatureState temperatureState, int oneWirePin);
    void begin();
    float getCurrentTemperature();
    //static member function so other classes can call on it.
    static void setTargetTemp_State(TemperatureState newTemp_State); //set a new target temperature and state.

protected:
    //static member variable so it has an allocated place in the memory. Shared across all instances.
    static TemperatureState targetTemp_State;
    OneWire oneWire;
    DallasTemperature sensor;
};


#endif //MICRO_CONTROLLER_TEMPERATURECONTROLLER_H