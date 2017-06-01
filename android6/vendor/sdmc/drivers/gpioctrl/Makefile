EXTRA_CFLAGS += $(USER_EXTRA_CFLAGS)
EXTRA_CFLAGS += -O1
#EXTRA_CFLAGS += -O3
#EXTRA_CFLAGS += -Wall
#EXTRA_CFLAGS += -Wextra
#EXTRA_CFLAGS += -Werror
#EXTRA_CFLAGS += -pedantic
#EXTRA_CFLAGS += -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes

EXTRA_CFLAGS += -Wno-unused-variable
EXTRA_CFLAGS += -Wno-unused-value
EXTRA_CFLAGS += -Wno-unused-label
EXTRA_CFLAGS += -Wno-unused-parameter
EXTRA_CFLAGS += -Wno-unused-function
EXTRA_CFLAGS += -Wno-unused

#EXTRA_CFLAGS += -Wno-uninitialized

EXTRA_CFLAGS += -I$(src)/include

EXTRA_LDFLAGS += --strip-debug

MODULE_NAME = gpioctrl

CONFIG_AUTOCFG_CP = n

#$(MODULE_NAME)-y += gpioctrl.o

obj-m := $(MODULE_NAME).o
ifeq ($(vendor), cuba)
$(MODULE_NAME)-objs = $(MODULE_NAME)_cuba.o
else
$(MODULE_NAME)-objs = $(MODULE_NAME)_normal.o
endif
ARCH :=arm64
ifeq ($(TARGET_PRODUCT), )
KSRC :=$(shell pwd)/../../../../out/target/product/p201/obj/KERNEL_OBJ
MODULE_OUT := $(ANDROID_BUILD_TOP)/out/target/product/p201/system/lib/
else
CROSS_COMPILE :=aarch64-linux-gnu-
KSRC :=$(ANDROID_BUILD_TOP)/out/target/product/$(TARGET_PRODUCT)/obj/KERNEL_OBJ
MODULE_OUT := $(ANDROID_BUILD_TOP)/out/target/product/$(TARGET_PRODUCT)/system/lib/
endif

all: modules

modules:
	echo "====== $(MODULE_NAME) ======"
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KSRC) O=$(KSRC) M=$(shell pwd)  modules
	install -p -m 644 $(MODULE_NAME).ko  $(MODULE_OUT)
	@rm -fr Module.symvers ; rm -fr Module.markers ; rm -fr modules.order
	@rm -fr *.mod.c *.mod *.o .*.cmd *.ko *~
	@rm -fr .tmp_versions

strip:
	$(CROSS_COMPILE)strip $(MODULE_NAME).ko --strip-unneeded

install:modules
#	install -p -m 644 $(MODULE_NAME).ko  $(MODULE_OUT)

uninstall:
	rm -f $(MODULE_OUT)/$(MODULE_NAME).ko

config_r:
	@echo "make config"
	/bin/bash script/Configure script/config.in

.PHONY: modules clean

clean:
	@rm -fr Module.symvers ; rm -fr Module.markers ; rm -fr modules.order
	@rm -fr *.mod.c *.mod *.o .*.cmd *.ko *~
	@rm -fr .tmp_versions
	@rm -f $(MODULE_OUT)/$(MODULE_NAME).ko

