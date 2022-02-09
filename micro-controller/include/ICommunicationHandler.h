//
// Created by danie on 08/02/2022.
//

#ifndef MICRO_CONTROLLER_ICOMMUNICATIONHANDLER_H
#define MICRO_CONTROLLER_ICOMMUNICATIONHANDLER_H


class ICommunicationHandler {
public:
    virtual void sendTemperature(float temp);

protected:
    virtual void recieveData();
    virtual void parseData();
    virtual void showParsedData();
};

#endif //MICRO_CONTROLLER_ICOMMUNICATIONHANDLER_H