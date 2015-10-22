#include "safe_queue.h"

using namespace std;

void SafeQueue::push(const T& value)
{
    {
        unique_lock<mutex> lock(_mutex);
        _q.push(val);
    }
}

T SafeQueue::pop()
{
    unique_lock<mutex> lock(_mutex);
    T value(move(_q->front()));
    _q.pop();
    return val;
}

int size()
{
    return _q.size();
}
