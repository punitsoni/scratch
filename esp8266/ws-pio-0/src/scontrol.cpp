#include "scontrol.h"
#include <cstdio>
#include <ESP8266Wifi.h>

SwController* SwController::obj = NULL;

SwController::SwController():
server(80)
{
    if (obj == NULL)
        obj = this;
}

void SwController::start()
{
    server.onEvent(SwController::websocketEventCb);
    server.begin();
    pinMode(led_pin, OUTPUT);
    Serial.print("websocket server started at ws://" + String(WiFi.localIP()));
}

void SwController::update()
{
    uint32_t ms = millis();
    uint32_t update_period = 10;

    server.loop();

    if (ms - last_update_ms < update_period) {
        return;
    }
}

void SwController::onMessage(uint8_t client_id, const String& message)
{
    Serial.println("[MSG_IN] " + message);
    uint8_t val;
    if (message == "C ON") {
        val = LOW;
        sw_state = true;
    } else if(message == "C OFF") {
        val = HIGH;
        sw_state = false;
    } else {
        return;
    }
    digitalWrite(led_pin, (sw_state) ? LOW : HIGH);
    server.sendTXT(client_id, "S " + (sw_state) ? "ON" : "OFF");
}

void SwController::onClientConnected(uint8_t client_id)
{
    num_clients++;
    if (num_clients > MAX_CLIENTS) {
        Serial.println("Could not connect for client " + String(client_id) +
            ". Max limit reached");
        server.sendTXT(client_id, String("ERR_BUSY"));
        server.disconnect(client_id);
        return;
    }
    Serial.println("Client " + String(client_id) + " connected.");
    server.sendTXT(client_id, String("HELLO"));
}

void SwController::onClientDisconnected(uint8_t client_id)
{
    Serial.println("Client " + String(client_id) + " disconnected.");
    num_clients--;
}

void SwController::websocketEventCb(uint8_t num, WStype_t type,
    uint8_t *payload, size_t length)
{
    switch (type) {
    case WStype_DISCONNECTED:
        obj->onClientDisconnected(num);
        break;
    case WStype_CONNECTED:
        obj->onClientConnected(num);
        break;
    case WStype_TEXT:
        obj->onMessage(num, String((char *)payload));
        break;
    case WStype_BIN:
        break;
    }
}
