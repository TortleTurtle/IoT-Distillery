//
// Created by danie on 09/02/2022.
//

#ifndef MICRO_CONTROLLER_SERVOCONTROLLER_H
#define MICRO_CONTROLLER_SERVOCONTROLLER_H

#include "TemperatureController.h"
#include "Servo.h"

class ServoController : public TemperatureController {
private:

    Servo servo;
public:
    ServoController(TemperatureState temperatureState, DallasTemperature *dallasTemperature, int pin);
    void update() override;
};


#endif //MICRO_CONTROLLER_SERVOCONTROLLER_H
