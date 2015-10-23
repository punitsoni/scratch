#pragma once

#include <stdint.h>
#include <thread>

namespace uv4l2 {

class TestGenListener {
public:
    virtual void onFrame(uint8_t *data) = 0;
};

class TestGen {
public:
    int start();
    int stop();
    int config(int w, int h) { width = w; height = h; }
    void setListener(TestGenListener *lis) { _listener = lis; }
    bool isStreaming() { return _isStreaming; }
private:
    int width = 0;
    int height = 0;
    TestGenListener *_listener;
    void threadFunc();
    bool stopRequested = false;
    bool _isStreaming = false;
    std::thread th;
};

}; /* namespace uv4l2 */
