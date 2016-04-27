#include "scontrol.h"
#include <cstdio>
#include <ESP8266Wifi.h>

namespace neptune {

SwController* SwController::obj = NULL;

SwController::SwController():
server(80)
{
    server.onEvent(SwController::websocketEventCb);
    pinMode(led_pin, OUTPUT);
}

SwController* SwController::getInstance()
{
    static SwController controller;
    controller.obj = &controller;
    return &controller;
}

void SwController::start()
{
    server.begin();
    Serial.print("websocket server started at ws://" + WiFi.localIP());
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
void SwController::updateSwitch(bool val)
{
    sw_state = val;
    digitalWrite(led_pin, (sw_state) ? LOW : HIGH);

    String resp = String("S_") + ((sw_state) ? "ON" : "OFF");
    Serial.println("resp: " + resp);
    for(int i=0; i<MAX_CLIENTS; i++) {
        if (clients[i].connected == true) {
            server.sendTXT(clients[i].id, resp);
        }
    }
}

void SwController::onMessage(uint8_t client_id, const String& message)
{
    Serial.println("[MSG_IN] " + message);
    if (message == "C_ON") {
        updateSwitch(true);
    } else if(message == "C_OFF") {
        updateSwitch(false);
    }
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

    for(int i=0; i<MAX_CLIENTS; i++) {
        if (clients[i].connected == false) {
            clients[i].id = client_id;
            clients[i].connected = true;
        }
    }
    server.sendTXT(client_id, String("HELLO"));
    updateSwitch(sw_state);
}

void SwController::onClientDisconnected(uint8_t client_id)
{
    Serial.println("Client " + String(client_id) + " disconnected.");
    num_clients--;
    for(int i=0; i<MAX_CLIENTS; i++) {
        if (clients[i].id == client_id) {
            clients[i].connected = false;
        }
    }
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

}
