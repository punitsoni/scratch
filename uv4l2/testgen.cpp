#include "testgen.h"
#include "log.h"

#include <chrono>

using namespace std;

namespace uv4l2 {

int TestGen::start()
{
    th = thread(&TestGen::threadFunc, this);
    _isStreaming = true;
    return 0;
}

int TestGen::stop()
{
    INFO("");
    stopRequested = true;
    th.join();
    _isStreaming = false;
    return 0;
}

void TestGen::threadFunc()
{
    while(!stopRequested) {
        _listener->onFrame(NULL);
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    INFO("DONE");
}

}; /* namespace uv4l2 */
