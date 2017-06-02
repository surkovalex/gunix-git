#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/leds.h>
#include <linux/gpio.h>
#include <linux/printk.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/delay.h>
//#include <linux/reboot.h>
//#include <linux/inetdevice.h>
//#include <net/if_inet6.h>

#define SDMCLED_NAME		"sdmcled"

struct sdmcled_gpio {
	const char *name;
	unsigned int pin;
	unsigned int active_low;
	unsigned int state;
};

struct sdmcled_dev {
	struct sdmcled_gpio d;
	struct led_classdev cdev;
	enum led_brightness new_brightness;

	struct work_struct work;
	struct mutex lock;
};


static const struct of_device_id sdmcled_dt_match[] = {
	{
		.compatible = "sdmc, sdmcled",
	},
	{},
};


static int sdmcled_dt_parse(struct platform_device *pdev)
{
	struct device_node *node;
	struct sdmcled_dev *ldev;
	struct gpio_desc *desc;
	enum of_gpio_flags flags;

	ldev = platform_get_drvdata(pdev);
	node = pdev->dev.of_node;
	if (!node) {
		pr_err("failed to find node for %s\n", SDMCLED_NAME);
		return -ENODEV;
	}

	desc = of_get_named_gpiod_flags(node, "sdmcledw_gpio", 0, &flags);
	ldev->d.pin = desc_to_gpio(desc);
	ldev->d.active_low = flags & OF_GPIO_ACTIVE_LOW;
	pr_info("sdmcledw_gpio = %u\n", ldev->d.pin);
	pr_info("active_low = %u\n", ldev->d.active_low);
	gpio_request(ldev->d.pin, SDMCLED_NAME);
	gpio_direction_output(ldev->d.pin, 1);

	return 0;
}


static void sdmcled_brightness_set(struct led_classdev *cdev, enum led_brightness value)
{
	struct sdmcled_dev *ldev;
	struct platform_device *pdev;

	pdev = to_platform_device(cdev->dev->parent);
	ldev = platform_get_drvdata(pdev);
	ldev->new_brightness = value;
	schedule_work(&ldev->work);
}


static void sdmcled_output_setup(struct sdmcled_dev *ldev, enum led_brightness value)
{
	unsigned int level = !!value;
#if 0
	if (ldev->d.active_low)
		level = !level;
#endif
	gpio_direction_output(ldev->d.pin, level);
}


static void sdmcled_work(struct work_struct *work)
{
	struct sdmcled_dev *ldev;

	ldev = container_of(work, struct sdmcled_dev, work);

	mutex_lock(&ldev->lock);
	sdmcled_output_setup(ldev, ldev->new_brightness);
	mutex_unlock(&ldev->lock);
}


static int sdmcled_probe(struct platform_device *pdev)
{
	struct sdmcled_dev *ldev;
	int ret;
	// int i;

	ldev = kzalloc(sizeof(struct sdmcled_dev), GFP_KERNEL);
	if (!ldev) {
		pr_err("kzalloc error\n");
		return -ENOMEM;
	}

	/* set driver data */
	platform_set_drvdata(pdev, ldev);

	/* parse dt param */
	ret = sdmcled_dt_parse(pdev);
	if (ret)
		return ret;

	/* register led class device */
	ldev->cdev.name = SDMCLED_NAME;
	ldev->cdev.brightness_set = sdmcled_brightness_set;
	mutex_init(&ldev->lock);
	INIT_WORK(&ldev->work, sdmcled_work);
	ret = led_classdev_register(&pdev->dev, &ldev->cdev);
	if (ret < 0) {
		kfree(ldev);
		return ret;
	}

	/* set led default on */
	/*for (i=0; i<60; i++) { */
		sdmcled_output_setup(ldev, 1);
		msleep(5000);
		sdmcled_output_setup(ldev, 0);
		msleep(5000);
	/*}*/
#if 0
	if (i == 50) {
		sdmcled_output_setup(ldev, 1);
	}
#endif

	pr_info("module probed ok\n");
	return 0;
}


static int __exit sdmcled_remove(struct platform_device *pdev)
{
	struct sdmcled_dev *ldev = platform_get_drvdata(pdev);

	led_classdev_unregister(&ldev->cdev);
	cancel_work_sync(&ldev->work);
	gpio_free(ldev->d.pin);
	platform_set_drvdata(pdev, NULL);
	kfree(ldev);

	pr_info("module removed ok\n");
	return 0;
}


static struct platform_driver sdmcled_driver = {
	.driver = {
		.name = SDMCLED_NAME,
		.owner = THIS_MODULE,
		.of_match_table = sdmcled_dt_match,
	},
	.probe = sdmcled_probe,
	.remove = __exit_p(sdmcled_remove),
};


static int __init sdmcled_init(void)
{
	pr_info("module init\n");
	if (platform_driver_register(&sdmcled_driver)) {
		pr_err("failed to register driver\n");
		return -ENODEV;
	}

	return 0;
}


static void __exit sdmcled_exit(void)
{
	pr_info("module exit\n");
	platform_driver_unregister(&sdmcled_driver);
}


module_init(sdmcled_init);
module_exit(sdmcled_exit);

MODULE_DESCRIPTION("SDMC leds driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jimmy<Jimmy_guo@sdmctech.com>");
MODULE_VERSION("sdmc led v1.0.0");

