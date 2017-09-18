
#
# Ronny creat it to make ota package on amlogic platform
#
# Copyright(c) : SDMC Apr 09, 2013
#
# <ronny@nuedc.net.cn>
#
define parse_parameters
$(shell if [ -z $(strip $(1)) ];then echo NULL;else echo $(strip $(1));fi)
endef

define print_parameters
	@echo "customer name : $(CUSTOMER)"
	@echo "product  type : $(PRODUCT)"
	@echo "package  type : $(PACKTYPE)"
	@echo "fw    version : $(VERSION)"
	@echo "base  version : $(BASEVER)"
	@echo "odex     flag : $(ODEXFLAG)"
	@echo "imgpkg  model : $(IMGPKG)"	
endef
# receive the make parameters
CUSTOMER := $(call parse_parameters, $(c))
PRODUCT  := $(call parse_parameters, $(p))
PACKTYPE := $(call parse_parameters, $(t))
VERSION  := $(call parse_parameters, $(v))
BASEVER  := $(call parse_parameters, $(i))
ODEXFLAG := $(call parse_parameters, $(d))
IMGPKG   := $(call parse_parameters, $(m))

# declare platform variables
ifeq ($(PRODUCT),dv7905)
PLATFORM_SDK := 0612_sdk
PLATFORM_VERSION := m8b-m201
UBOOT_TYPE	:= uboot
RAMDISK_TYPE	:= ramdisk
FRAMWORK_TYPE	:= framework
DT_TYPE         := dt_ott
BOARD_MKBOOTIMG_ARGS :=kernel/$(PLATFORM_SDK)/$(PLATFORM_VERSION)/$(RAMDISK_TYPE)/$(DT_TYPE)/dt.img
FRAMWORK := ./framework/$(PLATFORM_SDK)/$(PLATFORM_VERSION)/$(FRAMWORK_TYPE)/m8b-system.tar.bz2
endif

# declare platform variables
ifeq ($(PRODUCT),dv7920)
PLATFORM_SDK := 0612_sdk
PLATFORM_VERSION := m8b-m201
UBOOT_TYPE	:= uboot
RAMDISK_TYPE	:= ramdisk
FRAMWORK_TYPE	:= framework
DT_TYPE         := dt_ott
BOARD_MKBOOTIMG_ARGS :=kernel/$(PLATFORM_SDK)/$(PLATFORM_VERSION)/$(RAMDISK_TYPE)/$(DT_TYPE)/dt.img
FRAMWORK := ./framework/$(PLATFORM_SDK)/$(PLATFORM_VERSION)/$(FRAMWORK_TYPE)/m8b-system.tar.bz2
endif

ifeq ($(PRODUCT),dv7905_8189)
PLATFORM_SDK := 0414_sdk
PLATFORM_VERSION := m8b-m201
UBOOT_TYPE	:= uboot_ap8189
RAMDISK_TYPE	:= ramdisk_ap8189
FRAMWORK_TYPE	:= framework_ap8189
DT_TYPE         := dt_ott
BOARD_MKBOOTIMG_ARGS :=kernel/$(PLATFORM_SDK)/$(PLATFORM_VERSION)/$(RAMDISK_TYPE)/$(DT_TYPE)/dt.img
FRAMWORK := ./framework/$(PLATFORM_SDK)/$(PLATFORM_VERSION)/$(FRAMWORK_TYPE)/m8b-system.tar.bz2
endif

ifeq ($(PRODUCT),dv6063)
PLATFORM_SDK := 0414_sdk
PLATFORM_VERSION := m8b-m201
UBOOT_TYPE	:= uboot_6063
RAMDISK_TYPE	:= ramdisk_6063
FRAMWORK_TYPE	:= framework_6063
DT_TYPE         := dt_ott
BOARD_MKBOOTIMG_ARGS :=kernel/$(PLATFORM_SDK)/$(PLATFORM_VERSION)/$(RAMDISK_TYPE)/$(DT_TYPE)/dt.img
FRAMWORK := ./framework/$(PLATFORM_SDK)/$(PLATFORM_VERSION)/$(FRAMWORK_TYPE)/m8b-system.tar.bz2
AML_PACKAGE_BOOTLOADER := bootloader/$(PLATFORM_SDK)/$(PLATFORM_VERSION)/$(UBOOT_TYPE)/$(IMGPKG)
endif

ifeq ($(PRODUCT),dv7810)
PLATFORM_SDK := 0612_sdk
PLATFORM_VERSION := m8-n200
RAMDISK_TYPE	:= ramdisk
UBOOT_TYPE	:= uboot
FRAMWORK_TYPE	:= framework
BOARD_MKBOOTIMG_ARGS :=kernel/$(PLATFORM_SDK)/$(PLATFORM_VERSION)/$(RAMDISK_TYPE)/dt.img
FRAMWORK := ./framework/$(PLATFORM_SDK)/$(PLATFORM_VERSION)/$(FRAMWORK_TYPE)/m8-system.tar.bz2
endif

ifeq ($(PRODUCT),dv7904)
PLATFORM_SDK := 0612_sdk
PLATFORM_VERSION := m8b-m201
UBOOT_TYPE	:= uboot
RAMDISK_TYPE	:= ramdisk
FRAMWORK_TYPE	:= framework
DT_TYPE         := dt_dvb
BOARD_MKBOOTIMG_ARGS :=kernel/$(PLATFORM_SDK)/$(PLATFORM_VERSION)/$(RAMDISK_TYPE)/$(DT_TYPE)/dt.img
FRAMWORK := ./framework/$(PLATFORM_SDK)/$(PLATFORM_VERSION)/$(FRAMWORK_TYPE)/m8b-system.tar.bz2
endif

