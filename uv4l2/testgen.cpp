#include "testgen.h"
#include "log.h"

#include <chrono>

using namespace std;

namespace uv4l2 {

int TestGen::start()
{
    th = thread(&TestGen::threadFunc, this);
    return 0;
}

int TestGen::stop()
{
    INFO("");
    stopRequested = true;
    th.join();
    return 0;
}

void TestGen::threadFunc()
{
    while(!stopRequested) {
        INFO("");
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

}; /* namespace uv4l2 */
