#ifndef __UV4L2_H__
#define __UV4L2_H__

#include <stdint.h>

class Uv4l2Device
{
public:
    int id;
    Uv4l2Device();
    int open();
    int close();
    int ioctl(uint32_t request, void *arg);
private:
    int fd;
    bool isOpen;

    int initialize();
};

#endif