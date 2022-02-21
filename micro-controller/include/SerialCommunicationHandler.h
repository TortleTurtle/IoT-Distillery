//
// Created by danie on 10/02/2022.
//

#ifndef MICRO_CONTROLLER_SERIALCOMMUNICATIONHANDLER_H
#define MICRO_CONTROLLER_SERIALCOMMUNICATIONHANDLER_H

#include "ICommunicationHandler.h"

//TODO: Implement Singleton Pattern.
class SerialCommunicationHandler : public ICommunicationHandler {
private:
//atributes needed for storing and modifying incoming data.

    char incomingData[7]{}; //char array to temporarily store incoming data.
    char receivedData[7]{}; //char array to copy incoming data to.
    unsigned int messagePosition; //index of the incomingData array.

    bool receiving;
    bool newData;

public:
    explicit SerialCommunicationHandler();
    void sendTemperature(float temp) override;
    void parseData() override;
    void receiveData() override;

    void update() override;
};

#endif //MICRO_CONTROLLER_SERIALCOMMUNICATIONHANDLER_H
