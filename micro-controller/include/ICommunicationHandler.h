//
// Created by danie on 08/02/2022.
//

#ifndef MICRO_CONTROLLER_ICOMMUNICATIONHANDLER_H
#define MICRO_CONTROLLER_ICOMMUNICATIONHANDLER_H
#include <Arduino.h>
#include "global.h"
#include "TemperatureController.h"

//Interfaces in C++ consist of only pure virtual methods. This way an inheriting class needs to implement all methods.
class ICommunicationHandler {
public:
    virtual void sendTemperature(float temp) = 0;
    virtual void receiveData() = 0;
    virtual void update() = 0;
    virtual void parseData() = 0;
};

#endif //MICRO_CONTROLLER_ICOMMUNICATIONHANDLER_H