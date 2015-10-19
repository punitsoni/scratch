#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

#include "log.h"

int main()
{
    struct v4l2_capability cap;
    int rc;
    int fd = open("/dev/video0", O_RDWR);
    if (fd < 0) {
        ERR("open failed");
        goto ret;
    }
    INFO("querying caps");
    rc = ioctl(fd, VIDIOC_QUERYCAP, &cap);
    if (rc < 0) {
        ERR("failed");
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