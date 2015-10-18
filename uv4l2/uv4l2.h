#ifndef __UV4L2_H__
#define __UV4L2_H__

#ifdef __cplusplus
extern "C" {
#endif

int uv4l2_open(int id, int flags);
int uv4l2_close(int fd);
int uv4l2_ioctl(int id, unsigned long request, char *argp);
int uv4l2_get_devid(const char *path);

#ifdef __cplusplus
}
#endif

class Uv4l2Device
{
public:
    int id;
    Uv4l2Device();
    int open();
    int close();
private:
    int fd;
    bool isOpen;

    int initialize();
};

#endif