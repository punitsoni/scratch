#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/videodev2.h>
#include <poll.h>

#include "log.h"

#define BUF_COUNT 8

int main()
{
    struct v4l2_capability cap;
    struct v4l2_format fmt;
    struct v4l2_requestbuffers req;
    struct v4l2_buffer bufs[BUF_COUNT];
    struct v4l2_buffer buf;
    uint8_t *buffers[BUF_COUNT];
    struct pollfd pfds[2];
    int count;

    int rc;
    int fd = open("/dev/video0", O_RDWR);
    if (fd < 0) {
        ERR("open failed");
        goto ret;
    }
    INFO("querying caps");
    rc = ioctl(fd, VIDIOC_QUERYCAP, &cap);
    if (rc) {
        ERR("failed");
        goto close_fd;
    }
    // set format
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = 320;
    fmt.fmt.pix.height = 240;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_NV12;
    fmt.fmt.pix.field = V4L2_FIELD_NONE;
    rc = ioctl(fd, VIDIOC_S_FMT, &fmt);
    if (rc) {
        ERR("s_fmt failed");
        goto close_fd;
    }

    // request buffers
    req.count = BUF_COUNT;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    rc = ioctl(fd, VIDIOC_REQBUFS, &req);
    if (rc) {
        ERR("reqbufs failed");
        goto close_fd;
    }

    // query buffers
    for (int i=0; i<BUF_COUNT; i++) {
        bufs[i].type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        bufs[i].memory = V4L2_MEMORY_MMAP;
        bufs[i].index = i;
        rc = ioctl(fd, VIDIOC_QUERYBUF, &bufs[i]);
        if (rc) {
            ERR("querybuf failed");
            goto close_fd;
        }
        DBG_LO("index=%d, length=%u, offset=%u",
        bufs[i].index, bufs[i].length, bufs[i].m.offset);
    }

    // map buffers into user memory
    for (int i=0; i<BUF_COUNT; i++) {
        buffers[i] = (uint8_t *) mmap(NULL, bufs[i].length,
                    PROT_READ | PROT_WRITE, MAP_SHARED, fd, bufs[i].m.offset);
        if (buffers[i] == MAP_FAILED) {
            ERR("mmap failed");
            goto close_fd;
        }
    }

    // enqueue buffers in driver
    for (int i=0; i<BUF_COUNT; i++) {
        rc = ioctl(fd, VIDIOC_QBUF, &bufs[i]);
        if (rc) {
            ERR("qbuf failed");
            goto close_fd;
        }
    }

    // stream on
    rc = ioctl(fd, VIDIOC_STREAMON, &bufs[0].type);
    if (rc) {
        ERR("streamon failed");
        goto close_fd;
    }

    count = 10;
    // perform streaming operations
    pfds[0].fd = fd;
    pfds[0].events = POLLIN;
    while (count) {
        rc = poll(pfds, 1, -1);
        if (rc == -1) {
            ERR("poll() failed");
            goto close_fd;
        } else if (rc == 0) {
            ERR("poll timed out");
            goto close_fd;
        }
        if (pfds[0].revents & POLLIN) {
            INFO("count = %d", count);
            rc = ioctl(fd, VIDIOC_DQBUF, &buf);
            if (rc) {
                ERR("dqbuf failed");
                goto close_fd;
            }
        }
        count--;
    }

    rc = ioctl(fd, VIDIOC_STREAMOFF, &bufs[0].type);
    if (rc) {
        ERR("streamoff failed");
        goto close_fd;
    }

    INFO("close device");
    close(fd);
    return 0;
close_fd:
    close(fd);
ret:
    return -1;
}
