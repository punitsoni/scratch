#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

#include "log.h"

int main()
{
    struct v4l2_capability cap;
    struct v4l2_format fmt = {0};

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

    INFO("close device");
    close(fd);
    return 0;
close_fd:
    close(fd);
ret:
    return -1;
}
