#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>

#define INFO(fmt, args...) do { \
    fprintf(stderr, "I %s:%d, " fmt "\n", __FUNCTION__, __LINE__, ##args); \
} while (0)

#define ERR(fmt, args...) do { \
    fprintf(stderr, "E %s:%d, " fmt "\n", __func__, __LINE__, ##args); \
} while (0)

#define DBG_HI(fmt, args...) do { \
    fprintf(stderr, "D %s:%d, " fmt "\n", __func__, __LINE__, ##args); \
} while (0)

#define DBG_LO(fmt, args...) do {} while (0)

#endif
