//
// Created by danie on 09/02/2022.
//

#include "ServoController.h"

ServoController::ServoController(float targetTemp, bool state, int oneWirePin, int servoPin)
        : TemperatureController(targetTemp, state, oneWirePin) {
    ServoController::servoPin = servoPin;
}

void ServoController::update() {
    TemperatureController::update();
    //set servo to certain amount of degrees based on temperature.
}
