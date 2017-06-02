#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/reboot.h>
#include <linux/inetdevice.h>
#include <net/if_inet6.h>
#include <linux/slab.h>
#include <linux/gpio.h>

#ifdef CONFIG_HAS_EARLYSUSPEND
#include <linux/earlysuspend.h>
static struct early_suspend early_suspend;
static int early_suspend_flag = 0;
#endif

struct sdmc_gpio_dev {
	const char *name;
	unsigned int pin;
	unsigned int active;
	unsigned int status;
};

struct sdmc_gpio_dev *gdev;

#define NOUSED_GPIO	-1
#define GPIO_OUTPUT	1
#define GPIO_INPUT	0

#define LED_LAN_RCV		0x01
#define LED_LAN_TX		0x02
#define LED_TURNOFF		0x04

static struct workqueue_struct *led_wq;
static void led_work_func(struct work_struct *);
static DECLARE_DELAYED_WORK(led_task, led_work_func);

static unsigned int led_lanrxtx __read_mostly = 1;
static unsigned char lastleds;	/* LED state from most recent update */

/* ptr to LED-specific function */
static void (*led_func_ptr) (unsigned char) __read_mostly;

int sdmc_set_gpio(int num, int level);


/*
 ** led_halt()
 **
 ** called by the reboot notifier chain at shutdown and stops all LED activities.
 **
 */
static int led_halt(struct notifier_block *, unsigned long, void *);

static struct notifier_block led_notifier = {
	.notifier_call = led_halt,
};
static int notifier_disabled = 0;


static int led_halt(struct notifier_block *nb, unsigned long event, void *buf) 
{
	if (notifier_disabled)
		return NOTIFY_OK;

	notifier_disabled = 1;

	/* Cancel the work item and delete the queue */
	if (led_wq) {
		cancel_delayed_work_sync(&led_task);
		destroy_workqueue(led_wq);
		led_wq = NULL;
	}
	if ((gdev->net_led.active) == 0)
		sdmc_set_gpio(gdev->net_led.pin, 0);
	else
		sdmc_set_gpio(gdev->net_led.pin, 1);
	printk("reboot %s, line = %d!\n", __FUNCTION__, __LINE__);
	return NOTIFY_OK;
}


int sdmc_req_gpio(int num, int dir, int level, char *own)
{
	int nRet = NOUSED_GPIO;
	if (NOUSED_GPIO != num) {
		nRet = gpio_request(num, own);
		if (0 != nRet)
		   printk("*****%s %d gpionum: %d errno: 0x%x\n", __FUNCTION__, __LINE__, num, nRet);
		if (dir)	// out put
			nRet = gpio_direction_output(num, level);
		else
			nRet = gpio_direction_input(num);

		if (0 != nRet)
		   printk("*****%s %d gpionum: %d errno: 0x%x\n", __FUNCTION__, __LINE__, num, nRet);
	}

	return nRet;
}
EXPORT_SYMBOL(sdmc_req_gpio);


int sdmc_set_dir_gpio(int num, int dir, int level)
{
	int nRet = NOUSED_GPIO;
	if (NOUSED_GPIO != num) {
		if (dir)
			nRet = gpio_direction_output(num, level);
		else
			nRet = gpio_direction_input(num);
		if (0 != nRet)
		   printk("*****%s %d gpionum: %d errno: 0x%x\n", __FUNCTION__, __LINE__, num, nRet);
	}

	return nRet;
}
EXPORT_SYMBOL(sdmc_set_dir_gpio);


int sdmc_set_gpio(int num, int level)
{
	int nRet = NOUSED_GPIO;
	if (NOUSED_GPIO != num) {
		gpio_set_value(num, level);
		return 0;
	}

	return nRet;
}
EXPORT_SYMBOL(sdmc_set_gpio);


int sdmc_get_gpio(int num)
{
	int nRet = NOUSED_GPIO;
	if (NOUSED_GPIO != num)
		return gpio_get_value(num);

	return nRet;
}
EXPORT_SYMBOL(sdmc_get_gpio);


int sdmc_free_gpio(int num)
{
	int nRet = NOUSED_GPIO;
	if (NOUSED_GPIO != num) {
		gpio_free(num);
		return 0;
	}

	return nRet;
}
EXPORT_SYMBOL(sdmc_free_gpio);


static void sdmc_gpio_init(void)
{
    int nRet = 0;

	if (NOUSED_GPIO != gdev->sys_led.pin) {
		nRet = sdmc_req_gpio(gdev->sys_led.pin, GPIO_OUTPUT, 1, NULL);
		if (0 != nRet)
			printk("%s Failed, line = %d!\n", __FUNCTION__, __LINE__);
	}

	if (NOUSED_GPIO !=gdev->sdmc_led_blink.pin) {
		nRet = sdmc_req_gpio(gdev->sdmc_led_blink.pin, GPIO_OUTPUT, 0, NULL);
		if (0 != nRet)
			printk("%s Failed, line = %d!\n", __FUNCTION__, __LINE__);
	}
}


