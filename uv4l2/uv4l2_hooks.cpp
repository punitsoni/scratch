#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <dlfcn.h>
#include <string.h>

#include <map>

#include "log.h"
#include "uv4l2.h"

using namespace std;

typedef int (*open_fn_type)(const char *pathname, int flags);
typedef int (*close_fn_type)(int fd);
typedef int (*ioctl_fn_type)(int fd, unsigned long request, char *argp);

open_fn_type orig_open;
close_fn_type orig_close;
ioctl_fn_type orig_ioctl;

extern "C" {
int open(const char *pathname, int flags);
int close(int fd);
int ioctl(int fd, unsigned long request, char *argp);
}

const int NUM_DEVICES = 2;

/* map fd to device object */
std::map <int, Uv4l2Device*> deviceMap;
Uv4l2Device devicePool[NUM_DEVICES];

static void initDevicePool()
{
    for(int i=0; i < NUM_DEVICES; i++) {
        devicePool[i].id = i;
    }
}

static Uv4l2Device *getDevice(int id)
{
    devicePool[id].id = id;
    return &devicePool[id];
}

static Uv4l2Device *getDeviceFromFd(int fd)
{
    auto it = deviceMap.find(fd);
    if (it == deviceMap.end()) {
        return NULL;
    }
    return it->second;
}

int uv4l2_get_devid(const char *path)
{
    char temp_path[32];
    for(int i=0; i<NUM_DEVICES; i++) {
        snprintf(temp_path, 32, "/dev/video%d", i);
        if (strncmp(temp_path, path, 32) == 0) {
            return i;
        }
    }
    return -1;
}

int open(const char *pathname, int flags)
{
    int rc;
    int fd;
    INFO("path = %s", pathname);
    int id = uv4l2_get_devid(pathname);
    if (id < 0) {
        INFO("non-uv4l2 device, %s", pathname);
        return orig_open(pathname, flags);
    }
    Uv4l2Device *dev = getDevice(id);
    if (dev == NULL) {
        rc = -1;
        ERR("failed");
        goto ret;
    }
    fd = dev->open();
    if (fd < 0) {
        ERR("failed");
        rc = fd;
        goto ret;
    }
    deviceMap[fd] = dev;
    return fd;
ret:
    return rc;
}

int close(int fd)
{
    int rc = 0;
    INFO("");
    Uv4l2Device *dev = getDeviceFromFd(fd);
    if (dev) {
        dev->close();
    }
    return orig_close(fd);
ret:        
    return rc;
}

int ioctl(int fd, unsigned long request, char *argp)
{
    int rc = 0;
    INFO("fd=%d", fd);
    Uv4l2Device *dev = getDeviceFromFd(fd);
    if (!dev) {
        rc = -1;
        INFO("non-uv4l2 device");
        return orig_ioctl(fd, request, argp);
    }
    return dev->ioctl(request, argp);
ret:        
    return rc;
}

static void uv4l2_init() __attribute__((constructor));
void uv4l2_init() {
    INFO("");
    initDevicePool();
    orig_open = (open_fn_type) dlsym(RTLD_NEXT,"open");
    orig_close = (close_fn_type) dlsym(RTLD_NEXT,"close");
    orig_ioctl = (ioctl_fn_type) dlsym(RTLD_NEXT, "ioctl");
}