#ifndef ANDROID_FREG_INTERFACE_H
#define ANDROID_FREG_INTERFACE_H

#include <hardware/hardware.h>

__BEGIN_DECLS

/* define module ID */
#define FREG_HARDWARE_MODULE_ID "freg"

/* define device ID */
#define FREG_HARDWARE_DEVICE_ID "freg"

/* �Զ���ģ��ṹ�� */
struct freg_module_t {
    struct hw_module_t common;
};
 
/* �Զ����豸�ṹ�� */
struct freg_device_t {
    struct hw_device_t common;
    int fd;
    int (*set_val)(struct freg_device_t *dev�� int val);
    int (*get_val)(struct freg_device_t *dev�� int *val);
};

__END_DECLS

#endif

