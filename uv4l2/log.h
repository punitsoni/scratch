#pragma once

#include <stdio.h>

#define USE_PRETTY_FUNCTION 0

#if USE_PRETTY_FUNCTION
#define __func_name __PRETTY_FUNCTION__
#else
#define __func_name __func__
#endif

#define INFO(fmt, args...) do { \
    fprintf(stderr, "I %s:%d, " fmt "\n", __func_name, __LINE__, ##args); \
} while (0)

#define ERR(fmt, args...) do { \
    fprintf(stderr, "E %s:%d, " fmt "\n", __func_name, __LINE__, ##args); \
} while (0)

#define DBG_HI(fmt, args...) do { \
    fprintf(stderr, "D %s:%d, " fmt "\n", __func_name, __LINE__, ##args); \
} while (0)

#define DBG_LO(fmt, args...) do {} while (0)
