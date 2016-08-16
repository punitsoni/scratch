#include <Arduino.h>
#include <ESP8266Wifi.h>
#include "scontrol.h"

const char WIFI_SSID[] = "ncsu";
const char WIFI_PASS[] = "cocacola";

neptune::SwController *ctrl;

void setup()
{
    Serial.begin(115200);
    Serial.println("");
    Serial.println("Connecting to wifi...");
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while(WiFi.status() != WL_CONNECTED) {
        delay(100);
    }
    Serial.println("Wifi Connected.");
    Serial.println(WiFi.localIP());
    ctrl = neptune::SwController::getInstance();
    ctrl->start();
}

void loop()
{
    ctrl->update();
}
