#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "log.h"
#include "uv4l2.h"

using namespace std;

#define DRIVER_NAME "domino"
#define CAP_DRVNAME_SIZE_MAX 16


int createDummyFile(int id)
{
    int fd;
    char dummyFile[32];
    snprintf(dummyFile, 32, "/tmp/dummy%d", id);
    fd = creat(dummyFile, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd < 0) {
        ERR("failed");
        perror("");
    }
    return fd;
}

Uv4l2Device::Uv4l2Device()
{
}

int Uv4l2Device::open()
{
    int rc=0;
    if(this->isOpen) {
        ERR("device is already open");
        rc = -1;
        goto ret;
    }
    isOpen = true;
    return 0;
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

int Uv4l2Device::querycap(struct v4l2_capability *cap)
{
    INFO("");
    memset(cap, 0x00, sizeof(struct v4l2_capability));
    strncpy((char *) cap->driver, DRIVER_NAME, CAP_DRVNAME_SIZE_MAX);
    cap->capabilities |= V4L2_CAP_VIDEO_CAPTURE;
    cap->capabilities |= V4L2_CAP_STREAMING;
    cap->device_caps = cap->capabilities;
    return 0;
}

int Uv4l2Device::setFormat(struct v4l2_format *fmt)
{
    INFO("");
    return 0;
}

int Uv4l2Device::reqBufs(struct v4l2_requestbuffers *req)
{
    INFO("");
    return 0;
}

int Uv4l2Device::queryBuf(struct v4l2_buffer *buf)
{
    INFO("");
    return 0;
}

int Uv4l2Device::qbuf(struct v4l2_buffer *buf)
{
    INFO("");
    return 0;
}

int Uv4l2Device::dqbuf(struct v4l2_buffer *buf)
{
    INFO("");
    return 0;
}

int Uv4l2Device::streamOn(int *type)
{
    INFO("");
    return 0;
}

int Uv4l2Device::streamOff(int *type)
{
    INFO("");
    return 0;
}

int Uv4l2Device::ioctl(uint32_t request, void *arg)
{
    int rc = 0;
    if (!arg) {
        ERR("failed, arg=NULL");
        rc = -1;
        goto ret;
    }
    switch(request) {
    case VIDIOC_QUERYCAP:
        rc = this->querycap((struct v4l2_capability *) arg);
        break;
    case VIDIOC_S_FMT:
        rc = this->setFormat((struct v4l2_format *) arg);
        break;
    case VIDIOC_REQBUFS:
        rc = this->reqBufs((struct v4l2_requestbuffers *) arg);
        break;
    case VIDIOC_QUERYBUF:
        rc = this->queryBuf((struct v4l2_buffer *) arg);
        break;
    case VIDIOC_QBUF:
        rc = this->qbuf((struct v4l2_buffer *) arg);
        break;
    case VIDIOC_DQBUF:
        rc = this->dqbuf((struct v4l2_buffer *) arg);
        break;
    case VIDIOC_STREAMON:
        rc = this->streamOn((int *) arg);
        break;
    case VIDIOC_STREAMOFF:
        rc = this->streamOff((int *) arg);
        break;
    case VIDIOC_QUERYCTRL:
        //rc = this->queryCtrl((int *) arg);
        break;
    case VIDIOC_G_CTRL:
        //rc = this->getCtrl((int *) arg);
        break;
    case VIDIOC_S_CTRL:
        //rc = this->setCtrl((int *) arg);
        break;
    default:
        ERR("invalid request 0x%x", request);
        rc = -1;
        break;
    }
ret:
    return rc;
}
