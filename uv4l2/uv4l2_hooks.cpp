#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <dlfcn.h>
#include <string.h>

#include <map>

#include "log.h"
#include "uv4l2.h"

using namespace std;
using namespace uv4l2;

typedef int (*open_fn_type)(const char *pathname, int flags);
typedef int (*close_fn_type)(int fd);
typedef int (*ioctl_fn_type)(int fd, unsigned long request, char *argp);
typedef void* (*mmap_fn_type) (void *addr, size_t len, int prot, int flags,
       int fildes, off_t off);

open_fn_type orig_open;
close_fn_type orig_close;
ioctl_fn_type orig_ioctl;
mmap_fn_type orig_mmap;

extern "C" {
int open(const char *pathname, int flags);
int close(int fd);
int ioctl(int fd, unsigned long request, char *argp);
void *mmap(void *addr, size_t len, int prot, int flags,
       int fd, off_t offset);
}

const int NUM_DEVICES = 2;

/* map fd to device object */
std::map <int, Uv4l2Device*> deviceMap;
Uv4l2Device devicePool[NUM_DEVICES];

static inline void initDevicePool()
{
    DBG_LO("");
    for(int i=0; i < NUM_DEVICES; i++) {
        devicePool[i].id = i;
    }
}

static inline Uv4l2Device *getDevice(int id)
{
    devicePool[id].id = id;
    return &devicePool[id];
}

static inline Uv4l2Device *getDeviceFromFd(int fd)
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
    char dummyFile[32];
    DBG_HI("path = %s", pathname);
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
    rc = dev->open();
    if (rc < 0) {
        ERR("failed");
        goto ret;
    }
    /* create a dummy file to get a unique fd representing this device */
    fd = createDummyFile(id);
    if (fd < 0) {
        ERR("failed");
        rc = fd;
        goto close_dev;
    }
    deviceMap[fd] = dev;
    INFO("success, fd=%d", fd);
    return fd;
close_dev:
    dev->close();
ret:
    return rc;
}

int close(int fd)
{
    DBG_LO("");
    Uv4l2Device *dev = getDeviceFromFd(fd);
    if (dev) {
        dev->close();
    }
    /* even if dev exists, we need to call orig_close(),
     to close the dummy file created in open()*/
    return orig_close(fd);
}

int ioctl(int fd, unsigned long request, char *argp)
{
    DBG_LO("fd=%d", fd);
    Uv4l2Device *dev = getDeviceFromFd(fd);
    if (!dev) {
        INFO("non-uv4l2 device");
        return orig_ioctl(fd, request, argp);
    }
    return dev->ioctl(request, argp);
}

void *mmap(void *addr, size_t len, int prot, int flags,
       int fd, off_t offset)
{
    DBG_LO("fd = %d", fd);
    Uv4l2Device *dev = getDeviceFromFd(fd);
    if (dev) {
        return dev->mmap(addr, len, prot, flags, offset);
    }
    return orig_mmap(addr, len, prot, flags, fd, offset);
}

static void uv4l2_init() __attribute__((constructor));
void uv4l2_init() {
    DBG_LO("");
    initDevicePool();
    orig_open = (open_fn_type) dlsym(RTLD_NEXT,"open");
    orig_close = (close_fn_type) dlsym(RTLD_NEXT,"close");
    orig_ioctl = (ioctl_fn_type) dlsym(RTLD_NEXT, "ioctl");
    orig_mmap = (mmap_fn_type) dlsym(RTLD_NEXT, "mmap");
}
