#include <Arduino.h>
#include "TemperatureController.h"

//using a pointer to declare
TemperatureController* tempController;

void setup() {
    //creating a Temperature controller and assigning it to the pointer.
    tempController = new TemperatureController(65.0, false, 1);
}

void loop() {
    tempController->update();
}