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

struct sdmc_gpio_dev{
	int	 pin;
	char name[16];
	char status;
	int active;
};

struct sdmc_gpio_devs{
	struct sdmc_gpio_dev sys_led;
	struct sdmc_gpio_dev net_led;
	struct sdmc_gpio_dev demo_res;
	struct sdmc_gpio_dev ant_pwr;
	struct sdmc_gpio_dev s2_ant_pwr;
	struct sdmc_gpio_dev tuner_lock_status;
	struct sdmc_gpio_dev tuner_loop_out;
	struct sdmc_gpio_dev tuner_ch3_ch4;
};

struct sdmc_gpio_devs *gdev;

#define NOUSED_GPIO		-1
#define  GPIO_OUTPUT 1
#define  GPIO_INPUT  0

#define DTV_PWR_GPIO NOUSED_GPIO 
#define IR_GPIO			NOUSED_GPIO

#define LED_LAN_RCV 0x01
#define LED_LAN_TX 0x02
#define LED_TURNOFF 0x04

#ifdef CONFIG_HAS_EARLYSUSPEND
#include <linux/earlysuspend.h>
static struct early_suspend early_suspend;
static int early_suspend_flag = 0;
#endif

int t_wifi = 0;
EXPORT_SYMBOL(t_wifi);

static struct workqueue_struct *led_wq;
static void led_work_func(struct work_struct *);
static DECLARE_DELAYED_WORK(led_task, led_work_func);

static unsigned int led_lanrxtx   __read_mostly = 1;
//static unsigned int led_heartbeat __read_mostly = 1;
static unsigned char lastleds;	/* LED state from most recent update */

/* ptr to LED-specific function */
static void (*led_func_ptr) (unsigned char) __read_mostly;

