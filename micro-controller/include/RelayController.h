//
// Created by danie on 09/02/2022.
//

#ifndef MICRO_CONTROLLER_RELAYCONTROLLER_H
#define MICRO_CONTROLLER_RELAYCONTROLLER_H


#include "TemperatureController.h"

class RelayController : public TemperatureController {
private:
    int relayPin;
public:
    RelayController(float targetTemp, bool state, int oneWirePin, int relayPin);

    //override is not necessary when using virtual but is good practice.
    void update() override;
};


#endif //MICRO_CONTROLLER_RELAYCONTROLLER_H
