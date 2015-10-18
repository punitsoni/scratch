#include <string.h>
#include <linux/videodev2.h>
#include <fcntl.h>
#include <unistd.h>
#include "log.h"
#include "uv4l2.h"

using namespace std;

Uv4l2Device::Uv4l2Device()
{
    initialize();
}

int Uv4l2Device::initialize()
{
    id = -1;
    fd = -1;
    isOpen = false;
}

int Uv4l2Device::open()
{
    int rc=0;
    if(this->isOpen) {
        ERR("device is already open");
        rc = -1;
        goto ret;
    }
    char dummyFile[32];
    snprintf(dummyFile, 32, "/tmp/dummy%d", id);
    fd = creat(dummyFile, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd < 0) {
        perror("");
        ERR("failed");
        rc = fd;
        goto ret;
    }
    isOpen = true;
    INFO("Success. fd=%d", fd);
    return fd;
ret:
    return rc;
}

int Uv4l2Device::close()
{
    int rc = 0;
    if (!isOpen) {
        ERR("device is not open");
        rc = -1;
        goto ret;
    }
    return 0;
ret:
    return rc;
}

int Uv4l2Device::ioctl(uint32_t request, void *arg)
{
    int rc = 0;
    INFO("req=%x, arg=%p", request, arg);
    return rc;
}