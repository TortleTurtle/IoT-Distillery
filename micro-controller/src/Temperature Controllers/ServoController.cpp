//
// Created by danie on 09/02/2022.
//

#include "ServoController.h"

ServoController::ServoController(TemperatureState temperatureState, DallasTemperature *dallasTemperature, int pin)
        : TemperatureController(temperatureState, dallasTemperature) {
    servo.attach(pin);
    servo.write(0); //set servo to 0 degrees.
}

void ServoController::update() {
    //set servo to certain amount of degrees based on temperature.
    float currentTemp = getCurrentTemperature();
    if (targetTemp_State.temperature > currentTemp && targetTemp_State.state) {
        servo.write(360); //Turn the regulator of the electric plate fully open.
    } else {
        servo.write(0); //Turn off the electric plate.
    }
}