#!/bin/bash
# This script is used to build images.
# Please run this script on android top directory.
# Any problem, please let me know.

set -e

UBOOT_CONFIG_P212=gxl_p212_v1
UBOOT_CONFIG_Q200=gxm_q200_v1
UBOOT_CONFIG_Q201=gxm_q201_v1
UBOOT_CONFIG_SDMC_NORMAL=gxm_sdmc_normal_v1


function usage()
{
	echo ""
	echo "please run this script in android top directory"
	echo "Usage:  $0 [platform] [opts]	[descriptions]"
	echo "	$0 help"
	echo "	$0 [platform] all       	-----> compile everything"
	echo "	$0 [platform] uboot     	-----> compile uboot"
	echo "	$0 [platform] img       	-----> compile imgpackage"
	echo "	$0 [platform] ota       	-----> compile imgpackage and otapackage"
	echo "	$0 [platform] bootimg   	-----> compile bootimg"
	echo "	$0 [platform] recovery  	-----> compile recoveryimage"
	echo "	$0 [platform] menuconfig	-----> make menuconfig"
	echo "	$0 [platform] saveconfig	-----> save menuconfig"
	echo "		platform menu:"
	echo "			1: p212     	p212 platform for s905x chip"
	echo "			2: q200     	q200 platform for s912 chip"
	echo "			3: q201	        q201 platform for s912 chip"
	echo "			4: q201_9377	q201_9377 platform for s912 chip"
	echo "			5: sdmc_normal	sdmc_normal platform for s912 chip"
	echo ""
}


function build_env()
{
	echo $mode
	. build/envsetup.sh
	lunch $mode
}


function show_begin_time()
{
	echo "compile $1 begin, now time is: `date`"
}


function show_end_time()
{
	echo "compile $1 finished, now time is: `date`"
}


function comp_uboot()
{
	show_begin_time uboot
	cd uboot
	./mk $UBOOT_CONFIG
	cp fip/gxl/u-boot.bin ../device/amlogic/$name/
	cp fip/gxl/u-boot.bin.usb.bl2 ../device/amlogic/$name/upgrade/
	cp fip/gxl/u-boot.bin.usb.tpl ../device/amlogic/$name/upgrade/
	cp fip/gxl/u-boot.bin.sd.bin ../device/amlogic/$name/upgrade/
	cd ..
	show_end_time uboot
}


function clean_uboot()
{
	cd uboot
	make distclean
	cd ..
}


function comp_ota()
{
	show_begin_time otapackage
	build_env
	make otapackage -j12
	show_end_time otapackage
}


function comp_img()
{
	show_begin_time images
	build_env
	make -j8
	show_end_time images
}


function comp_all()
{
	comp_uboot
	comp_ota
}


function comp_bootimg()
{
	build_env
	device/amlogic/common/quick_build_kernel.sh bootimage
}


function comp_recoveryimg()
{
	build_env
	device/amlogic/common/quick_build_kernel.sh recoveryimage
}


function comp_menuconfig()
{
	build_env
	device/amlogic/common/quick_build_kernel.sh menuconfig
}


function comp_saveconfig()
{
	build_env
	device/amlogic/common/quick_build_kernel.sh savedefconfig
}


if [ $# -lt 1 ]; then
	echo "Error: wrong number of arguments in cmd: $0 $* "
	usage
	exit 1
fi


case $1 in
	help)
		usage
		exit 0
		;;
	
	1)
		mode=p212-user-32
		UBOOT_CONFIG=$UBOOT_CONFIG_P212
		name=p212
		;;
	
	2)
		mode=q200-user-32
		UBOOT_CONFIG=$UBOOT_CONFIG_Q200
		name=q200
		;;
	
	3)
		mode=q201-user-32
		UBOOT_CONFIG=$UBOOT_CONFIG_Q201
		name=q201
		;;
	
	4)
		mode=q201_9377-user-32
		UBOOT_CONFIG=$UBOOT_CONFIG_Q201
		name=q201_9377
		;;
	
	5)
		mode=sdmc_normal-user-32
		UBOOT_CONFIG=$UBOOT_CONFIG_SDMC_NORMAL
		name=sdmc_normal
		;;
	
	*)
		echo "Error: wrong parameters!"
		usage;
		exit 1
		;;
esac


case $2 in
	all)
		comp_all
		exit 0
		;;

	uboot)
		comp_uboot
		exit 0
		;;

	cleanuboot)
		clean_uboot
		exit 0
		;;

	img)
		comp_img
		exit 0
		;;

	ota)
		comp_ota
		exit 0
		;;

	bootimg)
		comp_bootimg
		exit 0
		;;

	recovery)
		comp_recoveryimg
		exit 0
		;;

	menuconfig)
		comp_menuconfig
		exit 0
		;;

	saveconfig)
		comp_saveconfig
		exit 0
		;;
	
	buildenv)
		build_env;
		exit 0
		;;
esac

