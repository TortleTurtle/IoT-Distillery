//
// Created by danie on 16/02/2022.
//

#ifndef MICRO_CONTROLLER_HTPP_COMMUNICATIONHANDLER_H
#define MICRO_CONTROLLER_HTPP_COMMUNICATIONHANDLER_H

#include "ICommunicationHandler.h"
#include "ESP8266WiFi.h"
#include "ESP8266WiFiMulti.h"
#include "ESP8266HTTPClient.h"
#include "WiFiClient.h"
#include "string"
#include "ArduinoJson.h"
#include "global.h"

class HTPP_CommunicationHandler : public ICommunicationHandler {
private:
    //Instances needed to connect to Wi-Fi and make http requests.
    ESP8266WiFiMulti WiFiMulti;
    WiFiClient client;
    HTTPClient http;
    String apiUrl;
    DynamicJsonDocument document = DynamicJsonDocument(64);
    String JSON;

    unsigned long startMillis;
    unsigned long currentMillis;

public:
    explicit HTPP_CommunicationHandler(const char *ssid, const char *password, const String& url);
    void sendTemperature(float temp) override;
    void parseData() override;
    void receiveData() override;
    void update() override;
};


#endif //MICRO_CONTROLLER_HTPP_COMMUNICATIONHANDLER_H
