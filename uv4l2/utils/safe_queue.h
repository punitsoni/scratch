#pragma once

template<typename T>
class SafeQueue
{
public:
    void push(const T & value);
    T pop();
    bool tryPop();
    int size();
private:
    std::mutex _mutex;
    std::condition_variable _cv;
    std::queue<T> _q;
};
