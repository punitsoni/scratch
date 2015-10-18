#include <string.h>
#include <linux/videodev2.h>
#include <fcntl.h>
#include <unistd.h>
#include "log.h"
#include "uv4l2.h"

#define DEV_IDS_MAX 2

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
    fd = ::open(dummyFile, O_RDWR|O_CREAT);
    if (fd < 0) {
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
    return ::close(fd);
ret:
    return rc;
}

int uv4l2_close(int fd)
{
    int rc = 0;
    INFO("fd = %d", fd);
    return rc;
}

int uv4l2_ioctl(int fd, unsigned long request, char *argp)
{
    int rc=0;
    INFO("fd=%d, req=0x%0lx", fd, request);
    return rc;
}
