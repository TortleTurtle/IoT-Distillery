//
// Created by danie on 16/02/2022.
//

#include "HTPP_CommunicationHandler.h"

HTPP_CommunicationHandler::HTPP_CommunicationHandler(const char *ssid, const char *password, const String& url) {
    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP(ssid, password); //information to connect with Wi-Fi Network.
    apiUrl = url;

    JSON = "";

    startMillis = millis();
    currentMillis = millis();
}

void HTPP_CommunicationHandler::receiveData() {
    Serial.println("Fetching data from API");
    //check if connected to Wi-Fi
    if (WiFiMulti.run() == WL_CONNECTED) {
        Serial.println("Connected to Wi-Fi");

        //connect to server
        if (http.begin(client, apiUrl)) {
            int httpCode = http.GET(); //fetch response

            if (httpCode > 0) {
                // Print response code
                Serial.printf("[HTTP] GET... code: %d\n", httpCode);

                // Server responded with a file.
                if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
                    String receivedJSON = http.getString();
                    Serial.print("Recieved payload: ");
                    Serial.println(receivedJSON);
                    parseData();
                    http.end();
                }
            } else {
                Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
            }
        }
    } else {
        Serial.println("Error: Could not connect to Wi-Fi");
    }
}

void HTPP_CommunicationHandler::parseData() {
    Serial.println("Parsing json");
    DeserializationError error = deserializeJson(document, JSON);

    if (!error) {
        TemperatureState parsedJson = {document["temp"], document["state"]};

        //log parsed Json
        Serial.print("Temperature: ");
        Serial.println(parsedJson.temperature);
        Serial.print("State: ");
        Serial.println(parsedJson.state);

        //pass on the parsed data to the temperature controller.
        TemperatureController::setTargetTemp_State(parsedJson);
    } else {
        Serial.print("deserialization failed: ");
        Serial.println(error.f_str());
    }
}

void HTPP_CommunicationHandler::sendTemperature(float temp) {
    //check connection to wifi.
    if (WiFiMulti.run() == WL_CONNECTED) {
        Serial.println("Connected to Wi-Fi");

        if (http.begin(client, apiUrl)) {
            http.addHeader("Content-Type", "application/json");

            //creating the body.
            DynamicJsonDocument body(64); //Object used to create a JSON document.
            String serializedBody; //Variable used to store serialized JSON.
            body["temp"].set(temp);

            serializeJson(body, serializedBody);

            int httpCode = http.POST(serializedBody); //send the request.

            if (httpCode > 0) {
                // HTTP header has been send and Server response header has been handled
                Serial.printf("[HTTP] POST... code: %d\n", httpCode);

                // file found at server
                if (httpCode == HTTP_CODE_OK) {
                    const String& payload = http.getString();
                    Serial.println("received payload:\n<<");
                    Serial.println(payload);
                    Serial.println(">>");
                }
            } else {
                Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
            }

            http.end();
        }
    }
}

void HTPP_CommunicationHandler::update() {
    //timer to send GET and POST request.
    currentMillis = millis();
    if (currentMillis - startMillis >= 1000 * 60) {
        receiveData();
        sendTemperature(TemperatureController::getCurrentTemperature());
        startMillis = currentMillis;
    }
}