#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/uio_driver.h>
#include <linux/slab.h>

#include "hello_log.h"

#define DRIVER_NAME "hello"

#define HELLO_MEMSIZE 32

struct uio_info hello_uinfo = {
	.name = DRIVER_NAME,
	.version = "0.0",
	.irq = UIO_IRQ_CUSTOM,
};

struct hello_device
{
	struct platform_device *pdev;
	struct uio_info *uinfo;
};

struct hello_device hdev;

static int hello_probe(struct platform_device *pdev)
{
	int rc = 0;
	H_INFO("");
	hdev.pdev = pdev;
	hdev.uinfo = &hello_uinfo;
	hdev.uinfo->mem[0].addr = (unsigned long) kmalloc(HELLO_MEMSIZE,
							    GFP_KERNEL);
	if (!hdev.uinfo->mem[0].addr) {
		H_ERR("kmalloc failed");
		rc = -ENOMEM;
		goto ret;
	}
	hdev.uinfo->mem[0].memtype = UIO_MEM_LOGICAL;
	hdev.uinfo->mem[0].size = HELLO_MEMSIZE;

	if (uio_register_device(&pdev->dev, hdev.uinfo)) {
		H_ERR("uio_register_device failed");
		rc = -ENODEV;
		goto free_mem;
	}
	return 0;

free_mem:
	kfree((void*)hdev.uinfo->mem[0].addr);
ret:
	return rc;
}

static int hello_remove(struct platform_device *pdev)
{
	H_INFO("");
	uio_unregister_device(hdev.uinfo);
	kfree((void*)hdev.uinfo->mem[0].addr);
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
