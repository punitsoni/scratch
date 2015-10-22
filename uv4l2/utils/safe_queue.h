#ifndef __SAFE_QUEUE_H__
#define __SAFE_QUEUE_H__

template<typename T>
class SafeQueue
{
public:
    void push(const T & value);
    T pop();
    int size();
private:
    std::mutex _mutex;
    std::condition_variable _cv;
    std::queue<T> _q;
};

#endif
