//
// Created by danie on 09/02/2022.
//

#include "ServoController.h"

ServoController::ServoController(TemperatureState temperatureState, int oneWirePin, int servoPin)
        : TemperatureController(temperatureState, oneWirePin) {
    ServoController::servoPin = servoPin;
}

void ServoController::update() {
    //set servo to certain amount of degrees based on temperature.
}
