#ifndef __UV4L2_H__
#define __UV4L2_H__

#include <stdint.h>
#include <linux/videodev2.h>

class Uv4l2Device
{
public:
    int id;
    Uv4l2Device();
    int open();
    int close();
    int ioctl(uint32_t request, void *arg);
private:
    bool isOpen = false;
    int querycap(struct v4l2_capability *cap);
    int setFormat(struct v4l2_format *fmt);
    int reqBufs(struct v4l2_requestbuffers *req);
    int queryBuf(struct v4l2_buffer *buf);
    int qbuf(struct v4l2_buffer *buf);
    int dqbuf(struct v4l2_buffer *buf);
    int streamOn(int *type);
    int streamOff(int *type);
};

int createDummyFile(int id);

#endif