TARGET_AMLOGIC_BOOTLOADER_NORAML := bootloader/$(PLATFORM_SDK)/$(PLATFORM_VERSION)/$(UBOOT_TYPE)/u-boot.bin
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 805306368

ifeq ($(IMGPKG), img)
AML_PACKAGE_BOOTLOADER := bootloader/$(PLATFORM_SDK)/$(PLATFORM_VERSION)/$(UBOOT_TYPE)/$(IMGPKG)
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 1073741824
endif

# declare global variables
TOOLS_DIR	:=	tools
COMMON_TOOl_DIR := tools/common/bin
HOST_OUT_EXECUTABLES := $(TOOLS_DIR)/android-utils/host/bin
MISC_TOOL_DIR := $(TOOLS_DIR)/android-utils/misc
SECURE_TOOL_DIR := $(TOOLS_DIR)/android-utils/security
ACP := $(HOST_OUT_EXECUTABLES)/acp

OUTPUT_DIR := out/$(PRODUCT)
CACHE_DIR := cache/$(PRODUCT)
ODEX_OUT_DIR := $(OUTPUT_DIR)/$(ODEXFLAG)/$(CUSTOMER)
ZIP_ROOT := $(CACHE_DIR)/target_files
CUSMOTER_DIR := platform/$(PRODUCT)/$(CUSTOMER)
SYSTEM_DIR := $(ZIP_ROOT)/SYSTEM

IMAGES_OUT_DIR := $(OUTPUT_DIR)/images/$(CUSTOMER)
OTAPCAKGE_OUT_DIR := $(OUTPUT_DIR)/otapackages/$(CUSTOMER)
BACKUP_OUT_DIR := $(OUTPUT_DIR)/backup
BACKUP_BASE_OTAPACKAGE_DIR := $(OUTPUT_DIR)/base-otapackage

define usage

	@echo "******************************************************************************************************"
	@echo " "
	@echo "* Copyright Shenzhen SDMC Electronics Co. Ltd,"
	@echo "* All rights reserved"
	@echo " "
	@echo "* Summary: Firmware generater for amlogic platform"
	@echo "* Current version: 4.2.2"
	@echo "*      Reversion           Author       Reason			        Date"
	@echo "*      mx-mr1-4.4          Ronny        Create		    Apr 09, 2013"
	@echo "	"	
	@echo "* Usage: make c=[custmoer] p=[product] t=[package-type] v=[version] i=[base version] d=[odex mode] "
	@echo "	"
	@echo "* Example: make c=normal p=dv7905 t=incsys v=4.4.0.0 i=4.0.0.0"
	@echo "*          make c=normal p=dv7905 t=bkrs v=4.4.0.0 d=odex"
	@echo "	"
	@echo "* Customer-name: "
	@echo "*      normal  ..."
	@echo "*      			     "
	@echo "* Product-name: "
	@echo "*      dv7905 : DDR_SIZE = 2*256M, NAND_SIZE = 4096M | 8092M"
	@echo "*      dv6061_v6 : DDR_SIZE = 2*512M, NAND_SIZE = 4096M | 8092M HDMI dongle"
	@echo "*      dv6800v_v6: DDR_SIZE = x*xxxM, NAND_SIZE = 4096M | 8092M verimatrix box"
	@echo "* 						"
	@echo "* Package-type:	   " 
	@echo "*      logo           (logo)"
	@echo "*      incsys         (system)"
	@echo "*      lnxsys         (kernel and system)"
	@echo "*      lnxrecsys      (logo, kernel, recovery, system)"
	@echo "*      bkrs           (boot, logo, kernel, recovery, system)"
	@echo "*      			        "	
	@echo "* Version : fireware version"
	@echo "*      			        "	
	@echo "* Base version: The project will make incremental otapackage if not empty or not NULL"
	@echo "*      			        "	
	@echo "* odex mode: if d=odex ,it will odex optimize system, or it doesn't work "
	@echo "* 						"	
	@echo "******************************************************************************************************"
	@echo
	exit 1
endef

define check_make_args
	$(hide) $(if $(findstring "$(PRODUCT)", "dv7905" "dv7905_1g" "dv7904_512m" "dv7904_1g" "dv7810" "dv7819_ap62x2" "dv7905_ap62x2" "dv7904_ap8189" "dv7819" 
	"dv7905_8189" "dv6063" "dv7904" "dv7905_1080p" "dv7920"),,\
				@echo "wrong product type : $(PRODUCT)"; $(call usage))
			
	$(hide) $(if $(findstring "$(PACKTYPE)", "bkrs" "lnxsys" "incsys" "logo"),,\
				@echo "wrong package type : $(PACKTYPE)"; $(call usage))
	
	$(hide) $(if $(findstring "$(CUSTOMER)", "Vmedia" "normal" "normal_ca" "yxt" "beenius" "dexp" "israel" "bennius_no_apk" "hk" "thailand" "bennius_artur" "hk_normal" 
	"spanish" "cmcc_normal" "cntv_normal" "cucc_normal" "atsc" "teledevice" "anhui" "CTI" "Vaas" "APLI_TV" "kodak" "hk_prima" "next" "normal_6064" "normal_c" "vector" "normal_s2" "xingyi_hospital"
        "nevron" "vevi" "odtv" "cable_tv" "taiji" "normal_c_j83b" "Bit-Tech" "YE-7805" "Bit-Tech" "ChannelAfrik" "CMT_s2" "Almajd_s2" "US_s2" "EDI-II" "tr069"),,\
				@echo "wrong package type : $(CUSTOMER)"; $(call usage))
  
  if [ "$(BASEVER)" != "NULL" ]; then \
    $(MISC_TOOL_DIR)/chk_inc_ver_is_valid $(BASEVER) $(VERSION); \
  fi
