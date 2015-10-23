#pragma once

#include <stdint.h>
#include <linux/videodev2.h>

#include <vector>
#include <queue>

#include "testgen.h"

namespace uv4l2 {

struct MappedBuffer {
    struct v4l2_buffer v4l2Buf;
    void *vaddr;
};

class BufManager {
public:
    int releaseMappedBuffers();
    int createMappedBuffers(int count, uint32_t size);
    void *mapBuf(off_t offset);
    int getBuf();
    int bufDone();
    int putBuf(uint32_t index);
    MappedBuffer *findBuf(uint32_t index);
private:
    std::vector<MappedBuffer> _mappedBufs;
    std::queue<MappedBuffer*> _inQueue;
    std::queue<MappedBuffer*> _outQueue;
};

class Uv4l2Device : TestGenListener
{
public:
    int id;
    Uv4l2Device();
    int open();
    int close();
    int ioctl(uint32_t request, void *arg);
    void* mmap(void *addr, size_t len, int prot, int flags, off_t offset);
    int poll();
    virtual void onFrame(uint8_t *data);
private:
    // ioctl handlers
    int queryCap(struct v4l2_capability *cap);
    int setFormat(struct v4l2_format *fmt);
    int reqBufs(struct v4l2_requestbuffers *req);
    int queryBuf(struct v4l2_buffer *buf);
    int qbuf(struct v4l2_buffer *buf);
    int dqbuf(struct v4l2_buffer *buf);
    int streamOn(int *type);
    int streamOff(int *type);

    BufManager bufMgr;
    struct v4l2_format currentFormat;
    bool isOpen = false;
    TestGen gen;

    int _pipeReadFd;
    int _pipeWriteFd;
};

};