int sdmc_set_gpio(int num,int level);
/*
   ** led_halt()
   ** 
   ** called by the reboot notifier chain at shutdown and stops all
   ** LED activities.
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
	if((gdev->net_led.active) == 0)
		sdmc_set_gpio(gdev->net_led.pin,0);
	else
		sdmc_set_gpio(gdev->net_led.pin,1);
	printk("reboot %s ,line = %d!\n",__FUNCTION__,__LINE__);
	return NOTIFY_OK;
}

int sdmc_req_gpio(int num,int dir,int level,char *own)
{
	int nRet = NOUSED_GPIO;
	if(NOUSED_GPIO != num)
	{
		nRet = gpio_request(num,own);
		if(0 != nRet)
		   printk("@@@@@%s %d gpionum:%d errno:0x%x\n",__FUNCTION__,__LINE__,num,nRet);
		if(dir) //out put
		{
			nRet = gpio_direction_output(num,level);
		}
		else
		{
			nRet = gpio_direction_input(num);
		}
		
		if(0 != nRet)
		   printk("@@@@@%s %d gpionum:%d errno:0x%x\n",__FUNCTION__,__LINE__,num,nRet);
	}

	return nRet;
}
EXPORT_SYMBOL(sdmc_req_gpio);

int sdmc_set_dir_gpio(int num,int dir,int level)
{
	int nRet = NOUSED_GPIO;
	if(NOUSED_GPIO != num)
	{
		if(dir)
			nRet = gpio_direction_output(num,level);
		else
			nRet = gpio_direction_input(num);
		if(0 != nRet)
		   printk("@@@@@%s %d gpionum:%d errno:0x%x\n",__FUNCTION__,__LINE__,num,nRet);
	}

	return nRet;
}
EXPORT_SYMBOL(sdmc_set_dir_gpio);

int sdmc_set_gpio(int num,int level)
{
	int nRet = NOUSED_GPIO;
	if(NOUSED_GPIO != num)
	{
		//gpio_set_value(num,level);
		return gpio_direction_output(num,level);
	}

	return nRet;
}
EXPORT_SYMBOL(sdmc_set_gpio);

int sdmc_get_gpio(int num)
{
	int nRet = NOUSED_GPIO;
	if(NOUSED_GPIO != num)
	{
		return gpio_get_value(num);
	}
	
	return nRet;
}
EXPORT_SYMBOL(sdmc_get_gpio);

int sdmc_free_gpio(int num)
{
	int nRet = NOUSED_GPIO;
	if(NOUSED_GPIO != num)
	{
		gpio_free(num);
		return 0;
	}
	
	return nRet;
}
EXPORT_SYMBOL(sdmc_free_gpio);

static void sdmc_gpio_init(void)
{
    int nRet = 0;
       
       if (NOUSED_GPIO != gdev->net_led.pin) 
       {
            nRet = sdmc_req_gpio(gdev->net_led.pin,GPIO_OUTPUT,1,NULL);
            if(0 != nRet)
            {
                printk("%s Failed,line = %d!\n",__FUNCTION__,__LINE__);
            }
       }
       if(NOUSED_GPIO != gdev->sys_led.pin)
       {
            nRet = sdmc_req_gpio(gdev->sys_led.pin,GPIO_OUTPUT,1,NULL);
            if(0 != nRet)
            {
                printk("%s Failed,line = %d!\n",__FUNCTION__,__LINE__);
            }
       }

       if(NOUSED_GPIO != DTV_PWR_GPIO)
       {
            nRet = sdmc_req_gpio(DTV_PWR_GPIO,GPIO_OUTPUT,0,NULL);
            if(0 != nRet)
            {
                printk("%s Failed,line = %d!\n",__FUNCTION__,__LINE__);
            }
       }
       if(NOUSED_GPIO !=gdev->ant_pwr.pin)
       {
            nRet = sdmc_req_gpio(gdev->ant_pwr.pin,GPIO_OUTPUT,0,NULL);
            if(0 != nRet)
            {
                printk("%s Failed,line = %d!\n",__FUNCTION__,__LINE__);
            }
       }

       if(NOUSED_GPIO !=gdev->s2_ant_pwr.pin)
       {
            nRet = sdmc_req_gpio(gdev->s2_ant_pwr.pin,GPIO_OUTPUT,0,NULL);
            if(0 != nRet)
            {
               printk("%s Failed,line = %d!\n",__FUNCTION__,__LINE__);
            }
       }
       
       if(NOUSED_GPIO !=gdev->demo_res.pin)
       {
            nRet = sdmc_req_gpio(gdev->demo_res.pin,GPIO_OUTPUT,1,NULL);
            if(0 != nRet)
            {
                printk("%s Failed,line = %d!\n",__FUNCTION__,__LINE__);
            }
       }

       if(NOUSED_GPIO !=IR_GPIO)
       {
            nRet = sdmc_req_gpio(IR_GPIO,GPIO_OUTPUT,0,NULL);
            if(0 != nRet)
            {
                printk("%s Failed,line = %d!\n",__FUNCTION__,__LINE__);
            }
       }
	   
	   if(NOUSED_GPIO != gdev->tuner_lock_status.pin)
       {
            nRet = sdmc_req_gpio(gdev->tuner_lock_status.pin,GPIO_OUTPUT,1,NULL);
            if(0 != nRet)
            {
                printk("%s Failed,line = %d!\n",__FUNCTION__,__LINE__);
            }
       }

       if(NOUSED_GPIO != gdev->tuner_loop_out.pin)
       {
            //nRet = sdmc_req_gpio(gdev->tuner_loop_out.pin,GPIO_OUTPUT,1,NULL);
            if(0 != nRet)
            {
                printk("%s Failed,line = %d!\n",__FUNCTION__,__LINE__);
            }
       }

       if(NOUSED_GPIO != gdev->tuner_ch3_ch4.pin)
       {
            //nRet = sdmc_req_gpio(gdev->tuner_ch3_ch4.pin,GPIO_OUTPUT,0,NULL);
            if(0 != nRet)
            {
                printk("%s Failed,line = %d!\n",__FUNCTION__,__LINE__);
            }
       }
}

/*
   ** 
   ** led_net_driver()
   **   
 */
