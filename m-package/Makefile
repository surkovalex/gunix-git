#
# Creat to make otapackage on amlogic platform
#

define usage

	@echo "**********************************************************************************************"
	@echo " "
	@echo "* Summary: Firmware generater for amlogic platform"
	@echo "* Current version: 6.0"
	@echo "*	Reversion	Author	Reason	Date"
	@echo "*	s905x-6.0	Jimmy	Create	05-02-2017"
	@echo "	"
	@echo "* Usage:"
	@echo "* 	make c=[custmoer] p=[product] t=[package-type] v=[version] d=[odex mode] f=[factory mode]"
	@echo "	"
	@echo "* Example:"
	@echo "*	make c=normal p=dv8220 t=bkrs v=6.0.1 d=odex"
	@echo "	"
	@echo "* Customer-name: "
	@echo "*	normal  ..."
	@echo "* "
	@echo "* Product-name: "
	@echo "*	dv8220 : DDR_SIZE = 4*512M, EMMC_SIZE = 8192M"
	@echo "* "
	@echo "* Package-type:"
	@echo "*	logo		(logo)"
	@echo "*	incsys		(system)"
	@echo "*	lnxsys		(kernel and system)"
	@echo "*	lnxrecsys	(logo, kernel, recovery, system)"
	@echo "*	bkrs		(boot, logo, kernel, recovery, system)"
	@echo "* "
	@echo "* Version : fireware version"
	@echo "* "
	@echo "* odex mode: if d=odex ,it will odex optimize system, or it doesn't work "
	@echo "* "
	@echo "**********************************************************************************************"
	@echo
	exit 1
endef

define parse_parameters
$(shell if [ -z $(strip $(1)) ];then echo NULL;else echo $(strip $(1));fi)
endef

define print_parameters
	@echo "customer name : $(CUSTOMER)"
	@echo "product  type : $(PRODUCT)"
	@echo "package  type : $(PACKTYPE)"
	@echo "fw    version : $(VERSION)"
	@echo "odex     flag : $(ODEXFLAG)"
	@echo "Factory model : $(FACTORY)"
endef

define check_make_args
	$(hide) $(if $(findstring "$(PRODUCT)", "dv8220"),,\
		@echo "wrong product type : $(PRODUCT)"; $(call usage))
	$(hide) $(if $(findstring "$(PACKTYPE)", "bkrs" "lnxsys" "incsys" "logo"),,\
		@echo "wrong package type : $(PACKTYPE)"; $(call usage))
	$(hide) $(if $(findstring "$(CUSTOMER)", "normal"),,\
		@echo "wrong package type : $(CUSTOMER)"; $(call usage))
endef

# extract the make parameters
CUSTOMER := $(call parse_parameters, $(c))
PRODUCT  := $(call parse_parameters, $(p))
PACKTYPE := $(call parse_parameters, $(t))
VERSION  := $(call parse_parameters, $(v))
ODEXFLAG := $(call parse_parameters, $(d))
FACTORY  := $(call parse_parameters, $(f))

# declare global variables
PLATFORM_NAME := s905x-p212
HOST_OUT_EXECUTABLES := tools/android-utils/host/bin
MISC_TOOL_DIR := tools/android-utils/misc
SECURE_TOOL_DIR := tools/android-utils/security
ACP := $(HOST_OUT_EXECUTABLES)/acp

OUTPUT_DIR := out
CACHE_DIR := cache
ZIP_ROOT := $(CACHE_DIR)/target_files
IMAGES_OUT_DIR := $(OUTPUT_DIR)/images/$(PRODUCT)/$(CUSTOMER)

#
# make otapackage main entry
#
DATE=$(shell date +%y%m%d%H%M)
BUILT_TARGET_FILES_PACKAGE := $(CACHE_DIR)/$(PLATFORM_NAME)-ota-base-$(DATE).zip
INTERNAL_OTA_PACKAGE_TARGET := $(CACHE_DIR)/$(PLATFORM_NAME)-ota-$(DATE).zip
INSTALLED_AML_UPGRADE_PACKAGE_TARGET := $(IMAGES_OUT_DIR)/$(PLATFORM_NAME)-$(PRODUCT)-$(CUSTOMER)-v$(VERSION)-$(DATE).img
OTA_PACKAGE_NAME = $(IMAGES_OUT_DIR)/$(PLATFORM_NAME)-$(PRODUCT)-$(CUSTOMER)-v$(VERSION)-$(DATE).zip

