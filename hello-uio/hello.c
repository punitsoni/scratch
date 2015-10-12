#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/uio_driver.h>
#include <linux/slab.h>
#include <linux/timer.h>

#include "hello_log.h"

#define DRIVER_NAME "hello"

#define HELLO_MEMSIZE 4096
#define HELLO_FREQ_HZ 1

struct uio_info hello_uinfo = {
	.name = DRIVER_NAME,
	.version = "0.0",
	.irq = UIO_IRQ_CUSTOM,
	.priv = NULL,
};

struct hello_device
{
	struct platform_device *pdev;
	struct uio_info *uinfo;
	struct timer_list timer;
	u32 freq;
	u32 count;
};

struct hello_device hdev;

static void hello_timer_func(unsigned long data)
{
	u32 *addr;
	struct hello_device *hdev = (struct hello_device *)data;
	addr = (u32 *) hdev->uinfo->mem[0].addr;
	*addr = hdev->count++;
	H_INFO("notify count = %d", hdev->count);
	/* notify event to user space */
	uio_event_notify(hdev->uinfo);
	mod_timer(&hdev->timer, jiffies + msecs_to_jiffies(1000 / hdev->freq));
}

static int hello_start(struct hello_device *hdev)
{
	H_INFO("");
	hdev->count = 0;
	hdev->freq = HELLO_FREQ_HZ;
	init_timer(&hdev->timer);
	hdev->timer.data = (unsigned long) hdev;
	hdev->timer.function = hello_timer_func;
	mod_timer(&hdev->timer, jiffies + msecs_to_jiffies(1000 / hdev->freq));
	return 0;
}

static int hello_stop(struct hello_device *hdev)
{
	H_INFO("");
	del_timer(&hdev->timer);
	return 0;
}

static int hello_open(struct uio_info *uinfo, struct inode *inode)
{
	int rc = 0;
	struct hello_device *hdev;
	H_INFO("");
	hdev = (struct hello_device *) uinfo->priv;
	rc = hello_start(hdev);
	if (rc) {
		H_ERR("failed");
		goto ret;
	}
	return 0;
ret:
	return rc;
}

static int hello_release(struct uio_info *uinfo, struct inode *inode)
{
	struct hello_device *hdev;
	H_INFO("");
	hdev = (struct hello_device *) uinfo->priv;
	hello_stop(hdev);
	return 0;
}

static int hello_probe(struct platform_device *pdev)
{
	int rc = 0;
	H_INFO("");
	hdev.pdev = pdev;
	hdev.uinfo = &hello_uinfo;
	hdev.uinfo->mem[0].addr = (unsigned long) kzalloc(HELLO_MEMSIZE,
							    GFP_KERNEL);
	if (!hdev.uinfo->mem[0].addr) {
		H_ERR("kmalloc failed");
		rc = -ENOMEM;
		goto ret;
	}

	hdev.uinfo->mem[0].memtype = UIO_MEM_LOGICAL;
	hdev.uinfo->mem[0].size = HELLO_MEMSIZE;
	hdev.uinfo->priv = (void *)&hdev;
	hdev.uinfo->open = hello_open;
	hdev.uinfo->release = hello_release;

	if (uio_register_device(&pdev->dev, hdev.uinfo)) {
		H_ERR("uio_register_device failed");
		rc = -ENODEV;
		goto free_mem;
	}

	platform_set_drvdata(pdev, &hdev);
	return 0;

free_mem:
	kfree((void*)hdev.uinfo->mem[0].addr);
ret:
	return rc;
}

static int hello_remove(struct platform_device *pdev)
{
	struct hello_device *hdev;
	H_INFO("");
	hdev = (struct hello_device *) platform_get_drvdata(pdev);
	uio_unregister_device(hdev->uinfo);
	kfree((void*)hdev->uinfo->mem[0].addr);
	return 0;
}

static struct platform_driver hello_driver = {
	.driver		= {
		.name	= DRIVER_NAME,
		.owner	= THIS_MODULE,
	},
	.probe		= hello_probe,
	.remove		= hello_remove,
};

int hello_init_module(void)
{
	int rc;
	H_INFO("");
	hdev.pdev = platform_device_register_simple(DRIVER_NAME, -1,
												NULL, 0);
	if (IS_ERR(hdev.pdev)) {
		H_ERR("platform_device_register_simple failed");
		rc = -EINVAL;
		goto ret;
	}

	rc = platform_driver_register(&hello_driver);
	if (rc) {
		H_ERR("failed");
		goto ret;
	}	
	return 0;
ret:
   	return rc;
}

void hello_exit_module(void)
{
	H_INFO("");
	platform_device_unregister(hdev.pdev);
	platform_driver_unregister(&hello_driver);
}  

module_init(hello_init_module);
module_exit(hello_exit_module);
MODULE_LICENSE("GPL");