static void led_net_driver(unsigned char leds)
{
	unsigned int msec_cmd_delay = 20;

	if((leds & LED_LAN_TX) && (leds & LED_LAN_RCV))
	{	
		if((gdev->net_led.active) == 0)
			sdmc_set_gpio(gdev->net_led.pin,0);
		else
			sdmc_set_gpio(gdev->net_led.pin,1);
		msleep(msec_cmd_delay);
		if((gdev->net_led.active) == 0)
			sdmc_set_gpio(gdev->net_led.pin,1);
		else
			sdmc_set_gpio(gdev->net_led.pin,0);
		msleep(msec_cmd_delay);
	}

	if(leds & LED_TURNOFF)
	{
		if((gdev->net_led.active) == 0)
			sdmc_set_gpio(gdev->net_led.pin,1);
		else
			sdmc_set_gpio(gdev->net_led.pin,0);
		msleep(50);
		if((gdev->net_led.active) == 0)
			sdmc_set_gpio(gdev->net_led.pin,0);
		else
			sdmc_set_gpio(gdev->net_led.pin,1);
		msleep(3000);
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
		nRet = sdmc_req_gpio(gdev->net_led.pin,1,1,"NET_LED");
		queue_delayed_work(led_wq, &led_task, 0);
		if(0 != nRet)
		{
			printk("%s Failed,line = %d!\n",__FUNCTION__,__LINE__);
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
   ** 
   ** led_get_net_activity()
   ** 
   ** calculate if there was TX- or RX-throughput on the network interfaces
   ** (analog to dev_get_info() from net/core/dev.c)
   **   
 */
static __inline__ int led_get_net_activity(void)
{ 
#ifndef CONFIG_NET
	return 0;
#else

	static u64 rx_total_last, tx_total_last;
	u64 rx_total, tx_total;
	struct net_device *dev = NULL;
	int retval=0;
	struct inet6_dev *idev=NULL;
	int hasNetDev = 0;

	rx_total = tx_total = 0;

	/* we are running as a workqueue task, so we can use an RCU lookup */
	rcu_read_lock();
	for_each_netdev_rcu(&init_net, dev) {
	    const struct rtnl_link_stats64 *stats;
	    struct rtnl_link_stats64 temp;
	    struct in_device *in_dev = __in_dev_get_rcu(dev);

	    hasNetDev = 0;
	    if (!in_dev || !in_dev->ifa_list)
		continue;
	    if (ipv4_is_loopback(in_dev->ifa_list->ifa_local))
		continue;
	    stats = dev_get_stats(dev, &temp);
	    rx_total += stats->rx_packets;
	    tx_total += stats->tx_packets;
	    hasNetDev = 1;
		break;
	}

	rcu_read_unlock();

	if( dev && hasNetDev)
		idev = rcu_dereference_rtnl(dev->ip6_ptr);
	else
	{
		retval |= LED_TURNOFF;
		return retval;
	}

	if ( idev ) {
		if (idev->if_flags & IF_READY)/* device is already configured. */
		{
			if (rx_total != rx_total_last) {
				rx_total_last = rx_total;
				retval |= LED_LAN_RCV;
			}

			if (tx_total != tx_total_last) {
				tx_total_last = tx_total;
				retval |= LED_LAN_TX;
			}

			return retval;
		}
		else
		{
			retval |= LED_TURNOFF;
		}
	}
	else
	{
		retval |= LED_TURNOFF;
	}

	return retval;
#endif
}

/*
   ** led_work_func()
   ** 
   ** manages when and which chassis LED gets updated

    TODO:
    - display load average (older machines like 715/64 have 4 "free" LED's for that)
    - optimizations
 */
#define LED_UPDATE_INTERVAL (1 + (HZ*19/1000))
static void led_work_func (struct work_struct *unused)
{
	unsigned char currentleds = 0; /* stores current value of the LEDs */
	/* exit if not initialized */
	if (!led_func_ptr)
	    return;
	
	if (likely(led_lanrxtx))
	{	
		currentleds |= led_get_net_activity();
	}
	
	if (currentleds != lastleds || (currentleds&LED_TURNOFF))
	{
		led_func_ptr(currentleds);	/* Update the LEDs */
		lastleds = currentleds;
	}

	queue_delayed_work(led_wq, &led_task, LED_UPDATE_INTERVAL);
}

static void sdmc_leds_dev_release(struct device *dev)
{}

#ifdef CONFIG_HAS_EARLYSUSPEND
static void sdmc_system_early_suspend(struct early_suspend *h)
{
	if (!early_suspend_flag) {
		early_suspend_flag = 1;
		sdmc_set_gpio(gdev->sys_led.pin,0);
		printk(KERN_INFO "%s\n",__func__);
	}
}

static void sdmc_system_late_resume(struct early_suspend *h)
{
	if (early_suspend_flag) {
		early_suspend_flag = 0;
		sdmc_set_gpio(gdev->sys_led.pin,1);
		printk(KERN_INFO "%s\n",__func__);
	}
}
#endif

static int sdmc_leds_suspend(struct platform_device *dev, pm_message_t state)
{
	int nRet =0;
	printk("\n@@@@@ turn off leds\n");
	if((gdev->net_led.active) == 0)
		sdmc_set_gpio(gdev->net_led.pin,0);
	else
		sdmc_set_gpio(gdev->net_led.pin,1);
	if((gdev->sys_led.active) == 0)
		sdmc_set_gpio(gdev->sys_led.pin,0);
	else
		sdmc_set_gpio(gdev->sys_led.pin,1);
	sdmc_set_gpio(DTV_PWR_GPIO,1);
	sdmc_set_gpio(gdev->tuner_loop_out.pin,0);
	//nRet = cancel_delayed_work_sync(&led_task);
	if(0 != nRet)
	{
	    printk("%s Failed,line = %d!\n",__FUNCTION__,__LINE__);
	}
	return nRet;
}

static int sdmc_leds_resume(struct platform_device *dev)
{
	int nRet =0;

	printk("\n@@@@@ turn on leds\n");
	sdmc_set_gpio(DTV_PWR_GPIO,0);
	sdmc_set_gpio(gdev->tuner_loop_out.pin,1);
	//nRet = queue_delayed_work(led_wq, &led_task, LED_UPDATE_INTERVAL);
	if(0 != nRet)
	{
	    printk("%s Failed,line = %d!\n",__FUNCTION__,__LINE__);
	}

	return nRet;
}

static ssize_t show_sys_led(struct class *class,
                    struct class_attribute *attr,      char *buf)
{
    return sprintf(buf, "%d\n",sdmc_get_gpio(gdev->sys_led.pin));
}

static ssize_t store_sys_led(struct class *class,
        struct class_attribute *attr, const char *buf, size_t count)
{
	unsigned int dbg;
	ssize_t r;
	r = sscanf(buf, "%d", &dbg);
	if (r != 1)
		return -EINVAL;
    if(1 == dbg)
	{
		sdmc_set_gpio(gdev->sys_led.pin,1);
	}else{
		sdmc_set_gpio(gdev->sys_led.pin,0);
	}

	return count;
}

static ssize_t show_net_led(struct class *class,
                    struct class_attribute *attr,      char *buf)
{
    return sprintf(buf, "%d\n",sdmc_get_gpio(gdev->net_led.pin));
}

static ssize_t store_net_led(struct class *class,
        struct class_attribute *attr, const char *buf, size_t count)
{
	unsigned int dbg;
	ssize_t r;
	r = sscanf(buf, "%d\n", &dbg);
	if (r != 1)
		return -EINVAL;

    if(1 == dbg)
	{
		sdmc_set_gpio(gdev->net_led.pin,1);
	}else{
		sdmc_set_gpio(gdev->net_led.pin,0);
	}

	return count;
}

static ssize_t show_dtv_pwr(struct class *class,
                    struct class_attribute *attr,      char *buf)
{
	if(NOUSED_GPIO != DTV_PWR_GPIO)
    	return sprintf(buf, "%d\n",sdmc_get_gpio(DTV_PWR_GPIO));
	else
		return sprintf(buf, "this gpio isn't used\n");
}

static ssize_t store_dtv_pwr(struct class *class,
        struct class_attribute *attr, const char *buf, size_t count)
{
	unsigned int dbg;
	ssize_t r;
	r = sscanf(buf, "%d", &dbg);
	if (r != 1 || NOUSED_GPIO == DTV_PWR_GPIO)
	{
		printk("invalid value, please input again\n");
		return -EINVAL;
	}
    if(1 == dbg)
	{
		sdmc_set_gpio(DTV_PWR_GPIO,1);
	}else{
		sdmc_set_gpio(DTV_PWR_GPIO,0);
	}

	return count;
}

static ssize_t show_ant_pwr(struct class *class,
                    struct class_attribute *attr,      char *buf)
{
    return sprintf(buf, "%d\n",sdmc_get_gpio(gdev->ant_pwr.pin));
}

static ssize_t store_ant_pwr(struct class *class,
        struct class_attribute *attr, const char *buf, size_t count)
{
	unsigned int dbg;
	ssize_t r;
	r = sscanf(buf, "%d", &dbg);
	if (r != 1)
		return -EINVAL;
    if(1 == dbg)
	{
		sdmc_set_gpio(gdev->ant_pwr.pin,1);
	}else{
		sdmc_set_gpio(gdev->ant_pwr.pin,0);
	}

	return count;
}

static ssize_t show_demo_res(struct class *class,
                    struct class_attribute *attr,      char *buf)
{
    return sprintf(buf, "%d\n",sdmc_get_gpio(gdev->demo_res.pin));
}

static ssize_t store_demo_res(struct class *class,
        struct class_attribute *attr, const char *buf, size_t count)
{
	unsigned int dbg;
	ssize_t r;
	r = sscanf(buf, "%d", &dbg);
	if (r != 1)
		return -EINVAL;
    if(1 == dbg)
	{
		sdmc_set_gpio(gdev->demo_res.pin,1);
	}else{
		sdmc_set_gpio(gdev->demo_res.pin,0);
	}

	return count;
}

static ssize_t show_s2_antpwr(struct class *class,
                    struct class_attribute *attr,      char *buf)
{
	if(NOUSED_GPIO != gdev->s2_ant_pwr.pin)
		return sprintf(buf, "%d\n",sdmc_get_gpio(gdev->s2_ant_pwr.pin));
	else
		return sprintf(buf, "this gpio isn't used\n");
}

static ssize_t store_s2_antpwr(struct class *class,
        struct class_attribute *attr, const char *buf, size_t count)
{
	unsigned int dbg;
	ssize_t r;
	r = sscanf(buf, "%d", &dbg);
	if (r != 1 || NOUSED_GPIO == gdev->s2_ant_pwr.pin)
	{
		printk("invalid value, please input again\n");
		return -EINVAL;
	}
    if(1 == dbg)
	{
		sdmc_set_gpio(gdev->s2_ant_pwr.pin,1);
	}else{
		sdmc_set_gpio(gdev->s2_ant_pwr.pin,0);
	}

	return count;
}

static ssize_t show_wifi_type(struct class *class,
                    struct class_attribute *attr,      char *buf)
{
	return sprintf(buf,"%d\n",t_wifi);
}

static ssize_t show_lockStatus(struct class *class,
                    struct class_attribute *attr,      char *buf)
{
	if(NOUSED_GPIO != gdev->tuner_lock_status.pin)
		return sprintf(buf, "%d\n",sdmc_get_gpio(gdev->tuner_lock_status.pin));
	else
		return sprintf(buf, "this gpio isn't used\n");
}

static ssize_t store_lockStatus(struct class *class,
        struct class_attribute *attr, const char *buf, size_t count)
{
	unsigned int dbg;
	ssize_t r;
	r = sscanf(buf, "%d", &dbg);
	if (r != 1 || NOUSED_GPIO == gdev->tuner_lock_status.pin)
	{
		printk("invalid value, please input again\n");
		return -EINVAL;
	}
    if(0 == dbg)
	{
		sdmc_set_gpio(gdev->tuner_lock_status.pin,1);
	}else{
		sdmc_set_gpio(gdev->tuner_lock_status.pin,0);
	}

	return count;
}

static ssize_t show_loopOut(struct class *class,
                    struct class_attribute *attr,      char *buf)
{
	if(NOUSED_GPIO != gdev->tuner_loop_out.pin)
		return sprintf(buf, "%d\n",sdmc_get_gpio(gdev->tuner_loop_out.pin));
	else
		return sprintf(buf, "this gpio isn't used\n");
}

static ssize_t store_loopOut(struct class *class,
        struct class_attribute *attr, const char *buf, size_t count)
{
	unsigned int dbg;
	ssize_t r;
	r = sscanf(buf, "%d", &dbg);
	if (r != 1 || NOUSED_GPIO == gdev->tuner_loop_out.pin)
	{
		printk("invalid value, please input again\n");
		return -EINVAL;
	}
    if(1 == dbg)
	{
		sdmc_set_gpio(gdev->tuner_loop_out.pin,1);
	}else{
		sdmc_set_gpio(gdev->tuner_loop_out.pin,0);
	}

	return count;
}

static ssize_t show_tunerChannel(struct class *class,
                    struct class_attribute *attr,      char *buf)
{
	if(NOUSED_GPIO != gdev->tuner_ch3_ch4.pin)
		return sprintf(buf, "%d\n",sdmc_get_gpio(gdev->tuner_ch3_ch4.pin));
	else
		return sprintf(buf, "this gpio isn't used\n");
}

static ssize_t store_tunerChannel(struct class *class,
        struct class_attribute *attr, const char *buf, size_t count)
{
	unsigned int dbg;
	ssize_t r;
	r = sscanf(buf, "%d", &dbg);
	if (r != 1 || NOUSED_GPIO == gdev->tuner_ch3_ch4.pin)
	{
		printk("invalid value, please input again\n");
		return -EINVAL;
	}
    if(1 == dbg)
	{
		sdmc_set_gpio(gdev->tuner_ch3_ch4.pin,1);
	}else{
		sdmc_set_gpio(gdev->tuner_ch3_ch4.pin,0);
	}

	return count;
}

static struct class_attribute sdmc_class_attrs[] = {
	__ATTR(sys_led,  S_IRUGO | S_IWUGO, show_sys_led,store_sys_led),
	__ATTR(net_led,  S_IRUGO | S_IWUGO, show_net_led,store_net_led),
	__ATTR(dtv_pwr,  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH, show_dtv_pwr,store_dtv_pwr),
	__ATTR(ant_pwr,  S_IRUGO | S_IWUGO, show_ant_pwr,store_ant_pwr),
	__ATTR(demo_res,  S_IRUGO | S_IWUGO, show_demo_res,store_demo_res),
	__ATTR(s2_antpwr,  S_IRUGO | S_IWUGO, show_s2_antpwr,store_s2_antpwr),
	__ATTR(wifi_type,  S_IRUGO | S_IWUGO, show_wifi_type,NULL),
	__ATTR(lockStatus,  S_IRUGO | S_IWUGO, show_lockStatus,store_lockStatus),
	__ATTR(loopOut,  S_IRUGO | S_IWUGO, show_loopOut,store_loopOut),
	__ATTR(tunerChannel,  S_IRUGO | S_IWUGO, show_tunerChannel,store_tunerChannel),
    __ATTR_NULL
};
static struct class sdmc_class = {
	.name = "sdmc",
	.class_attrs = sdmc_class_attrs,
 };

/* The workqueue must be created at init-time */

static const struct of_device_id sdmc_leds_dt_match[] = {
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

	desc = of_get_named_gpiod_flags(node, "sys_led", 0, &flags);
	gdev->sys_led.active = flags & OF_GPIO_ACTIVE_LOW;
	gdev->sys_led.pin = desc_to_gpio(desc);
	printk("###$$$ sdmc_gpio->sys_led.pin= %d flags=%d\n", gdev->sys_led.pin, flags);

	gdev->net_led.pin = -1;

	desc = of_get_named_gpiod_flags(node, "tuner_lnb", 0, &flags);
	gdev->ant_pwr.active = flags & OF_GPIO_ACTIVE_LOW;
	if(gdev->ant_pwr.active == 1)
		gdev->ant_pwr.pin = -1;
	else
		gdev->ant_pwr.pin = desc_to_gpio(desc);
	printk("###$$$ sdmc_gpio->ant_pwr.pin= %d flags=%d\n", gdev->ant_pwr.pin, flags);
	
	gdev->s2_ant_pwr.pin = -1;

	desc = of_get_named_gpiod_flags(node, "demo_res", 0, &flags);
	gdev->demo_res.active = flags & OF_GPIO_ACTIVE_LOW;
	if(gdev->demo_res.active == 1)
		gdev->demo_res.pin = -1;
	else
		gdev->demo_res.pin = desc_to_gpio(desc);
	printk("###$$$ sdmc_gpio->demo_res.pin= %d flags=%d\n", gdev->demo_res.pin, flags);

	desc = of_get_named_gpiod_flags(node, "tuner_lock_status", 0, &flags);
	gdev->tuner_lock_status.pin = desc_to_gpio(desc);
	gdev->tuner_lock_status.active = flags & OF_GPIO_ACTIVE_LOW;
	printk("sdmc_gpio->tuner_lock_status.pin= %d\n", gdev->tuner_lock_status.pin);
	
	desc = of_get_named_gpiod_flags(node, "tuner_loop_out", 0, &flags);
	gdev->tuner_loop_out.pin = desc_to_gpio(desc);
	gdev->tuner_loop_out.active = flags & OF_GPIO_ACTIVE_LOW;
	printk("sdmc_gpio->tuner_loop_out.pin= %d\n", gdev->tuner_loop_out.pin);
	
	desc = of_get_named_gpiod_flags(node, "tuner_ch3_ch4", 0, &flags);
	gdev->tuner_ch3_ch4.pin = desc_to_gpio(desc);
	gdev->tuner_ch3_ch4.active = flags & OF_GPIO_ACTIVE_LOW;
	printk("sdmc_gpio->tuner_ch3_ch4.pin= %d\n", gdev->tuner_ch3_ch4.pin);
	return 0;
}

static int sdmc_leds_probe(struct platform_device *pdev)
{
	int ret;
	int nRet = 0;
	gdev = kzalloc(sizeof(struct sdmc_gpio_devs), GFP_KERNEL);
	ret = sdmc_gpio_dt_parse(pdev);
	if (ret)
		return ret;
	/* register gpio class device */

#ifdef CONFIG_HAS_EARLYSUSPEND
	early_suspend.level = EARLY_SUSPEND_LEVEL_DISABLE_FB;
	early_suspend.suspend = sdmc_system_early_suspend;
	early_suspend.resume = sdmc_system_late_resume;
	register_early_suspend(&early_suspend);
#endif
	
	nRet = class_register(&sdmc_class);
    if(nRet)
        printk(" sdmc class register fail nRet = %d!\n",nRet);
	/* Create the work queue and queue the LED task */
	led_wq = create_singlethread_workqueue("led_wq");	
	nRet |= queue_delayed_work(led_wq, &led_task, 0);
	if(1 != nRet)
	{
	    printk("%s Failed!\n",__FUNCTION__);
	}

	return register_led_driver(0,0,0);
}
static int sdmc_leds_remove(struct platform_device *pdev)
{
	int nRet = 0;

	nRet = unregister_reboot_notifier(&led_notifier);
	if(0 != nRet)
	{
	    printk("%s Failed,line = %d!\n",__FUNCTION__,__LINE__);
	}
	sdmc_free_gpio(gdev->net_led.pin);
	sdmc_free_gpio(gdev->sys_led.pin);
	sdmc_free_gpio(DTV_PWR_GPIO);
	sdmc_free_gpio(gdev->ant_pwr.pin);
	sdmc_free_gpio(gdev->demo_res.pin);
	sdmc_free_gpio(gdev->s2_ant_pwr.pin);
	sdmc_free_gpio(IR_GPIO);
	sdmc_free_gpio(gdev->tuner_lock_status.pin);
	sdmc_free_gpio(gdev->tuner_loop_out.pin);
	sdmc_free_gpio(gdev->tuner_ch3_ch4.pin);

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
/*平台驱动定义*/
static struct platform_driver sdmc_leds_driver = {
	.probe		= sdmc_leds_probe,
	.remove		= sdmc_leds_remove,
	.suspend	= sdmc_leds_suspend,
	.resume		= sdmc_leds_resume,
	.driver		= {
		.owner	= THIS_MODULE,
		.name	= "gpioctrl",
		.of_match_table = sdmc_leds_dt_match,
	},
};
static struct platform_device sdmc_leds_device ={
    .name = "gpioctrl",
	.dev.release	= sdmc_leds_dev_release,
};

static int __init sdmc_leds_init(void)
{
	int nRet = 0;
	/*
	nRet = platform_device_register(&sdmc_leds_device);
	if(0 != nRet)
	{
	    printk("%s Failed,line = %d!\n",__FUNCTION__,__LINE__);
	}*/
	/*平台驱动注册*/
	return platform_driver_register(&sdmc_leds_driver);
}

static void __exit sdmc_leds_exit(void)
{
	platform_driver_unregister(&sdmc_leds_driver);
	/*platform_device_unregister(&sdmc_leds_device);*/
}
module_init(sdmc_leds_init);
module_exit(sdmc_leds_exit);

MODULE_DESCRIPTION("SDMC leds driver ");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Young <young_yang@sdmctech.com>");
MODULE_VERSION("sdmc v1.0.0");