$(OTA_PACKAGE_NAME): get_args $(INTERNAL_OTA_PACKAGE_TARGET) $(INSTALLED_AML_UPGRADE_PACKAGE_TARGET) 
	@echo "\nmaking package, pls wait ...\n"
	@cp $(INTERNAL_OTA_PACKAGE_TARGET) $@

.PHONY: make_ota_package
make_ota_package:$(OTA_PACKAGE_NAME)

#
# build boot and recovery 
#
KERNEL_DIR = ./kernel
INSTALLED_KERNEL_TARGET = $(KERNEL_DIR)/kernel
INSTALLED_BOARDDTB_TARGET = ./$(KERNEL_DIR)/dts/dtb.img
BOARD_KERNEL_OFFSET = 0x1080000
BOARD_KERNEL_BASE = 0x0
MKBOOTFS = $(HOST_OUT_EXECUTABLES)/mkbootfs
MKBOOTIMG = $(HOST_OUT_EXECUTABLES)/mkbootimg
MINIGZIP = $(HOST_OUT_EXECUTABLES)/minigzip
#
# build boot.img
#
TARGET_BOOT_DIR = $(ZIP_ROOT)/BOOT
INSTALLED_BOOTIMAGE_TARGET = $(CACHE_DIR)/boot.img
BOOT_RAMDISK = $(KERNEL_DIR)/ramdisk/root.tar.bz2
$(INSTALLED_BOOTIMAGE_TARGET) : $(BOOT_RAMDISK) $(MKBOOTIMG) $(MINIGZIP) $(MKBOOTFS) $(INSTALLED_KERNEL_TARGET)
	@mkdir -p $(TARGET_BOOT_DIR)
	tar -jxf $< -C $(TARGET_BOOT_DIR)/
	@mv $(TARGET_BOOT_DIR)/root $(TARGET_BOOT_DIR)/RAMDISK
	@cp -f $(INSTALLED_KERNEL_TARGET) $(TARGET_BOOT_DIR)/kernel
	$(hide) $(MKBOOTFS) $(TARGET_BOOT_DIR)/RAMDISK | $(MINIGZIP) > $(CACHE_DIR)/ramdisk.img
	$(hide) $(MKBOOTIMG) --kernel $(INSTALLED_KERNEL_TARGET) --base 0x0 --kernel_offset 0x1080000 --second $(INSTALLED_BOARDDTB_TARGET) --kernel_offset 0x1080000 --ramdisk $(CACHE_DIR)/ramdisk.img --output $@
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
RECOVERY_RAMDISK := $(KERNEL_DIR)/ramdisk/root-recovery.tar.bz2
$(INSTALLED_RECOVERYIMAGE_TARGET) : $(RECOVERY_RAMDISK) $(MKBOOTIMG) $(MINIGZIP) $(MKBOOTFS) $(INSTALLED_KERNEL_TARGET)
	@mkdir -p $(TARGET_RECOVERY_DIR)
	tar -jxf $< -C $(TARGET_RECOVERY_DIR)/
	@mv $(TARGET_RECOVERY_DIR)/root $(TARGET_RECOVERY_DIR)/RAMDISK
	@cp -f $(INSTALLED_KERNEL_TARGET) $(TARGET_RECOVERY_DIR)/kernel
	$(hide) $(MKBOOTFS) $(TARGET_RECOVERY_DIR)/RAMDISK | $(MINIGZIP) > $(INSTALLED_AMLOGIC_RECOVERY_TARGET)
	$(hide) $(MKBOOTIMG) --kernel $(INSTALLED_KERNEL_TARGET) --base 0x0 --kernel_offset 0x1080000 --second $(INSTALLED_BOARDDTB_TARGET) --ramdisk $(INSTALLED_AMLOGIC_RECOVERY_TARGET) --output $@
	@mv $@ $(IMAGES_OUT_DIR)/
	@rm -f $(INSTALLED_AMLOGIC_RECOVERY_TARGET)
.PHONY: installrecovery
installrecovery: $(INSTALLED_RECOVERYIMAGE_TARGET)

