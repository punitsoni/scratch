#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/videodev2.h>

#include "log.h"

int main()
{
    struct v4l2_capability cap;
    struct v4l2_format fmt = {0};
    struct v4l2_requestbuffers req = {0};
    struct v4l2_buffer buf = {0};
    uint8_t *buffer;

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
    req.count = 1;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    rc = ioctl(fd, VIDIOC_REQBUFS, &req);
    if (rc) {
        ERR("reqbufs failed");
        goto close_fd;
    }

    // query buffer
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = 0;
    rc = ioctl(fd, VIDIOC_QUERYBUF, &buf);
    if (rc) {
        ERR("querybuf failed");
        goto close_fd;
    }

    INFO("index=%d, length=%u, offset=%u", buf.index, buf.length, buf.m.offset);

    // map buffer into user memory
    buffer = (uint8_t *) mmap(NULL, buf.length, PROT_READ | PROT_WRITE,
                    MAP_SHARED, fd, buf.m.offset);
    if (buffer == MAP_FAILED) {
        ERR("mmap failed");
        goto close_fd;
    }

    // stream on
    rc = ioctl(fd, VIDIOC_STREAMON, &buf.type);
    if (rc) {
        ERR("streamon failed");
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
