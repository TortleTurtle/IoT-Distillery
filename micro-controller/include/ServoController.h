//
// Created by danie on 09/02/2022.
//

#ifndef MICRO_CONTROLLER_SERVOCONTROLLER_H
#define MICRO_CONTROLLER_SERVOCONTROLLER_H

#include "TemperatureController.h"

class ServoController : public TemperatureController {
private:
    int servoPin;
public:
    ServoController(TemperatureState temperatureState, int oneWirePin, int servoPin);
    void update() override;
};


#endif //MICRO_CONTROLLER_SERVOCONTROLLER_H
