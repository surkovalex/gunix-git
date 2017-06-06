#include <Linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/wait.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/time.h>
#include "kd_flashlight.h"
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include "kd_camera_hw.h"

#define USE_UNLOCKED_IOCTL


/******************************************************************************
 * Definition
******************************************************************************/
#ifndef TRUE
#define TRUE	KAL_TRUE
#endif
#ifndef FALSE
#define FALSE	KAL_FALSE
#endif


/* device name and major number */
#define FLASHLIGHT_DEVNAME		"flash_led"		// this is the dev/name


#define DELAY_MS(ms)	{mdelay(ms);}	// unit: ms(10^-3)
#define DELAY_US(us)	{mdelay(us);}	// unit: us(10^-6)
#define DELAY_NS(ns)	{mdelay(ns);}	// unit: ns(10^-9)


/******************************************************************************
 * Debug configuration
******************************************************************************/
#define PFX		"[FLASH_LED]"
#define PK_DBG_NONE(fmt, arg...)	do {} while (0)
#define PK_DBG_FUNC(fmt, arg...)	printk(KERN_INFO PFX "flash_led_test %s: " fmt, __FUNCTION__ , ##arg)

#define PK_WARN(fmt, arg...)		printk(KERN_WARNING PFX "%s: " fmt, __FUNCTION__ , ##arg)
#define PK_NOTICE(fmt, arg...)		printk(KERN_NOTICE PFX "%s: " fmt, __FUNCTION__ , ##arg)
#define PK_INFO(fmt, arg...)		printk(KERN_INFO PFX "%s: " fmt, __FUNCTION__ , ##arg)
#define PK_TRC_FUNC(f)				printk(PFX "<%s>\n", __FUNCTION__);
#define PK_TRC_VERBOSE(fmt, arg...)	printk(PFX fmt, ##arg)

#define DEBUG_FLASH_LED
#ifdef DEBUG_FLASH_LED
	#define PK_DBG PK_DBG_FUNC
	#define PK_TRC PK_DBG_NONE	// PK_TRC_FUNC
	#define PK_VER PK_DBG_NONE	// PK_TRC_VERBOSE
	#define PK_ERR(fmt, arg...)	printk(KERN_ERR PFX "%s: " fmt, __FUNCTION__ , ##arg)
#else
	#define PK_DBG(a, ...)
	#define PK_TRC(a, ...)
	#define PK_VER(a, ...)
	#define PK_ERR(a, ...)
#endif


/*****************************************************************************

*****************************************************************************/
#define FLASH_GPIO_ENABLE	GPIO12	// enble pin 
#define FLASH_GPIO_FLASH	GPIO13	// flash pin
static int flash_led_state = 0;		// flash_led_state
static struct task_struct *flash_thread_id = NULL;

/******************************************************************/
// gpio control 
//******************************************************************/
int FLASH_LED_Enable(void)
{
	mt_set_gpio_out(FLASH_GPIO_ENABLE, GPIO_OUT_ONE);
	mt_set_gpio_out(FLASH_GPIO_FLASH, GPIO_OUT_ZERO);
	PK_DBG("FLASH_LED_Enable line = %d\n", __LINE__);

	return 0;
}


int FLASH_LED_Disable(void)
{
	mt_set_gpio_out(FLASH_GPIO_ENABLE, GPIO_OUT_ZERO);
	mt_set_gpio_out(FLASH_GPIO_FLASH, GPIO_OUT_ZERO);
	PK_DBG("FLASH_LED_Disable line = %d\n", __LINE__);

	return 0;
}


int FLASH_LED_Init(void)
{
	if (mt_set_gpio_mode(FLASH_GPIO_FLASH, GPIO_MODE_00))
		PK_DBG("[flash_led] set gpio mode failed!! \n");
	if (mt_set_gpio_dir(FLASH_GPIO_FLASH, GPIO_DIR_OUT))
		PK_DBG("[flash_led] set gpio dir failed!! \n");
	if (mt_set_gpio_out(FLASH_GPIO_FLASH, GPIO_OUT_ONE))
		PK_DBG("[flash_led] set gpio failed!! \n");
	if (mt_set_gpio_mode(FLASH_GPIO_ENABLE, GPIO_MODE_00))
		PK_DBG("[flash_led] set gpio mode failed!! \n");
	if (mt_set_gpio_dir(FLASH_GPIO_ENABLE, GPIO_DIR_OUT))
		PK_DBG("[flash_led] set gpio dir failed!! \n");
	if (mt_set_gpio_out(FLASH_GPIO_ENABLE, GPIO_OUT_ONE))
		PK_DBG("[flash_led] set gpio failed!! \n");

	PK_DBG("FLASH_LED_Uninit line = %d\n", __LINE__);

    return 0;
}


int FLASH_LED_Uninit(void)
{
	FLASH_LED_Disable();
	PK_DBG("FLASH_LED_Uninit line = %d\n", __LINE__);

    return 0;
}


/***********************************************************************************/
/***********************************************************************************/

/* show the  flash pin and enable pin state
 * example:cat flash_led state
 */
