#include <WebSocketsServer.h>
#include <cstdint>
#include <Arduino.h>
#include <Hash.h>

class SwController
{
public:
    SwController();
    void update();
    void start();

private:
    uint32_t last_update_ms = 0;
    WebSocketsServer server;
    int num_clients = 0;
    int led_pin = LED_BUILTIN;
    int button_pin = 1;
    bool sw_state = false;

    static SwController *obj;
    static const int MAX_CLIENTS = 1;

    void handleMessage(char *msg);
    void onMessage(uint8_t client_id, const String& message);
    void onClientConnected(uint8_t client_id);
    void onClientDisconnected(uint8_t client_id);

    static void websocketEventCb(uint8_t num, WStype_t type, uint8_t * payload,
                            size_t length);
};
