#ifndef __HELLO_LOG_H__
#define __HELLO_LOG_H__

#define H_INFO(fmt, args...) do { \
	pr_info("I %s:%d, " fmt "\n", __func__, __LINE__, ##args); \
} while (0)

#define H_ERR(fmt, args...) do { \
	pr_info("E %s:%d, " fmt "\n", __func__, __LINE__, ##args); \
} while (0)
#endif
