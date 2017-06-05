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
#include <linux/timer.h>
#include <linux/jiffies.h>


#define GPIO_OUTPUT	1
#define GPIO_INPUT	0

struct blinkbled_gpio {
    const char *name;
    unsigned int pin;
    unsigned int active;
    unsigned int status;
};

struct blinkbled_gpio_dev {
    struct blinkbled_gpio bled_gpio;
    struct timer_list bled_timer;
    unsigned int led_level;
    unsigned int stop_flag;
};

struct blinkbled_gpio_dev *gdev;


static ssize_t show_blinkled(struct class *class, struct class_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", gpio_get_value(gdev->bled_gpio.pin));
}


static ssize_t store_blinkled(struct class *class, struct class_attribute *attr, const char *buf, size_t count)
{
    unsigned int dbg;
    ssize_t r;

    r = sscanf(buf, "%d", &dbg);
    if (dbg)
        gpio_set_value(gdev->bled_gpio.pin, 1);
    else
        gpio_set_value(gdev->bled_gpio.pin, 0);

    return count;
}


static ssize_t show_stopflag(struct class *class, struct class_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", gdev->stop_flag);
}


static ssize_t store_stopflag(struct class *class, struct class_attribute *attr, const char *buf, size_t count)
{
    unsigned int dbg;
    ssize_t r;

    r = sscanf(buf, "%d", &dbg);
    if (dbg)
        gdev->stop_flag = 1;
    else
        gdev->stop_flag = 0;

    return count;
}


static struct class_attribute sdmca_class_attrs[] = {
    __ATTR(blink_led, S_IRUGO | S_IWUGO, show_blinkled, store_blinkled),
    __ATTR(stop_flag, S_IRUGO | S_IWUGO, show_stopflag, store_stopflag),
    __ATTR_NULL
};


static struct class sdmca_class = {
    .name = "sdmca",
    .class_attrs = sdmca_class_attrs,
 };


static const struct of_device_id sdmc_blinkled_dt_match[] = {
    {
        .compatible = "sdmca, blinkled",
    },
    {},
};


static int blinkbled_gpio_dt_parse(struct platform_device *pdev)
{
    struct device_node *node;
    struct gpio_desc *desc;
    enum of_gpio_flags flags;

    node = pdev->dev.of_node;
    if (!node) {
        pr_err("failed to find node for blinkbled_gpio_dt_parse\n");
        return -ENODEV;
    }

    desc = of_get_named_gpiod_flags(node, "blinkled_gpio", 0, &flags);
    gdev->bled_gpio.active = flags & OF_GPIO_ACTIVE_LOW;
    gdev->bled_gpio.pin = desc_to_gpio(desc);
    pr_info("bled_gpio.pin = %d flags = %d\n", gdev->bled_gpio.pin, flags);

    return 0;
}


static void bled_timer_handler(unsigned long data)
{
    unsigned int stop_flag;

    stop_flag = gdev->stop_flag;
    if (!stop_flag) {
        gpio_set_value(gdev->bled_gpio.pin, !(gdev->led_level));
        gdev->led_level = !(gdev->led_level);
        mod_timer(&gdev->bled_timer, jiffies + HZ/4);
    } else
        gpio_set_value(gdev->bled_gpio.pin, 0);
}


static int blinkbled_gpio_dev_init(void)
{
    int nRet = 0;

    nRet = gpio_request(gdev->bled_gpio.pin, NULL);
    if (0 != nRet) {
        pr_err("%s %d gpio_request() failed, errno = %d\n", __func__, __LINE__, nRet);
        return nRet;
    }
    nRet = gpio_direction_output(gdev->bled_gpio.pin, 1);
    if (0 != nRet) {
        pr_err("%s %d gpio_direction_output() failed, errno = %d\n", __func__, __LINE__, nRet);
        return nRet;
    }
    gpio_set_value(gdev->bled_gpio.pin, 0);
    gdev->led_level = 0;
    gdev->stop_flag = 0;

    /* init the timer */
    init_timer(&gdev->bled_timer);
    gdev->bled_timer.function = &bled_timer_handler;
    gdev->bled_timer.expires = jiffies + HZ/4;
    add_timer(&gdev->bled_timer);

    return 0;
}


static int sdmc_blinkled_probe(struct platform_device *pdev)
{
    int nRet = 0;

    gdev = kzalloc(sizeof(struct blinkbled_gpio_dev), GFP_KERNEL);
    if (!gdev) {
        pr_err("kzalloc error\n");
        return -ENOMEM;
    }

    nRet = blinkbled_gpio_dt_parse(pdev);
    if (nRet)
        return nRet;

    nRet = blinkbled_gpio_dev_init();
    if (nRet)
        return nRet;

    nRet = class_register(&sdmca_class);
    if (nRet)
        pr_err("sdmc class register fail nRet = %d!\n", nRet);

    return 0;
}


static int sdmc_blinkled_remove(struct platform_device *pdev)
{
    class_unregister(&sdmca_class);
    gpio_free(gdev->bled_gpio.pin);
    del_timer(&gdev->bled_timer);
    kfree(gdev);
    pr_info("sdmc blinkled module removed ok\n");

    return 0;
}


static struct platform_driver sdmc_blinkled_driver = {
    .probe      = sdmc_blinkled_probe,
    .remove     = sdmc_blinkled_remove,
    .driver     = {
        .owner	= THIS_MODULE,
        .name	= "blinkled",
        .of_match_table = sdmc_blinkled_dt_match,
    },
};


static int __init sdmc_blinkled_init(void)
{
    pr_info("sdmc blinkled module init\n");
    if (platform_driver_register(&sdmc_blinkled_driver)) {
        pr_err("failed to register sdmc blinkled driver\n");
        return -ENODEV;
    }

    return 0;
}


static void __exit sdmc_blinkled_exit(void)
{
    pr_info("sdmc blinkled module exit\n");
    platform_driver_unregister(&sdmc_blinkled_driver);
}


core_initcall_sync(sdmc_blinkled_init);
module_exit(sdmc_blinkled_exit);

MODULE_DESCRIPTION("sdmc blinkled driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jimmy");
MODULE_VERSION("sdmc blinkled driver v1.0.0");