endef

#
# make otapackage main entry
#
DATE=$(shell date +%y%m%d%H%M)
OTA_GEN_PKG := $(COMMON_TOOl_DIR)/ota_gen_pkg
OTA_GEN_SYSINFO := $(COMMON_TOOl_DIR)/gen_ota_sysinfo
PLATFORM_CONFIG := ./platform/$(PRODUCT)/$(CUSTOMER)/platform.cfg
BUILT_TARGET_FILES_PACKAGE := $(CACHE_DIR)/$(PLATFORM_VERSION)-ota-base-$(DATE).zip
INTERNAL_OTA_PACKAGE_TARGET := $(CACHE_DIR)/$(PLATFORM_VERSION)-ota-$(DATE).zip
BASE_BUILT_TARGET_FILES_PACKAGE	:= $(BACKUP_BASE_OTAPACKAGE_DIR)/$(PLATFORM_VERSION)-$(PRODUCT)-$(CUSTOMER)-v$(BASEVER)-BASEPACKAGE.zip
CURRENT_BUILT_TARGET_FILES_PACKAGE := $(BACKUP_BASE_OTAPACKAGE_DIR)/$(PLATFORM_VERSION)-$(PRODUCT)-$(CUSTOMER)-v$(VERSION)-BASEPACKAGE.zip
ifneq ($(BASEVER),NULL)
OTA_PACKAGE_NAME = $(OTAPCAKGE_OUT_DIR)/$(PLATFORM_VERSION)-$(PRODUCT)-$(CUSTOMER)-v$(VERSION)-i$(BASEVER)-$(DATE).zip
else
OTA_PACKAGE_NAME = $(OTAPCAKGE_OUT_DIR)/$(PLATFORM_VERSION)-$(PRODUCT)-$(CUSTOMER)-v$(VERSION)-$(DATE).zip
IMG_PACKAGE_NAME = $(OTAPCAKGE_OUT_DIR)/$(PLATFORM_VERSION)-$(PRODUCT)-$(CUSTOMER)-v$(VERSION)-$(DATE).img
endif

ifeq ($(IMGPKG), img)
$(OTA_PACKAGE_NAME): get_args $(INTERNAL_OTA_PACKAGE_TARGET) $(IMG_PACKAGE_NAME)
else
$(OTA_PACKAGE_NAME): get_args $(INTERNAL_OTA_PACKAGE_TARGET)
endif
	@echo "\nmaking package, pls wait ...\n"
#ifeq ($(IMGPKG), img)	
#	@cp -f $(INTERNAL_OTA_PACKAGE_TARGET) $(OTA_PACKAGE_NAME)
#else	
	$(hide) $(OTA_GEN_PKG) -t $(PACKTYPE) -c $(PLATFORM_CONFIG) -v $(VERSION) -i $(BASEVER) -f $(INTERNAL_OTA_PACKAGE_TARGET) -o $@
#endif
.PHONY: make_ota_package
make_ota_package:$(OTA_PACKAGE_NAME)

#
# build initroot logo
#
RGB2565 = $(HOST_OUT_EXECUTABLES)/BMP2RGB565
BOOT_LOGO = ./platform/$(PRODUCT)/$(CUSTOMER)/boot-logo/logo.bmp
RECOVERY_LOGO = ./platform/$(PRODUCT)/$(CUSTOMER)/logo/initlogo.rle
define build_initroot_logo
  if [ -f "$(BOOT_LOGO)" ];then \
	$(RGB2565) $(BOOT_LOGO) $(TARGET_AMLOGIC_RES_PACKAGE)/bootup	 ;\
	sync; \
  fi
endef

#
# build boot and recovery 
#
KERNEL_DIR = ./kernel/$(PLATFORM_SDK)/$(PLATFORM_VERSION)
INSTALLED_KERNEL_TARGET = $(KERNEL_DIR)/$(RAMDISK_TYPE)/kernel
MKBOOTFS = $(HOST_OUT_EXECUTABLES)/mkbootfs
MKBOOTIMG = $(HOST_OUT_EXECUTABLES)/mkbootimg
MINIGZIP = $(HOST_OUT_EXECUTABLES)/minigzip
MAKE_EXT4FS = $(HOST_OUT_EXECUTABLES)/make_ext4fs
#
# build boot.img
#
TARGET_BOOT_DIR = $(ZIP_ROOT)/BOOT
INSTALLED_BOOTIMAGE_TARGET = $(CACHE_DIR)/boot.img
BOOT_RAMDISK = $(KERNEL_DIR)/$(RAMDISK_TYPE)/root.tar.bz2
$(INSTALLED_BOOTIMAGE_TARGET) : $(BOOT_RAMDISK) $(MKBOOTIMG) $(MINIGZIP) $(MKBOOTFS) $(INSTALLED_KERNEL_TARGET)
	@mkdir -p $(TARGET_BOOT_DIR)
	tar -jxf $< -C $(TARGET_BOOT_DIR)/
	@mv $(TARGET_BOOT_DIR)/root $(TARGET_BOOT_DIR)/RAMDISK
	@cp -f $(INSTALLED_KERNEL_TARGET) $(TARGET_BOOT_DIR)/kernel
	$(hide) $(call build_initroot_logo, $(TARGET_BOOT_DIR)/RAMDISK)
	$(hide) $(MKBOOTFS) $(TARGET_BOOT_DIR)/RAMDISK | $(MINIGZIP) > $(CACHE_DIR)/ramdisk.img
	$(hide) $(MKBOOTIMG) --kernel $(INSTALLED_KERNEL_TARGET) --second $(BOARD_MKBOOTIMG_ARGS) --ramdisk $(CACHE_DIR)/ramdisk.img --output $@
	@mv $@ $(IMAGES_OUT_DIR)/
	@rm -f $(CACHE_DIR)/ramdisk.img

