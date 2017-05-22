#define LOG_TAG	"FregServiceJNI"

#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"
#include <utils/misc.h>
#include <utils/Log.h>
#include <hardware/hardware.h>
#include <hardware/freg.h>

namespace android
{
	/* set the value of the fake hardware device freg's register */
	static void freg_setVal(JNIEnv *env, jobject clazz, jint ptr, jint value) {
		freg_device_t *device = (freg_device_t *)ptr;
		if (!device) {
			ALOGE("Device freg is not open.");
			return;
		}

		int val = value;
		ALOGI("Set value %d to device freg.", val);
		device->set_val(device, val);
	}

	/* read the value of the fake hardware device freg's regiter */
	static jint freg_getVal(JNIEnv *env, jobject clazz, jint ptr) {
		freg_device_t *device = (freg_device_t *)ptr;
		if (!device) {
			ALOGE("Device freg is not open.");
			return 0;
		}

		int val = 0;
		device->get_val(device, &val);
		ALOGI("Get value %d from device freg.", val);

		return val;
	}

	/* open fake hardware device freg */
	static inline int freg_device_open(const hw_module_t *module, struct freg_device_t **device) {
		return module->methods->open(module, FREG_HARDWARE_DEVICE_ID, (struct hw_device_t **)device);
	}

	/* init the fake hardware device freg */
	static jint freg_init(JNIEnv *env, jclass clazz) {
		freg_module_t *module;
		freg_device_t *device;

		ALOGI("initializing HAL stub freg ......");
		/* load the hal module freg */
		if (hw_get_module(FREG_HARDWARE_MODULE_ID, (const struct hw_module_t **)&module) == 0) {
			ALOGI("Device freg found.");

			/* open fake hardware device freg */
			if (freg_device_open(&(module->common), &device) == 0) {
				ALOGI("Device freg is open.");

				/* convert the freg_devict_t to int as the return value */
				return (jint)device;
			}
			ALOGE("Failed to open device freg.");
			return 0;
		}

		ALOGE("Failed to get HAL stub freg.");
		return 0;
	}

	/* java native interface methods */
	static const JNINativeMethod method_table[] = {
		{"init_native", "()I", (void *)freg_init},
		{"setVal_native", "(II)V", (void *)freg_setVal},
		{"getVal_native", "(I)I", (void *)freg_getVal},
	};

	/* register java native interface methods */
	int register_android_server_FregService(JNIEnv *env) {
		return jniRegisterNativeMethods(env, "com/android/server/FregService", method_table, NELEM(method_table));
	}
};

