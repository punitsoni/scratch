#ifndef __UV4L2_H__
#define __UV4L2_H__

#include <stdint.h>
#include <linux/videodev2.h>

#include <vector>

namespace uv4l2 {

struct MappedBuffer {
    struct v4l2_buffer v4l2Buf;
    void *vaddr;
};

class Uv4l2Device
{
public:
    int id;
    Uv4l2Device();
    int open();
    int close();
    int ioctl(uint32_t request, void *arg);
    void* mmap(void *addr, size_t len, int prot, int flags, off_t offset);
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

    int releaseMappedBuffers();
    int createMappedBuffers(int count);

    std::vector<MappedBuffer> mappedBufs;
    struct v4l2_format currentFormat;
    bool isOpen = false;
};

int createDummyFile(int id);

};

#endif