.PHONY: installboot
installboot : $(INSTALLED_BOOTIMAGE_TARGET)

#
# build recovery.img
#
TARGET_RECOVERY_DIR := $(ZIP_ROOT)/RECOVERY
INSTALLED_RECOVERYIMAGE_TARGET := $(CACHE_DIR)/recovery.img
INSTALLED_AMLOGIC_RECOVERY_TARGET := $(CACHE_DIR)/ramdisk-recovery.img
RECOVERY_RAMDISK := $(KERNEL_DIR)/$(RAMDISK_TYPE)/root-recovery.tar.bz2
RECOVERY_REMOTE_CONFIG := $(CUSMOTER_DIR)/private.system/etc/*
$(INSTALLED_RECOVERYIMAGE_TARGET) : $(RECOVERY_RAMDISK) $(MKBOOTIMG) $(MINIGZIP) $(MKBOOTFS) $(INSTALLED_KERNEL_TARGET)
	@mkdir -p $(TARGET_RECOVERY_DIR)
	tar -jxf $< -C $(TARGET_RECOVERY_DIR)/
	@mv $(TARGET_RECOVERY_DIR)/root $(TARGET_RECOVERY_DIR)/RAMDISK
	@cp -f $(INSTALLED_KERNEL_TARGET) $(TARGET_RECOVERY_DIR)/kernel
	$(hide) $(call build_initroot_logo, $(TARGET_RECOVERY_DIR)/RAMDISK)
	@cp -rf $(RECOVERY_REMOTE_CONFIG) $(TARGET_RECOVERY_DIR)/RAMDISK/etc/
	$(hide) $(MKBOOTFS) $(TARGET_RECOVERY_DIR)/RAMDISK | $(MINIGZIP) > $(INSTALLED_AMLOGIC_RECOVERY_TARGET)
	$(hide) $(MKBOOTIMG) --kernel $(INSTALLED_KERNEL_TARGET) --second $(BOARD_MKBOOTIMG_ARGS) --ramdisk $(INSTALLED_AMLOGIC_RECOVERY_TARGET) --output $@
	@mv $@ $(IMAGES_OUT_DIR)/
	@rm -f $(INSTALLED_AMLOGIC_RECOVERY_TARGET)

.PHONY: installrecovery
installrecovery: $(INSTALLED_RECOVERYIMAGE_TARGET)

#
# encrypt resources
#

TERMINAL_CRYPT_DIR := /crypt
CRYPT_RES_NAME := crypt_res.bin
RM_FILE_TOOL := $(COMMON_TOOl_DIR)/rm_file
ENCRYPT_TOOL := $(COMMON_TOOl_DIR)/encrypt_res
DECRYPT_TOOL := $(COMMON_TOOl_DIR)/decrypt_res
DOS2UNIX_TOOL := $(COMMON_TOOl_DIR)/dos2unix
ENCRYPT_RES_LIST := $(CUSMOTER_DIR)/encrypt/crypt_list.cfg
ENCRYPT_RES_DIR := $(CUSMOTER_DIR)/encrypt/encrypt_resources
define do_encrypt_res
if [ ! -f $(ENCRYPT_RES_LIST) ];then \
	$(hide) echo "file isn't exist : $(ENCRYPT_RES_LIST)"; \
	$(hide) echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"; \
else \
  if [ ! -d $(ENCRYPT_RES_DIR) ];then \
	$(hide) echo "dir isn't exist : $(ENCRYPT_RES_DIR)"; \
	$(hide) echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"; \
  else \
  	$(hide) echo ready to do crypt, pls wait ...; \
	$(hide) $(DOS2UNIX_TOOL) $(ENCRYPT_RES_LIST); \
	$(hide) $(ENCRYPT_TOOL) -c $(ENCRYPT_RES_LIST) -d $(ENCRYPT_RES_DIR) -o $(2); \
	$(hide) cp $(DECRYPT_TOOL) $(1)/system/bin/; \
	$(hide) chmod 777 $(1)/system/bin/$(notdir $(DECRYPT_TOOL)); \
	$(hide) sh $(RM_FILE_TOOL) $(1) $(ENCRYPT_RES_LIST); \
	$(hide) sync; \
  	$(hide) echo crypt finish.; \
  fi \
fi
endef

#
# build system
#
CUSTOMER_DIR := platform/$(PRODUCT)/$(CUSTOMER)
PLATFORM_PUBLIC_DIR := platform/platform_public
CUSTOMER_PUBLIC_DIR := platform/$(PRODUCT)/customer_public
CUSTOMISZED_DATA_DIR := $(CUSTOMER_DIR)/customized_data
INSTALLED_SYSTEM_TARGET := $(ZIP_ROOT)/SYSTEM
CURRENT_DIR := $(shell pwd)
$(INSTALLED_SYSTEM_TARGET): $(FRAMWORK)
	@echo "" && echo "decompressing framework, pls wait ..." && echo ""
	@tar jxf $< -C $(ZIP_ROOT)
	$(call do_encrypt_res, $(ZIP_ROOT), $(ZIP_ROOT)/system/$(CRYPT_RES_NAME))
	@mv $(ZIP_ROOT)/system $@
	@cp cache/sysinfo.fex $(INSTALLED_SYSTEM_TARGET)/bin/
	@sh $(CUSTOMER_DIR)/build.sh "$@" "$(CUSTOMER_DIR)" "$(FACTORY)" "$(VERSION)" "$(PLATFORM_PUBLIC_DIR)" "$(CUSTOMER_PUBLIC_DIR)"
	@# try to backup customer data
	$(hide) cd $(CUSTOMISZED_DATA_DIR)/ && tar cvf $(CURRENT_DIR)/$@/customized_data.tar *
ifeq ($(ODEXFLAG), odex)
	@mkdir -p $(ODEX_OUT_DIR)/system/ && rm -rf $(ODEX_OUT_DIR)/system/*
	@mv $@/framework $(ODEX_OUT_DIR)/system/
	@mv $@/app       $(ODEX_OUT_DIR)/system/
	@mv $@/priv-app       $(ODEX_OUT_DIR)/system/
	@sync && sh $(MISC_TOOL_DIR)/odex-optimize "$(PWD)/$(ODEX_OUT_DIR)" "$(PWD)/$(HOST_OUT_EXECUTABLES)"&& sync
	@mv $(ODEX_OUT_DIR)/system/framework $@/
	@mv $(ODEX_OUT_DIR)/system/app       $@/
	@mv $(ODEX_OUT_DIR)/system/priv-app       $@/
	@sync
	@# remove tmp dir 
	@rm -rf $(OUTPUT_DIR)/$(CUSTOMER)
endif

ifeq ($(IMGPKG), img)
	@./tools/android-utils/host/bin/mkuserimg.sh -s $(INSTALLED_SYSTEM_TARGET) $(IMAGES_OUT_DIR)/system.img ext4 system $(BOARD_SYSTEMIMAGE_PARTITION_SIZE) $(TARGET_BOOT_DIR)/RAMDISK/file_contexts
endif

.PHONY: installsystem
installsystem : $(INSTALLED_SYSTEM_TARGET)


# apk certs file
APKCERTS_FILE := $(SECURE_TOOL_DIR)/apkcerts.txt

#
# build ota tools
#
TARGET_BUILD_OMIT_PREREQ := false
TARGET_BUILD_WIPE_USERDATA := false
built_ota_tools := ./$(TOOLS_DIR)/android-utils/target
BOOTLOGO = ./platform/$(PRODUCT)/$(CUSTOMER)/boot-logo/logo.bmp
IMGPACK = $(HOST_OUT_EXECUTABLES)/imgpack

TARGET_AMLOGIC_RES_PACKAGE := $(dir $(BOOTLOGO))../res_pack
PRIVATE_RECOVERY_API_VERSION := 3
BOARD_FLASH_BLOCK_SIZE := 2048
ifeq ($(TARGET_RELEASETOOLS_EXTENSIONS),)
# default to common dir for device vendor
$(BUILT_TARGET_FILES_PACKAGE): tool_extensions := $(CACHE_DIR)/common
else
$(BUILT_TARGET_FILES_PACKAGE): tool_extensions := $(TARGET_RELEASETOOLS_EXTENSIONS)
endif
DEFAULT_SYSTEM_DEV_CERTIFICATE := $(SECURE_TOOL_DIR)/testkey
INTERNAL_USERIMAGES_EXT_VARIANT := ext4
INTERNAL_USERIMAGES_SPARSE_EXT_FLAG := -s

# $(1): the path of the output dictionary file
define generate-userimage-prop-dictionary
$(if $(INTERNAL_USERIMAGES_EXT_VARIANT),$(hide) echo "fs_type=$(INTERNAL_USERIMAGES_EXT_VARIANT)" >> $(1))
$(if $(BOARD_SYSTEMIMAGE_PARTITION_SIZE),$(hide) echo "system_size=$(BOARD_SYSTEMIMAGE_PARTITION_SIZE)" >> $(1))
$(if $(BOARD_USERDATAIMAGE_PARTITION_SIZE),$(hide) echo "userdata_size=$(BOARD_USERDATAIMAGE_PARTITION_SIZE)" >> $(1))
$(if $(BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE),$(hide) echo "cache_fs_type=$(BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE)" >> $(1))
$(if $(BOARD_CACHEIMAGE_PARTITION_SIZE),$(hide) echo "cache_size=$(BOARD_CACHEIMAGE_PARTITION_SIZE)" >> $(1))
$(if $(INTERNAL_USERIMAGES_SPARSE_EXT_FLAG),$(hide) echo "extfs_sparse_flag=$(INTERNAL_USERIMAGES_SPARSE_EXT_FLAG)" >> $(1))
$(if $(mkyaffs2_extra_flags),$(hide) echo "mkyaffs2_extra_flags=$(mkyaffs2_extra_flags)" >> $(1))
$(if $(filter true, $(strip $(HAVE_SELINUX))), echo "selinux_fc=$(TARGET_ROOT_OUT)/file_contexts" >> $(1))
endef

ifneq ($(TARGET_AMLOGIC_RES_PACKAGE),)

INSTALLED_AML_LOGO := $(IMAGES_OUT_DIR)/res-package.img
$(INSTALLED_AML_LOGO): $(IMGPACK)
	@echo
	@echo "generate $(INSTALLED_AML_LOGO)"
	@echo
#	@cp -f $(BOOTLOGO) $(strip $(TARGET_AMLOGIC_RES_PACKAGE))/bootup 
	$(IMGPACK) -r $(TARGET_AMLOGIC_RES_PACKAGE) $@
else
	INSTALLED_AML_LOGO := $(BOOTLOGO)
endif

$(BUILT_TARGET_FILES_PACKAGE): \
		OTA_PACKAGE_RELY_SRC \
		$(INSTALLED_RADIOIMAGE_TARGET) \
		$(built_ota_tools) \
		$(APKCERTS_FILE) \
		$(HOST_OUT_EXECUTABLES)/fs_config \
		| $(ACP) \
		$(INSTALLED_AML_LOGO) \
		$(TARGET_AMLOGIC_KERNEL)
	@echo "Package target files: $@"
	$(hide) mkdir -p $(dir $@) $(ZIP_ROOT)
ifdef INSTALLED_2NDBOOTLOADER_TARGET
	$(hide) $(ACP) \
		$(INSTALLED_2NDBOOTLOADER_TARGET) $(ZIP_ROOT)/RECOVERY/second
endif
ifdef BOARD_KERNEL_CMDLINE
	$(hide) echo "$(BOARD_KERNEL_CMDLINE)" > $(ZIP_ROOT)/RECOVERY/cmdline
endif
ifdef BOARD_KERNEL_BASE
	$(hide) echo "$(BOARD_KERNEL_BASE)" > $(ZIP_ROOT)/RECOVERY/base
endif
ifdef BOARD_KERNEL_PAGESIZE
	$(hide) echo "$(BOARD_KERNEL_PAGESIZE)" > $(ZIP_ROOT)/RECOVERY/pagesize
endif
ifneq ($(IMGPKG), img)	
	$(hide) $(if $(TARGET_AMLOGIC_BOOTLOADER), \
		$(hide) mkdir -p $(ZIP_ROOT)/BOOTLOADER && \
		$(hide) $(ACP) $(TARGET_AMLOGIC_BOOTLOADER_NORAML) $(ZIP_ROOT)/BOOTLOADER/bootloader && \
		$(hide) $(ACP) $(TARGET_AMLOGIC_BOOTLOADER) $(IMAGES_OUT_DIR)/)
else
	$(hide) $(if $(TARGET_AMLOGIC_BOOTLOADER), \
		$(hide) mkdir -p $(ZIP_ROOT)/BOOTLOADER && \
		$(hide) $(ACP) $(AML_PACKAGE_BOOTLOADER)/u-boot.bin $(ZIP_ROOT)/BOOTLOADER/bootloader && \
		$(hide) $(ACP) $(TARGET_AMLOGIC_BOOTLOADER) $(IMAGES_OUT_DIR)/)
endif
	@# Logo resource component
	$(hide) mkdir -p $(ZIP_ROOT)/LOGO
ifneq ($(INSTALLED_AML_LOGO),)
	@cp $(INSTALLED_AML_LOGO) $(ZIP_ROOT)/LOGO/logo
endif
ifdef TARGET_AMLOGIC_AML_LOGO
	$(hide) $(ACP) $(TARGET_AMLOGIC_AML_LOGO) $(ZIP_ROOT)/LOGO/aml_logo
endif
ifdef TARGET_AMLOGIC_RESOURCE
	$(hide) mkdir -p $(ZIP_ROOT)/SYSTEM/resource
	$(hide) $(ACP) -rf $(TARGET_AMLOGIC_RESOURCE)/* $(ZIP_ROOT)/SYSTEM/resource
endif
ifdef TARGET_AMLOGIC_PARAM	
	$(hide) mkdir -p $(ZIP_ROOT)/PARAM	
	$(hide) $(ACP) -rf $(TARGET_AMLOGIC_PARAM) $(ZIP_ROOT)/PARAM/param
endif
ifdef INSTALLED_2NDBOOTLOADER_TARGET
	$(hide) $(ACP) \
		$(INSTALLED_2NDBOOTLOADER_TARGET) $(ZIP_ROOT)/BOOT/second
endif
ifdef BOARD_KERNEL_CMDLINE
	$(hide) echo "$(BOARD_KERNEL_CMDLINE)" > $(ZIP_ROOT)/BOOT/cmdline
endif
ifdef BOARD_KERNEL_BASE
	$(hide) echo "$(BOARD_KERNEL_BASE)" > $(ZIP_ROOT)/BOOT/base
endif
ifdef BOARD_KERNEL_PAGESIZE
	$(hide) echo "$(BOARD_KERNEL_PAGESIZE)" > $(ZIP_ROOT)/BOOT/pagesize
endif
	$(hide) $(foreach t,$(INSTALLED_RADIOIMAGE_TARGET),\
	            mkdir -p $(ZIP_ROOT)/RADIO; \
	            $(ACP) $(t) $(ZIP_ROOT)/RADIO/$(notdir $(t));)
	@# Components of the spi image
ifdef TARGET_AMLOGIC_SPI
	$(hide) mkdir -p $(ZIP_ROOT)/SPI
	$(hide) $(ACP) $(TARGET_AMLOGIC_SPI) $(ZIP_ROOT)/SPI/spi
endif
	$(hide) $(call package_files-copy-root, \
		$(TARGET_OUT_DATA),$(ZIP_ROOT)/DATA)
	@# Extra contents of the OTA package
	$(hide) mkdir -p $(ZIP_ROOT)/OTA
	$(hide) cp -rf $(built_ota_tools)/* $(ZIP_ROOT)/OTA/
	@# Files that do not end up in any images, but are necessary to
	@# build them.
	$(hide) mkdir -p $(ZIP_ROOT)/META
	$(hide) $(ACP) $(APKCERTS_FILE) $(ZIP_ROOT)/META/apkcerts.txt
	$(hide)	echo "$(PRODUCT_OTA_PUBLIC_KEYS)" > $(ZIP_ROOT)/META/otakeys.txt
	$(hide) echo "recovery_api_version=$(PRIVATE_RECOVERY_API_VERSION)" > $(ZIP_ROOT)/META/misc_info.txt
ifdef BOARD_FLASH_BLOCK_SIZE
	$(hide) echo "blocksize=$(BOARD_FLASH_BLOCK_SIZE)" >> $(ZIP_ROOT)/META/misc_info.txt
endif
ifdef BOARD_BOOTIMAGE_PARTITION_SIZE
	$(hide) echo "boot_size=$(BOARD_BOOTIMAGE_PARTITION_SIZE)" >> $(ZIP_ROOT)/META/misc_info.txt
endif
ifdef BOARD_RECOVERYIMAGE_PARTITION_SIZE
	$(hide) echo "recovery_size=$(BOARD_RECOVERYIMAGE_PARTITION_SIZE)" >> $(ZIP_ROOT)/META/misc_info.txt
endif
	$(hide) echo "tool_extensions=$(tool_extensions)" >> $(ZIP_ROOT)/META/misc_info.txt
	$(hide) echo "default_system_dev_certificate=$(DEFAULT_SYSTEM_DEV_CERTIFICATE)" >> $(ZIP_ROOT)/META/misc_info.txt
ifdef PRODUCT_EXTRA_RECOVERY_KEYS
	$(hide) echo "extra_recovery_keys=$(PRODUCT_EXTRA_RECOVERY_KEYS)" >> $(ZIP_ROOT)/META/misc_info.txt
endif
	$(hide) echo "mkbootimg_args= --second $(BOARD_MKBOOTIMG_ARGS)" >> $(ZIP_ROOT)/META/misc_info.txt
	$(call generate-userimage-prop-dictionary, $(ZIP_ROOT)/META/misc_info.txt)
	@# Zip everything up, preserving symlinks
	$(hide) (cd $(ZIP_ROOT) && zip -qry ../$(notdir $@) .)
	@# Run fs_config on all the system, boot ramdisk, and recovery ramdisk files in the zip, and save the output
	$(hide) zipinfo -1 $@ | awk 'BEGIN { FS="SYSTEM/" } /^SYSTEM\// {print "system/" $$2}' | $(HOST_OUT_EXECUTABLES)/fs_config > $(ZIP_ROOT)/META/filesystem_config.txt
	$(hide) zipinfo -1 $@ | awk 'BEGIN { FS="BOOT/RAMDISK/" } /^BOOT\/RAMDISK\// {print $$2}' | $(HOST_OUT_EXECUTABLES)/fs_config > $(ZIP_ROOT)/META/boot_filesystem_config.txt
	$(hide) zipinfo -1 $@ | awk 'BEGIN { FS="RECOVERY/RAMDISK/" } /^RECOVERY\/RAMDISK\// {print $$2}' | $(HOST_OUT_EXECUTABLES)/fs_config > $(ZIP_ROOT)/META/recovery_filesystem_config.txt
	$(hide) (cd $(ZIP_ROOT) && zip -q ../$(notdir $@) META/*filesystem_config.txt)
	@sync && cp -f $@ $(CURRENT_BUILT_TARGET_FILES_PACKAGE)

target-files-package: $(BUILT_TARGET_FILES_PACKAGE)

DEFAULT_KEY_CERT_PAIR := $(DEFAULT_SYSTEM_DEV_CERTIFICATE)
$(INTERNAL_OTA_PACKAGE_TARGET): KEY_CERT_PAIR := $(DEFAULT_KEY_CERT_PAIR)

ifeq ($(TARGET_BUILD_WIPE_USERDATA),false)
    wipeopt := 
else
    wipeopt := -w
endif # TARGET_BUILD_WIPE_USERDATA

ifeq ($(TARGET_BUILD_WIPE_SYSTEM),false)
    wipeopt += --no_wipe_system
endif

ifeq ($(TARGET_BUILD_OMIT_PREREQ), false)
	wipeopt += -n
endif

ifneq ($(TARGET_AMLOGIC_KERNEL),)
    amlogic_flag := --amlogic
else
    amlogic_flag :=
endif

RELEASE_TOOL_DIR := ./$(TOOLS_DIR)/android-utils/releasetools

ifeq ($(BASEVER), NULL)
ifeq ($(PRODUCT), dv6061_v6)
$(INTERNAL_OTA_PACKAGE_TARGET): $(BUILT_TARGET_FILES_PACKAGE) $(DISTTOOLS) 
	@echo "Package OTA: $@"
	./$(RELEASE_TOOL_DIR)/ota_from_target_files_6061 -v \
	   $(amlogic_flag) \
	   -p $(HOST_OUT_EXECUTABLES)/../ \
	   $(wipeopt) \
	   -k $(KEY_CERT_PAIR) \
	   $(BUILT_TARGET_FILES_PACKAGE) $@
else
$(INTERNAL_OTA_PACKAGE_TARGET): $(BUILT_TARGET_FILES_PACKAGE) $(DISTTOOLS) 
	@echo "Package OTA: $@"
	./$(RELEASE_TOOL_DIR)/ota_from_target_files -v \
	   $(amlogic_flag) \
	   -p $(HOST_OUT_EXECUTABLES)/../ \
	   $(wipeopt) \
	   -k $(KEY_CERT_PAIR) \
	   $(BUILT_TARGET_FILES_PACKAGE) $@
endif	

else # make incremental package
$(INTERNAL_OTA_PACKAGE_TARGET): $(BUILT_TARGET_FILES_PACKAGE) $(DISTTOOLS) 
	@echo "Package OTA: $@"
	./$(RELEASE_TOOL_DIR)/ota_from_target_files -v \
	   $(amlogic_flag) \
	   -i $(BASE_BUILT_TARGET_FILES_PACKAGE) \
	   -p $(HOST_OUT_EXECUTABLES)/../ \
	   $(wipeopt) \
	   -k $(KEY_CERT_PAIR) \
	   $(BUILT_TARGET_FILES_PACKAGE) $@
	   
endif

AML_IMAGE_DIR := $(ZIP_ROOT)/AML_IMAGE
PACKAGE_CONFIG_FILE := ./$(AML_PACKAGE_BOOTLOADER)/aml_upgrade_package.conf
$(IMG_PACKAGE_NAME): \
        $(INSTALLED_USERDATAIMAGE_TARGET) \
	$(INSTALLED_CACHEIMAGE_TARGET) \
        $(TARGET_USB_BURNING_V2_DEPEND_MODULES)
	@echo "Package Aml Image: $@"
	$(update-aml_upgrade-conf)
	@echo ./$(RELEASE_TOOL_DIR)/aml_image_v2_packer -r \
		$(PACKAGE_CONFIG_FILE) \
		$(AML_IMAGE_DIR)/ \
                $(IMG_PACKAGE_NAME)	

	@mkdir -p $(AML_IMAGE_DIR)
	@cp $(IMAGES_OUT_DIR)/*.img $(AML_IMAGE_DIR)
	@cp $(INSTALLED_AML_LOGO) $(AML_IMAGE_DIR)
	@cp -rf $(AML_PACKAGE_BOOTLOADER)/* $(AML_IMAGE_DIR)
	$(hide) ./$(RELEASE_TOOL_DIR)/aml_image_v2_packer -r \
                $(PACKAGE_CONFIG_FILE) \
                $(AML_IMAGE_DIR)/ \
                $(IMG_PACKAGE_NAME)		
	@echo " $@ installed"
	
get_args:
	$(hide) $(call print_parameters)
	$(hide) $(call check_make_args)
	@rm -rf $(CACHE_DIR)/*
	@mkdir -p $(IMAGES_OUT_DIR)
	@mkdir -p $(OTAPCAKGE_OUT_DIR)
	@mkdir -p $(BACKUP_OUT_DIR)
	@mkdir -p $(CACHE_DIR)
	@mkdir -p $(BACKUP_BASE_OTAPACKAGE_DIR)
	@rm -rf $(CACHE_DIR)/*
	$(hide) $(OTA_GEN_SYSINFO) -t $(PACKTYPE) -c $(PLATFORM_CONFIG) -v $(VERSION) -i $(BASEVER) -f$(INTERNAL_OTA_PACKAGE_TARGET) -o $(OTA_PACKAGE_NAME)
ifeq ($(PACKTYPE), bkrs)

TARGET_AMLOGIC_BOOTLOADER := $(TARGET_AMLOGIC_BOOTLOADER_NORAML)

OTA_PACKAGE_RELY_SRC : \
		$(TARGET_AMLOGIC_BOOTLOADER) \
		$(INSTALLED_BOOTIMAGE_TARGET) \
		$(INSTALLED_RECOVERYIMAGE_TARGET) \
		$(INSTALLED_SYSTEM_TARGET)

endif
ifeq ($(PACKTYPE), lnsys)
OTA_PACKAGE_RELY_SRC : \
		$(INSTALLED_BOOTIMAGE_TARGET) \
		$(INSTALLED_SYSTEM_TARGET)
endif
ifeq ($(PACKTYPE), incsys)
OTA_PACKAGE_RELY_SRC : \
		$(INSTALLED_SYSTEM_TARGET)
endif

# default use logo

.PHONY: otapackage
otapackage:droidcore dist_files $(INTERNAL_OTA_PACKAGE_TARGET)

distclean: clean
clean:
	@rm -rf ./cache
	@rm -rf ./out

ERR = $(error found an error!)
.PHONY: err
err: ; $(ERR)