/*
 ** register_led_driver()
 **
 ** registers an external LED or for usage by this driver.
 **
 */
int register_led_driver(int model, unsigned long cmd_reg, unsigned long data_reg)
{
	static int initialized;
	int nRet = 0;

	if (initialized)
		return 1;
	led_func_ptr = led_net_driver;

	/* mark the LED driver now as initialized and 
	 * register to the reboot notifier chain */
	initialized++;
	register_reboot_notifier(&led_notifier);

	/* Ensure the work is queued */
	if (led_wq) {
		printk("turn off: net led\n");
		nRet = sdmc_req_gpio(gdev->net_led.pin, 1, 1, "NET_LED");
		queue_delayed_work(led_wq, &led_task, 0);
		if(0 != nRet) {
			printk("%s Failed, line = %d!\n", __FUNCTION__, __LINE__);
			if (led_wq) {
				cancel_delayed_work_sync(&led_task);
				unregister_reboot_notifier(&led_notifier);
				led_func_ptr = NULL;
				destroy_workqueue(led_wq);
				led_wq = NULL;
			}
		}
	}

	sdmc_gpio_init();

	return 0;
}


/*
 ** led_work_func()
 **
 ** manages when and which chassis LED gets updated
 TODO:
	- display load average (older machines like 715/64 have 4 "free" LED's for that)
	- optimizations
 */
#define LED_UPDATE_INTERVAL	(1 + (HZ*19/1000))
static void led_work_func(struct work_struct *unused)
{
	unsigned char currentleds = 0;	/* stores current value of the LEDs */
	/* exit if not initialized */
	if (!led_func_ptr)
	    return;

	if (likely(led_lanrxtx))
		currentleds |= led_get_net_activity();

	if (currentleds != lastleds || (currentleds&LED_TURNOFF)) {
		led_func_ptr(currentleds);	/* Update the LEDs */
		lastleds = currentleds;
	}

	queue_delayed_work(led_wq, &led_task, LED_UPDATE_INTERVAL);
}


#ifdef CONFIG_HAS_EARLYSUSPEND
static void sdmc_system_early_suspend(struct early_suspend *h)
{
	if (!early_suspend_flag) {
		early_suspend_flag = 1;
		sdmc_set_gpio(gdev->sys_led.pin, 0);
		printk(KERN_INFO "%s\n", __func__);
	}
}


static void sdmc_system_late_resume(struct early_suspend *h)
{
	if (early_suspend_flag) {
		early_suspend_flag = 0;
		sdmc_set_gpio(gdev->sys_led.pin, 1);
		printk(KERN_INFO "%s\n", __func__);
	}
}
#endif


static int sdmc_led_blink_suspend(struct platform_device *dev, pm_message_t state)
{
	int nRet =0;
	printk("\n***** turn off leds\n");

	if ((gdev->net_led.active) == 0)
		sdmc_set_gpio(gdev->net_led.pin, 0);
	else
		sdmc_set_gpio(gdev->net_led.pin, 1);

	if ((gdev->sys_led.active) == 0)
		sdmc_set_gpio(gdev->sys_led.pin, 0);
	else
		sdmc_set_gpio(gdev->sys_led.pin, 1);
	sdmc_set_gpio(DTV_PWR_GPIO, 1);

	return nRet;
}


static int sdmc_led_blink_resume(struct platform_device *dev)
{
	int nRet =0;

	printk("\n***** turn on leds\n");
	sdmc_set_gpio(DTV_PWR_GPIO, 0);
	/* nRet = queue_delayed_work(led_wq, &led_task, LED_UPDATE_INTERVAL); */
	if (0 != nRet)
	    printk("%s Failed, line = %d!\n", __FUNCTION__, __LINE__);

	return nRet;
}


static ssize_t show_sys_led(struct class *class, struct class_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", sdmc_get_gpio(gdev->sys_led.pin));
}


static ssize_t store_sys_led(struct class *class, struct class_attribute *attr, const char *buf, size_t count)
{
	unsigned int dbg;
	ssize_t r;

	r = sscanf(buf, "%d", &dbg);
	if (r != 1)
		return -EINVAL;
    if (1 == dbg)
		sdmc_set_gpio(gdev->sys_led.pin, 1);
	else
		sdmc_set_gpio(gdev->sys_led.pin, 0);

	return count;
}


static ssize_t show_s2_antpwr(struct class *class, struct class_attribute *attr, char *buf)
{
	if (NOUSED_GPIO != gdev->sdmc_led_blink.pin)
		return sprintf(buf, "%d\n", sdmc_get_gpio(gdev->sdmc_led_blink.pin));
	else
		return sprintf(buf, "this gpio isn't used\n");
}