static ssize_t flash_led_state_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	PK_DBG("FLASH_STATUS = %d, \n", flash_led_state);
	return sprintf(buf, "%u\n", flash_led_state);
}


static int flash_thread(void *arg)
{
	while (1) {
		if (kthread_should_stop())
			break;
		FLASH_LED_Enable();
		msleep(10);
		FLASH_LED_Disable();
		msleep(1000);
	}
}


static ssize_t flash_led_state_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int err;

	if (count <= 0) {
		PK_ERR("flash_led_state_store error");
		return 0;
	}
	unsigned int value = 0;
	sscanf(buf, "%d", &value);
	PK_DBG("FLASH_VALUE = %d, \n", value);
	switch (value) {
	case 0:
		FLASH_LED_Disable();
		flash_led_state = 0;
		break;

	case 1:
		FLASH_LED_Enable();
		flash_led_state = 1;
		break;

	case 2:	// creat thread
		flash_thread_id = kthread_create(flash_thread, NULL, "flash_thread");
		if (IS_ERR(flash_thread_id)) {
			PK_ERR("flash_thread create failed");
			err = PTR_ERR(flash_thread_id);
			flash_thread_id = NULL;
			return err;
		}
		wake_up_process(flash_thread_id);
		flash_led_state = 1;
		break;

	case 3:	// stop thread
		if (flash_thread_id ) {
			kthread_stop(flash_thread_id);
			flash_thread_id = NULL;
		}
		flash_led_state = 0;
		break;

	default:
		FLASH_LED_Disable();
		flash_led_state = 0;
	}

	return strnlen(buf, count);
}


/* control the flash_led state
 * example:echo 0 1  > flash_led state
 */
static DEVICE_ATTR(flash_led_state, 0666, flash_led_state_show, flash_led_state_store);


/****************************************************************************************************************/

/****************************************************************************************************************/
#ifdef USE_UNLOCKED_IOCTL
static long flashlight_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
#else
static int flashlight_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
#endif
{
    int i4RetValue = 0;

    PK_DBG("XXflashlight_ioctl cmd,arg= %x, %x +\n",cmd,(unsigned int)arg);
    switch (cmd) {
	case 0:
		mt_set_gpio_out(FLASH_GPIO_ENABLE, GPIO_OUT_ZERO);	// 真正对硬件的操作，把管脚设置为高低电平
		mt_set_gpio_out(FLASH_GPIO_FLASH, GPIO_OUT_ZERO);
		flash_led_state = 0;
		break;

	case 1:
		mt_set_gpio_out(FLASH_GPIO_ENABLE, GPIO_OUT_ONE);
		mt_set_gpio_out(FLASH_GPIO_FLASH, GPIO_OUT_ONE);
		flash_led_state = 1;
		break;

	case 2:
		mt_set_gpio_out(FLASH_GPIO_ENABLE, GPIO_OUT_ZERO);
		mt_set_gpio_out(FLASH_GPIO_FLASH, GPIO_OUT_ONE);
		flash_led_state = 0;
		break;

	case 3:
		if (flash_thread_id) {
			kthread_stop(flash_thread_id);
			flash_thread_id = NULL;
		}
		flash_led_state = 0;
		break;

	default:
		mt_set_gpio_out(FLASH_GPIO_ENABLE, GPIO_OUT_ZERO);
		mt_set_gpio_out(FLASH_GPIO_FLASH, GPIO_OUT_ZERO);
		flash_led_state = 0;
	}

	return i4RetValue;
}


static int flashlight_open(struct inode *inode, struct file *file)
{
	int i4RetValue = 0;
	PK_DBG("[flashlight_open] E\n");
	// FLASH_LED_Init();
	return i4RetValue;
}


static int flashlight_release(struct inode *inode, struct file *file)
{
	PK_DBG("[flashlight_release] E\n");
	FLASH_LED_Disable();

	return 0;
}


/*****************************************************************************/
/* Kernel interface */
static struct file_operations flashlight_fops = {
	.owner			= THIS_MODULE,
#ifdef USE_UNLOCKED_IOCTL
	.unlocked_ioctl	= flashlight_ioctl,
#else
	.ioctl			= flashlight_ioctl,
#endif
	.open			= flashlight_open,
	.release		= flashlight_release,
};