#
# build system
#
ODEX_OUT_DIR := $(OUTPUT_DIR)/target/product/p212
CUSTOMER_DIR := platform/$(PRODUCT)/$(CUSTOMER)
CUSTOMISZED_DATA_DIR := $(CUSTOMER_DIR)/customized_data
FRAMWORK := s905x-system.tar.bz2
INSTALLED_SYSTEM_TARGET := $(ZIP_ROOT)/SYSTEM
CURRENT_DIR := $(shell pwd)
$(INSTALLED_SYSTEM_TARGET): $(FRAMWORK)
	@echo "" && echo "decompressing framework, pls wait ..." && echo ""
	@tar -jxf $< -C $(ZIP_ROOT)
	@mv $(ZIP_ROOT)/system $@
	@echo "$(CUSTOMER_DIR)"
#	@sh $(CUSTOMER_DIR)/build.sh "$@" "$(CUSTOMER_DIR)" "$(FACTORY)" "$(VERSION)"
	@# try to backup customer data
	$(hide) cd $(CUSTOMISZED_DATA_DIR)/ && tar cvf $(CURRENT_DIR)/$@/customized_data.tar *
ifeq ($(ODEXFLAG), odex)
	@mkdir -p $(ODEX_OUT_DIR)/system/ && rm -rf $(ODEX_OUT_DIR)/system/*
	@mv $@/framework $(ODEX_OUT_DIR)/system/
	@mv $@/app       $(ODEX_OUT_DIR)/system/
	@sync && sh $(MISC_TOOL_DIR)/odex-optimize "$(PWD)" && sync
	@mv $(ODEX_OUT_DIR)/system/framework $@/
	@mv $(ODEX_OUT_DIR)/system/app       $@/
	@sync
	@# remove tmp dir 
	@rm -rf $(OUTPUT_DIR)/target
endif
	@./tools/android-utils/host/bin/mkuserimg.sh -s $(INSTALLED_SYSTEM_TARGET) $(IMAGES_OUT_DIR)/system.img ext4 system $(BOARD_SYSTEMIMAGE_PARTITION_SIZE) $(TARGET_BOOT_DIR)/RAMDISK/file_contexts

.PHONY: installsystem
installsystem : $(INSTALLED_SYSTEM_TARGET)


# apk certs file
APKCERTS_FILE := $(SECURE_TOOL_DIR)/apkcerts.txt

#
# build ota tools
#
TARGET_BUILD_OMIT_PREREQ := false
built_ota_tools := ./tools/android-utils/target
BOOTLOGO = ./platform/$(PRODUCT)/$(CUSTOMER)/boot-logo/logo.bmp
IMGPACK = $(HOST_OUT_EXECUTABLES)/logo_img_packer
TARGET_ROOT_OUT := $(ZIP_ROOT)/BOOT/RAMDISK

#TARGET_AMLOGIC_RES_PACKAGE := $(dir $(BOOTLOGO))/../res_pack
TARGET_AMLOGIC_RES_PACKAGE := $(dir $(BOOTLOGO))
PRIVATE_RECOVERY_API_VERSION := 3
BOARD_FLASH_BLOCK_SIZE := 4096
PRIVATE_RECOVERY_FSTAB_VERSION := 2
DEFAULT_TARGET_RECOVERY_FSTYPE_MOUNT_OPTIONS := ext4=max_batch_time=0,commit=1,data=ordered,barrier=1,errors=panic,nodelalloc
ifeq ($(TARGET_RELEASETOOLS_EXTENSIONS),)
# default to common dir for device vendor
$(BUILT_TARGET_FILES_PACKAGE): tool_extensions := $(CACHE_DIR)/common
else
$(BUILT_TARGET_FILES_PACKAGE): tool_extensions := $(TARGET_RELEASETOOLS_EXTENSIONS)
endif

DEFAULT_SYSTEM_DEV_CERTIFICATE := $(SECURE_TOOL_DIR)/testkey
INTERNAL_USERIMAGES_EXT_VARIANT := ext4
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 1073741824
BOARD_USERDATAIMAGE_PARTITION_SIZE := 576716800
BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_CACHEIMAGE_PARTITION_SIZE := 69206016
INTERNAL_USERIMAGES_SPARSE_EXT_FLAG := -s
SELINUX_FC := $(TARGET_ROOT_OUT)/file_contexts
BOARD_MKBOOTIMG_ARGS := --second $(INSTALLED_BOARDDTB_TARGET)

# $(1): the path of the output dictionary file
define generate-userimage-prop-dictionary
$(if $(INTERNAL_USERIMAGES_EXT_VARIANT),$(hide) echo "fs_type=$(INTERNAL_USERIMAGES_EXT_VARIANT)" >> $(1))
$(if $(BOARD_SYSTEMIMAGE_PARTITION_SIZE),$(hide) echo "system_size=$(BOARD_SYSTEMIMAGE_PARTITION_SIZE)" >> $(1))
$(if $(BOARD_USERDATAIMAGE_PARTITION_SIZE),$(hide) echo "userdata_size=$(BOARD_USERDATAIMAGE_PARTITION_SIZE)" >> $(1))
$(if $(BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE),$(hide) echo "cache_fs_type=$(BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE)" >> $(1))
$(if $(BOARD_CACHEIMAGE_PARTITION_SIZE),$(hide) echo "cache_size=$(BOARD_CACHEIMAGE_PARTITION_SIZE)" >> $(1))
$(if $(INTERNAL_USERIMAGES_SPARSE_EXT_FLAG),$(hide) echo "extfs_sparse_flag=$(INTERNAL_USERIMAGES_SPARSE_EXT_FLAG)" >> $(1))
$(if $(mkyaffs2_extra_flags),$(hide) echo "mkyaffs2_extra_flags=$(mkyaffs2_extra_flags)" >> $(1))
$(hide) echo "selinux_fc=$(SELINUX_FC)" >> $(1)
endef

ifneq ($(TARGET_AMLOGIC_RES_PACKAGE),)
INSTALLED_AML_LOGO := $(IMAGES_OUT_DIR)/logo.img
$(INSTALLED_AML_LOGO): $(IMGPACK)
	@echo
	@echo "generate $(INSTALLED_AML_LOGO)"
	@echo
	$(IMGPACK) -r $(TARGET_AMLOGIC_RES_PACKAGE) $(INSTALLED_AML_LOGO)
else
INSTALLED_AML_LOGO :=
endif

#INSTALLED_AML_DATA := ./data/backtrace_test
INSTALLED_AML_DTB := $(INSTALLED_BOARDDTB_TARGET)

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
	$(hide) $(ACP) $(INSTALLED_2NDBOOTLOADER_TARGET) $(ZIP_ROOT)/RECOVERY/second
endif

ifdef INSTALLED_BOARDDTB_TARGET
	$(hide) $(ACP) $(INSTALLED_BOARDDTB_TARGET) $(ZIP_ROOT)/RECOVERY/second
endif

ifdef INSTALLED_KERNEL_TARGET
	$(hide) $(ACP) $(INSTALLED_KERNEL_TARGET) $(ZIP_ROOT)/RECOVERY/kernel
endif

ifdef BOARD_KERNEL_CMDLINE
	$(hide) echo "$(BOARD_KERNEL_CMDLINE)" > $(ZIP_ROOT)/RECOVERY/cmdline
endif

ifdef BOARD_KERNEL_BASE
	$(hide) echo "$(BOARD_KERNEL_BASE)" > $(ZIP_ROOT)/RECOVERY/base
endif

ifdef BOARD_KERNEL_OFFSET
	$(hide) echo "$(BOARD_KERNEL_OFFSET)" > $(ZIP_ROOT)/RECOVERY/kernel_offset
endif

ifdef BOARD_KERNEL_PAGESIZE
	$(hide) echo "$(BOARD_KERNEL_PAGESIZE)" > $(ZIP_ROOT)/RECOVERY/pagesize
endif
	$(hide) $(if $(TARGET_AMLOGIC_BOOTLOADER), \
	$(hide) mkdir -p $(ZIP_ROOT)/BOOTLOADER && \
	$(hide) $(ACP) $(TARGET_AMLOGIC_BOOTLOADER) $(ZIP_ROOT)/BOOTLOADER/bootloader &&\
	$(hide) $(ACP) $(TARGET_AMLOGIC_BOOTLOADER) $(IMAGES_OUT_DIR)/u-boot.bin)
	$(hide) mkdir -p $(ZIP_ROOT)/LOGO

ifneq ($(INSTALLED_AML_LOGO),)
	@cp $(INSTALLED_AML_LOGO) $(ZIP_ROOT)/LOGO/logo
endif

ifneq ($(INSTALLED_AML_DTB),)
	$(hide) mkdir -p $(ZIP_ROOT)/DTB/
	@cp $(INSTALLED_AML_DTB) $(ZIP_ROOT)/DTB/dtb
endif

ifneq ($(INSTALLED_AML_DATA),)
	$(hide) mkdir -p $(ZIP_ROOT)/DATA/nativetest/backtrace_test
	@cp $(INSTALLED_AML_DATA) $(ZIP_ROOT)/DATA/nativetest/backtrace_test
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
	$(hide) $(ACP) $(INSTALLED_2NDBOOTLOADER_TARGET) $(ZIP_ROOT)/BOOT/second
endif
ifdef INSTALLED_BOARDDTB_TARGET
	$(hide) $(ACP) $(INSTALLED_BOARDDTB_TARGET) $(ZIP_ROOT)/BOOT/second
endif
ifdef INSTALLED_KERNEL_TARGET
	$(hide) $(ACP) $(INSTALLED_KERNEL_TARGET) $(ZIP_ROOT)/BOOT/kernel
endif
ifdef BOARD_KERNEL_OFFSET
	$(hide) echo "$(BOARD_KERNEL_OFFSET)" > $(ZIP_ROOT)/BOOT/kernel_offset
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
ifdef PRIVATE_RECOVERY_FSTAB_VERSION
	$(hide) echo "fstab_version=$(PRIVATE_RECOVERY_FSTAB_VERSION)" >> $(ZIP_ROOT)/META/misc_info.txt
endif	
ifdef BOARD_FLASH_BLOCK_SIZE
	$(hide) echo "blocksize=$(BOARD_FLASH_BLOCK_SIZE)" >> $(ZIP_ROOT)/META/misc_info.txt
endif
ifdef TARGET_RECOVERY_FSTYPE_MOUNT_OPTIONS
	@# TARGET_RECOVERY_FSTYPE_MOUNT_OPTIONS can be empty to indicate that nothing but defaults should be used.
	$(hide) echo "recovery_mount_options=$(TARGET_RECOVERY_FSTYPE_MOUNT_OPTIONS)" >> $(ZIP_ROOT)/META/misc_info.txt
else
	$(hide) echo "recovery_mount_options=$(DEFAULT_TARGET_RECOVERY_FSTYPE_MOUNT_OPTIONS)" >> $(ZIP_ROOT)/META/misc_info.txt
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
#	$(hide) echo "mkbootimg_args=$(BOARD_MKBOOTIMG_ARGS)" >> $(ZIP_ROOT)/META/misc_info.txt
	$(hide) echo "use_set_metadata=1" >> $(ZIP_ROOT)/META/misc_info.txt
	$(hide) echo "multistage_support=1" >> $(ZIP_ROOT)/META/misc_info.txt
	$(hide) echo "update_rename_support=1" >> $(ZIP_ROOT)/META/misc_info.txt
	$(hide) echo "blockimgdiff_versions=1,2,3" >> $(ZIP_ROOT)/META/misc_info.txt
	$(call generate-userimage-prop-dictionary, $(ZIP_ROOT)/META/misc_info.txt)
	$(hide) ./tools/android-utils/releasetools/make_recovery_patch $(ZIP_ROOT) $(ZIP_ROOT)
	$(hide) cp ./tools/android-utils/releasetools/releasetools.py $(ZIP_ROOT)/META/
	@# Zip everything up, preserving symlinks
	$(hide) (cd $(ZIP_ROOT) && zip -qry ../$(notdir $@) .)
	@# Run fs_config on all the system, boot ramdisk, and recovery ramdisk files in the zip, and save the output
	$(hide) zipinfo -1 $@ | awk 'BEGIN { FS="SYSTEM/" } /^SYSTEM\// {print "system/" $$2}' | $(HOST_OUT_EXECUTABLES)/fs_config -C -S $(SELINUX_FC) > $(ZIP_ROOT)/META/filesystem_config.txt
	$(hide) zipinfo -1 $@ | awk 'BEGIN { FS="VENDOR/" } /^VENDOR\// {print "vendor/" $$2}' | $(HOST_OUT_EXECUTABLES)/fs_config -C -S $(SELINUX_FC) > $(ZIP_ROOT)/META/vendor_filesystem_config.txt
	$(hide) zipinfo -1 $@ | awk 'BEGIN { FS="BOOT/RAMDISK/" } /^BOOT\/RAMDISK\// {print $$2}' | $(HOST_OUT_EXECUTABLES)/fs_config -C -S $(SELINUX_FC) > $(ZIP_ROOT)/META/boot_filesystem_config.txt
	$(hide) zipinfo -1 $@ | awk 'BEGIN { FS="RECOVERY/RAMDISK/" } /^RECOVERY\/RAMDISK\// {print $$2}' | $(HOST_OUT_EXECUTABLES)/fs_config -C -S $(SELINUX_FC) > $(ZIP_ROOT)/META/recovery_filesystem_config.txt
	$(hide) (cd $(ZIP_ROOT) && zip -q ../$(notdir $@) META/*filesystem_config.txt)
	$(hide) ./tools/android-utils/releasetools/add_img_to_target_files -p ./tools/android-utils/host/ $@

target-files-package: $(BUILT_TARGET_FILES_PACKAGE)

DEFAULT_KEY_CERT_PAIR := $(DEFAULT_SYSTEM_DEV_CERTIFICATE)
$(INTERNAL_OTA_PACKAGE_TARGET): KEY_CERT_PAIR := $(DEFAULT_KEY_CERT_PAIR)

TARGET_BUILD_WIPE_USERDATA := false
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

RELEASE_TOOL_DIR := ./tools/android-utils/releasetools

$(INTERNAL_OTA_PACKAGE_TARGET): $(BUILT_TARGET_FILES_PACKAGE) $(DISTTOOLS)
	@echo "Package OTA: $@"
	./$(RELEASE_TOOL_DIR)/ota_from_target_files -v --block --dtb \
	   $(wipeopt) \
	   -p $(HOST_OUT_EXECUTABLES)/../ \
	   -k $(KEY_CERT_PAIR) \
	   $(BUILT_TARGET_FILES_PACKAGE) $@
    
AML_PACKAGE_BOOTLOADER := bootloader/upgrade
AML_IMAGE_DIR := $(ZIP_ROOT)/AML_IMAGE
PACKAGE_CONFIG_FILE := $(AML_IMAGE_DIR)/aml_upgrade_package.conf
$(INSTALLED_AML_UPGRADE_PACKAGE_TARGET): \
        $(INSTALLED_USERDATAIMAGE_TARGET) \
	$(INSTALLED_CACHEIMAGE_TARGET) \
        $(TARGET_USB_BURNING_V2_DEPEND_MODULES)
	@echo "Package Aml Image: $@"
	$(update-aml_upgrade-conf)
	@echo ./tools/aml_upgrade/aml_image_v2_packer -r \
		$(PACKAGE_CONFIG_FILE) \
		$(AML_IMAGE_DIR)/ \
		$(INSTALLED_AML_UPGRADE_PACKAGE_TARGET)	

	@mkdir -p $(AML_IMAGE_DIR)
	@cp $(IMAGES_OUT_DIR)/boot.img $(AML_IMAGE_DIR)
	@cp $(IMAGES_OUT_DIR)/recovery.img $(AML_IMAGE_DIR)
	@cp $(IMAGES_OUT_DIR)/system.img $(AML_IMAGE_DIR)
	@cp -rf $(AML_PACKAGE_BOOTLOADER)/* $(AML_IMAGE_DIR)
	@cp -rf $(INSTALLED_AML_LOGO) $(AML_IMAGE_DIR)	
	$(hide) ./tools/aml_upgrade/aml_image_v2_packer -r \
                $(PACKAGE_CONFIG_FILE) \
                $(AML_IMAGE_DIR)/ \
                $(INSTALLED_AML_UPGRADE_PACKAGE_TARGET)
#	@rm -rf $(AML_IMAGE_DIR)
	@echo " $@ installed"
	
get_args:
	$(hide) $(call print_parameters)
	$(hide) $(call check_make_args)
	@mkdir -p $(IMAGES_OUT_DIR)
	@mkdir -p $(CACHE_DIR)
	@rm -rf $(CACHE_DIR)/*
	@rm -rf $(IMAGES_OUT_DIR)/*

ifeq ($(PACKTYPE), bkrs)
TARGET_AMLOGIC_BOOTLOADER := $(AML_PACKAGE_BOOTLOADER)/u-boot.bin
OTA_PACKAGE_RELY_SRC : \
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
otapackage: droidcore dist_files $(INTERNAL_OTA_PACKAGE_TARGET)

distclean: clean
clean:
	@rm -rf ./cache
	@rm -rf ./out

ERR = $(error found an error!)
.PHONY: err
err: ; $(ERR)