static ssize_t store_s2_antpwr(struct class *class, struct class_attribute *attr, const char *buf, size_t count)
{
	unsigned int dbg;
	ssize_t r;

	r = sscanf(buf, "%d", &dbg);
	if (r != 1 || NOUSED_GPIO == gdev->sdmc_led_blink.pin) {
		printk("invalid value, please input again\n");
		return -EINVAL;
	}
    if (1 == dbg)
		sdmc_set_gpio(gdev->sdmc_led_blink.pin, 1);
	else
		sdmc_set_gpio(gdev->sdmc_led_blink.pin, 0);

	return count;
}


static struct class_attribute sdmc_class_attrs[] = {
	__ATTR(sys_led, S_IRUGO | S_IWUGO, show_sys_led, store_sys_led),
	__ATTR(s2_antpwr, S_IRUGO | S_IWUGO, show_s2_antpwr, store_s2_antpwr),
    __ATTR_NULL
};


static struct class sdmc_class = {
	.name = "sdmc",
	.class_attrs = sdmc_class_attrs,
 };


static const struct of_device_id sdmc_led_blink_dt_match[] = {
	{
		.compatible = "sdmc, gpioctrl",
	},
	{},
};


static int sdmc_gpio_dt_parse(struct platform_device *pdev)
{
	struct device_node *node;
	struct gpio_desc *desc;
	enum of_gpio_flags flags;

	node = pdev->dev.of_node;
	if (!node) {
		pr_err("failed to find node for sdmc_gpio_dt_parse\n");
		return -ENODEV;
	}

	desc = of_get_named_gpiod_flags(node, "s2_tuner_lnb", 0, &flags);
	gdev->active = flags & OF_GPIO_ACTIVE_LOW;
	if (gdev->active == 1)
		gdev->sdmc_led_blink.pin = -1;
	else
		gdev->pin = desc_to_gpio(desc);
	printk("###$$$ sdmc_led_blink.pin = %d flags = %d\n", gdev->pin, flags);

	return 0;
}


static int sdmc_led_blink_probe(struct platform_device *pdev)
{
	int nRet = 0;

	gdev = kzalloc(sizeof(struct sdmc_gpio_dev), GFP_KERNEL);
	if (!gdev) {
		pr_err("kzalloc error\n");
		return -ENOMEM;
	}

	nRet = sdmc_gpio_dt_parse(pdev);
	if (nRet)
		return nRet;

#ifdef CONFIG_HAS_EARLYSUSPEND
	early_suspend.level = EARLY_SUSPEND_LEVEL_DISABLE_FB;
	early_suspend.suspend = sdmc_system_early_suspend;
	early_suspend.resume = sdmc_system_late_resume;
	register_early_suspend(&early_suspend);
#endif

	nRet = class_register(&sdmc_class);
	if (nRet)
        printk(" sdmc class register fail nRet = %d!\n", nRet);
	/* Create the work queue and queue the LED task */
	led_wq = create_singlethread_workqueue("led_wq");
	nRet |= queue_delayed_work(led_wq, &led_task, 0);
	if (1 != nRet)
	    printk("%s Failed!\n", __FUNCTION__);

	return register_led_driver(0, 0, 0);
}


static int sdmc_led_blink_remove(struct platform_device *pdev)
{
	int nRet = 0;

	nRet = unregister_reboot_notifier(&led_notifier);
	if (0 != nRet)
	    printk("%s Failed, line = %d!\n", __FUNCTION__, __LINE__);
	sdmc_free_gpio(gdev->sdmc_led_blink.pin);

	/* Cancel the work item and delete the queue */
	if (led_wq) {
		cancel_delayed_work_sync(&led_task);
		destroy_workqueue(led_wq);
		led_wq = NULL;
	}
	class_unregister(&sdmc_class);
#ifdef CONFIG_HAS_EARLYSUSPEND
	unregister_early_suspend(&early_suspend);
#endif
	kfree(gdev);
	printk("gpioctrl module removed ok\n");
    return 0;
}


static struct platform_driver sdmc_led_blink_driver = {
	.probe		= sdmc_led_blink_probe,
	.remove		= sdmc_led_blink_remove,
	.suspend	= sdmc_led_blink_suspend,
	.resume		= sdmc_led_blink_resume,
	.driver		= {
		.owner	= THIS_MODULE,
		.name	= "gpioctrl",
		.of_match_table = sdmc_led_blink_dt_match,
	},
};


static int __init sdmc_led_blink_init(void)
{
	pr_info("sdmc led blink module init\n");
	if (platform_driver_register(&sdmc_led_blink_driver)) {
		pr_err("failed to register sdmc led blink driver\n");
		return -ENODEV;
	}

	return 0;
}


static void __exit sdmc_led_blink_exit(void)
{
	pr_info("sdmc led blink module exit\n");
	platform_driver_unregister(&sdmc_led_blink_driver);
}


core_initcall_sync(sdmc_led_blink_init);
module_exit(sdmc_led_blink_exit);

MODULE_DESCRIPTION("sdmc led blink driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jimmy");
MODULE_VERSION("sdmc led blink v1.0.0");