/*****************************************************************************
Driver interface
*****************************************************************************/
static struct class *flashlight_class = NULL;	// 节点类
static struct device *flashlight_device = NULL;	// 节点设备
static dev_t flashlight_devno;	// 设备号
static struct cdev flashlight_cdev;
/****************************************************************************/
#define ALLOC_DEVNO
static int flashlight_probe(struct platform_device *dev)
{
	int ret = 0, err = 0;

	PK_DBG("[flashlight_probe] start\n");
#ifdef ALLOC_DEVNO
	ret = alloc_chrdev_region(&flashlight_devno, 0, 1, FLASHLIGHT_DEVNAME);
	if (ret) {
		PK_ERR("[flashlight_probe] alloc_chrdev_region fail: %d\n", ret);
		goto flashlight_probe_error;
    } else
		PK_DBG("[flashlight_probe] major: %d, minor: %d\n", MAJOR(flashlight_devno), MINOR(flashlight_devno));
	cdev_init(&flashlight_cdev, &flashlight_fops);
	flashlight_cdev.owner = THIS_MODULE;
	err = cdev_add(&flashlight_cdev, flashlight_devno, 1);
	if (err) {
		PK_ERR("[flashlight_probe] cdev_add fail: %d\n", err);
		goto flashlight_probe_error;
    }
	// 上面代码会在 /dev/flash_led 创建一个设备，这个设备是抽象的。
#else
	#define FLASHLIGHT_MAJOR 242
	ret = register_chrdev(FLASHLIGHT_MAJOR, FLASHLIGHT_DEVNAME, &flashlight_fops);
	if (ret != 0) {
		PK_ERR("[flashlight_probe] Unable to register chardev on major=%d (%d)\n", FLASHLIGHT_MAJOR, ret);
		return ret;
    }
	flashlight_devno = MKDEV(FLASHLIGHT_MAJOR, 0);
#endif
	// 下面的代码在 sys/class/flashdev 目录下创建一个文件节点，通过对文件读写操作就会跳转到指定的函数内执行相应的逻辑操作
	// create the class name flashlightdrv
	flashlight_class = class_create(THIS_MODULE, "flashleddrv");
	if (IS_ERR(flashlight_class)) {
		PK_ERR("[flashlight_probe] Unable to create class, err = %d\n", (int)PTR_ERR(flashlight_class));
		goto flashlight_probe_error;
    }
	// create the device name  "flash_led"
	flashlight_device = device_create(flashlight_class, NULL, flashlight_devno, NULL, FLASHLIGHT_DEVNAME);
	if(NULL == flashlight_device){
		PK_ERR("[flashlight_probe] device_create fail\n");
		goto flashlight_probe_error;
    }
	// create the file name  flash_led_state
	if (device_create_file(flashlight_device, &dev_attr_flash_led_state) < 0)
		pr_err("Failed to create device file(%s)!\n", dev_attr_flash_led_state.attr.name);

	// 开始的时候启动代码一次
	// when booting ,flash once .
	FLASH_LED_Init();
	msleep(10);
	mt_set_gpio_out(FLASH_GPIO_ENABLE, GPIO_OUT_ZERO);	// 对应闪光灯的引脚，zero 为低电平
	mt_set_gpio_out(FLASH_GPIO_FLASH, GPIO_OUT_ZERO);
	PK_DBG("[flashlight_probe] Done\n");

	return 0;

flashlight_probe_error:
#ifdef ALLOC_DEVNO
	if (err == 0)
		cdev_del(&flashlight_cdev);
	if (ret == 0)
		unregister_chrdev_region(flashlight_devno, 1);
#else
	if (ret == 0)
		unregister_chrdev(MAJOR(flashlight_devno), FLASHLIGHT_DEVNAME);
#endif
	return -1;
}


static int flashlight_remove(struct platform_device *dev)
{
	PK_DBG("[flashlight_probe] start\n");

#ifdef ALLOC_DEVNO
	cdev_del(&flashlight_cdev);
	unregister_chrdev_region(flashlight_devno, 1);
#else
	unregister_chrdev(MAJOR(flashlight_devno), FLASHLIGHT_DEVNAME);
#endif
	device_destroy(flashlight_class, flashlight_devno);
	class_destroy(flashlight_class);

	PK_DBG("[flashlight_probe] Done\n");

    return 0;
}


static struct platform_driver flashlight_platform_driver =
{
	.probe		= flashlight_probe,		// 加载驱动时调用该方法
    .remove		= flashlight_remove,	// 卸载驱动调用该方法
    .driver		= {
		.name = FLASHLIGHT_DEVNAME,		// 驱动名，和设备名
		.owner  = THIS_MODULE,
    },
};


static struct platform_device flashlight_platform_device = {
	.name = FLASHLIGHT_DEVNAME,	// 设备名称，该名称必须和驱动名称一致。
	.id = 0,
	.dev = {}
};


static int __init flashlight_init(void)
{
	int ret = 0;
	PK_DBG("[flashlight_probe] start\n");
	// 注册一个设备
	ret = platform_device_register (&flashlight_platform_device);
	if (ret) {
		PK_ERR("[flashlight_probe] platform_device_register fail\n");
		return ret;
	}
	// 注册一个驱动， 通过注册可以设备对应一个驱动，由上层调用。
	ret = platform_driver_register(&flashlight_platform_driver);
	if (ret) {
		PK_ERR("[flashlight_probe] platform_driver_register fail\n");
		return ret;
	}

	PK_DBG("[flashlight_probe] done!\n");
    return ret;
}


static void __exit flashlight_exit(void)
{
	PK_DBG("[flashlight_probe] start\n");
	platform_driver_unregister(&flashlight_platform_driver);
	PK_DBG("[flashlight_probe] done!\n");
}


/*****************************************************************************/
module_init(flashlight_init);
module_exit(flashlight_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("name");
MODULE_DESCRIPTION("FLAH_LED CONTROL TEST");
