#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>

#include "log.h"
#include "uv4l2.h"

using namespace std;

#define DRIVER_NAME "domino"
#define CAP_DRVNAME_SIZE_MAX 16

namespace uv4l2 {

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

void Uv4l2Device::onFrame(uint8_t *data)
{
    int rc;
    INFO("");
    uint8_t dummyData = 0xFF;
    rc = write(_pipeWriteFd, &dummyData, 1);
    if (rc < 0) {
        ERR("write failed\n");
        return;
    }
}

int Uv4l2Device::open()
{
    int rc=0;
    if(this->isOpen) {
        ERR("device is already open");
        rc = -1;
        goto ret;
    }
    int fds[2];
    rc = pipe(fds);
    if (rc) {
        ERR("pipe failed");
        goto ret;
    }
    _pipeReadFd = fds[0];
    _pipeWriteFd = fds[1];
    isOpen = true;
    return _pipeReadFd;
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
    bufMgr.releaseMappedBuffers();
    if (gen.isStreaming()) {
        gen.stop();
    }
    ::close(_pipeWriteFd);
    return 0;
ret:
    return rc;
}

void *Uv4l2Device::mmap(void *addr, size_t len, int prot,
                        int flags, off_t offset)
{
    return bufMgr.mapBuf(offset);
}

int Uv4l2Device::poll()
{
    return 0;
}

static inline bool isBufTypeValid(int type)
{
    if (type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
        return true;
    }
    return false;
}

int Uv4l2Device::queryCap(struct v4l2_capability *cap)
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
    memcpy(&currentFormat, fmt, sizeof(struct v4l2_format));
    return 0;
}

int Uv4l2Device::reqBufs(struct v4l2_requestbuffers *req)
{
    int rc;
    uint32_t size;
    DBG_LO("");
    if (!isBufTypeValid(req->type)) {
        ERR("unsupported buf type %d", req->type);
        rc = -EINVAL;
        goto ret;
    }
    switch (req->memory) {
    case V4L2_MEMORY_MMAP:
        INFO("count = %d", req->count);
        size = currentFormat.fmt.pix.width * currentFormat.fmt.pix.height;
        rc = bufMgr.createMappedBuffers(req->count, size);
        if (rc) {
            ERR("failed");
            rc = -ENOMEM;
            goto ret;
        }
        break;
    default:
        ERR("unsupported memory type %d", req->memory);
        rc = -EINVAL;
        goto ret;
    }
    return 0;
ret:
    return rc;
}

int Uv4l2Device::queryBuf(struct v4l2_buffer *buf)
{
    int rc;
    MappedBuffer *mbuf;
    INFO("");
    if (!isBufTypeValid(buf->type)) {
        ERR("unsupported buf type %d", buf->type);
        rc = -EINVAL;
        goto ret;
    }
    mbuf = bufMgr.findBuf(buf->index);
    if (!mbuf) {
        ERR("failed");
        rc = -EINVAL;
        goto ret;
    }
    *buf = mbuf->v4l2Buf;
    return 0;
ret:
    return rc;
}

int Uv4l2Device::qbuf(struct v4l2_buffer *buf)
{
    int rc;
    INFO("");

    rc = bufMgr.putBuf(buf->index);
    if (rc) {
        ERR("failed");
        rc = -EINVAL;
        goto ret;
    }
    return 0;
ret:
    return rc;
}

int Uv4l2Device::dqbuf(struct v4l2_buffer *buf)
{
    int rc;
    INFO("");
    uint8_t dummyData;
    rc = read(_pipeReadFd, &dummyData, 1);
    if (rc != 1) {
        ERR("read failed");
        rc = -1;
        goto ret;
    }
    return 0;
ret:
    return rc;
}

int Uv4l2Device::streamOn(int *type)
{
    INFO("");
    gen.setListener(this);
    gen.start();
    return 0;
}

int Uv4l2Device::streamOff(int *type)
{
    INFO("");
    gen.stop();
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
        rc = this->queryCap((struct v4l2_capability *) arg);
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

int BufManager::releaseMappedBuffers()
{
    INFO("");
    for(int i=0; i<_mappedBufs.size(); i++) {
        free(_mappedBufs[i].vaddr);
    }
    _mappedBufs.clear();
    return 0;
}

int BufManager::createMappedBuffers(int count, uint32_t size)
{
    int rc;
    MappedBuffer buf = {0};

    if (count == 0) {
        return releaseMappedBuffers();
    }

    _mappedBufs.resize(count);
    for (int i=0; i<count; i++) {
        buf.v4l2Buf.index = i;
        buf.v4l2Buf.length = size;
        buf.v4l2Buf.memory = V4L2_MEMORY_MMAP;
        buf.v4l2Buf.m.offset = i * buf.v4l2Buf.length;
        buf.vaddr = malloc(buf.v4l2Buf.length);
        if (!buf.vaddr) {
            ERR("malloc failed");
            rc = -ENOMEM;
            goto ret;
        }
        _mappedBufs[i] = buf;
        INFO("buffer %d created", i);
    }
    return 0;
ret:
    return rc;
}

void *BufManager::mapBuf(off_t offset)
{
    void *mapAddr;
    uint32_t index = offset / _mappedBufs[0].v4l2Buf.length;
    INFO("index=%d", index);

    if (index >= _mappedBufs.size()) {
        ERR("invalid offset %ld", offset);
        goto ret;
    }
    _mappedBufs[index].v4l2Buf.flags |= V4L2_BUF_FLAG_MAPPED;
    mapAddr = _mappedBufs[index].vaddr;
    return mapAddr;
    ret:
    return MAP_FAILED;
}

int BufManager::getBuf()
{
    _inQueue.pop();
}

int BufManager::putBuf(uint32_t index)
{
    int rc;
    if (index >= _mappedBufs.size()) {
        ERR("failed");
        rc = -EINVAL;
        goto ret;
    }
    //TODO: error checking for buffer state (flags)
    _mappedBufs[index].v4l2Buf.flags |= V4L2_BUF_FLAG_QUEUED;
    _inQueue.push(&_mappedBufs[index]);
    return 0;
ret:
    return rc;
}

MappedBuffer* BufManager::findBuf(uint32_t index)
{
    MappedBuffer *mbuf;
    if (index >= _mappedBufs.size()) {
        ERR("failed");
        goto ret;
    }
    return &_mappedBufs[index];
ret:
    return NULL;
}



}; /* namespace uv4l2 */
