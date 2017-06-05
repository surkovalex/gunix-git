#!/bin/bash
# This script use to build images.

process_nums=`cat /proc/cpuinfo | egrep 'processor' | wc | awk '{print $1}'`

if [ $process_nums -gt 16 ]; then
	process_nums=16
fi

echo "process_nums = "$process_nums

if [ $process_nums -le 4 ]; then
	make_jobs=3
else
	make_jobs=$process_nums
fi

if [ $process_nums -le 4 ]; then
	uboot_make_jobs=1
else
	uboot_make_jobs=$process_nums
fi

#export TERMINAL_TEST=1

PEOJECT_NAME=OTT_DEFAULT
RELEASE_DIR=''
UBOOT_PRJ=NO
GHOST_SIZE=536870912
function usage()
{
	echo "Pelease run the script in android top directory"
	echo "Usage: $0 [mode] [options]"
	echo "Usage: $0 [mode] [options] <use antutu>"
	echo "       $0         help            ---> printf help information"
	echo "       $0 [mode]  all             ---> compile everything"
	echo "       $0 [mode]  all antutu      ---> compile everything with raise antutu score patch"

	echo "       $0 [mode]  uboot           ---> compile uboot"
	echo "       $0 [mode]  clean           ---> build clean"
	echo "          mode menu:"
	echo "          1: p212_iptv                 s905X	 platform with amlogic origin application"
	echo "          2: Megafon                   Megafon platform with Megafon application"
	
}


function build_env()
{
	echo $mode
	. build/envsetup.sh
	export UBOOT_PRJ=$UBOOT_PRJ_VALUE
}

function show_begin_time()
{
	echo "compile $1 begin, now time is: `date`"
}

function show_end_time()
{
	echo "compile $1 finished, now time is: `date`"
}

function comp_ota()
{
	show_begin_time otapackage
	build_env
	lunch $mode
	rm -rf out/target/product/$name/system/build.prop #delete this file make for syste to rebuild it.
	make otapackage -j${make_jobs}
	if [ $? -ne 0 ]; then
		echo "comp_ota result is $?"
		exit $?
	fi
	show_end_time otapackage
}

function comp_uboot()
{
	build_env
	cd uboot/
	#compile gxl uboot begin
	UBOOT_CONFIG=gxl_p212_v1_config
	make clean && make distclean
	make $UBOOT_CONFIG
	if [ $? -ne 0 ]; then
		echo "comp_uboot result is $?"
		exit $?
	fi
	make -j${uboot_make_jobs}
	if [ $? -ne 0 ]; then
		echo "comp_uboot result is $?"
		exit $?
	fi
	cp  fip/gxl/u-boot.bin ./../device/amlogic/$name/     
	cp  fip/gxl/u-boot.bin.usb.bl2 ./../device/amlogic/$name/upgrade/
	cp  fip/gxl/u-boot.bin.sd.bin  ./../device/amlogic/$name/upgrade/
	cp  fip/gxl/u-boot.bin.usb.tpl ./../device/amlogic/$name/upgrade/
	
	#compile gxl uboot end
	cd ../
	
}

function comp_all()
{
	comp_all_cmds=( \
		comp_uboot\
		comp_ota \
		comp_release \
    comp_ghost \
		)
	
	for cmd in ${comp_all_cmds[@]}; do
		echo "now cmd is $cmd"
		$cmd
		ret=$?
		echo "$cmd result is $ret"
		if [ $ret -ne 0 ]; then
			printf  "Error happens. $cmd failed....................\nError......\n"
			return
		fi
	done
	
	echo "Congratulations! Your compile is successfully done!!!!"
}

#mv the release file to release dir
function comp_release()
{
	show_begin_time comp_release
	
	output=out/target/product/$name/
	system_profile=out/target/product/$name/system/build.prop
	v_svn=`svn info | grep "Last Changed Rev:" | awk '{print $4}'`
	v_sw=`grep "ro.build.version.incremental" $output/system/build.prop | awk -F"=" '{print $2}'`
	v_hw=`grep "vender.hw.version" $output/system/build.prop | awk -F"=" '{print $2}'`
	profile_data_string=`grep 'ro.build.date=' $system_profile`
	profile_data_string_=${profile_data_string#ro.build.date=}
	v_date=`date -d "${profile_data_string_}" +%Y%m%d`
	v_time=`date -d "${profile_data_string_}" +%H%M`
	
	release_dir=$PEOJECT_NAME"_"H$v_hw"_"S$v_sw"_"SVN$v_svn"_"$v_date.$v_time
	signed_package=`find out/target/product/$name/ -maxdepth 1 -name "$name*.zip" | xargs ls -t | head -1`
	target_files_for_ota_patch=`find $output/obj/PACKAGING/target_files_intermediates -maxdepth 1 -name "$name*.zip" | xargs ls -t | head -1`
	echo target_files_for_ota_patch is $target_files_for_ota_patch
	
	echo the release dir is: $output/$release_dir
	RELEASE_DIR=$release_dir
	mkdir -p $output/$release_dir
	
	cp -rf  $output/recovery.img $output/$release_dir
	cp -rf  $output/u-boot.bin $output/$release_dir
	cp -rf  $output/dtb.img $output/$release_dir
	cp -rf  $target_files_for_ota_patch $output/$release_dir/$release_dir"_"src.zip
	cp -rf  $signed_package $output/$release_dir/$release_dir.zip
	cp -rf  $output/aml_upgrade_package.img $output/$release_dir/$release_dir"_".img
	show_end_time comp_release
}
#//add  by Gavin.Lei for the needing of back to factory 20150610 begin
function comp_ghost()
{
	show_begin_time comp_ghost
	cd $output/$release_dir
	var=`find ./ -maxdepth 1 -name "${name}""*.zip" | xargs ls -t | head -1`
	echo ghost src file is: $var
	echo step 1: unzip the ghost_dncrypt.zip to ghost_dncrypt_unzip
	unzip -n $var -d ghost_unzip
	echo step 2: mkdir ghost and copy file
	cd ghost_unzip
	mkdir ghost
	cp ../$var ghost
	cp ../recovery.img ghost
	echo step 3:edit updater-script and factory_update_param.aml
	cd ghost
	echo -e "--wipe_data\n"> factory_update_param.aml
	echo -e "--wipe_cache\n">> factory_update_param.aml
	echo -e "--wipe_media\n">> factory_update_param.aml
	echo -e "--update_package=/ghost/${var#*/}\n">> factory_update_param.aml
	sed -e '1,4s#./O#/O#' factory_update_param.aml>tmp;rm factory_update_param.aml;mv tmp factory_update_param.aml 
	cd ../META-INF/com/google/android/
	sed '4 iformat("ext4", "EMMC", "/dev/block/ghost", "0", "/ghost");\nmount("ext4", "EMMC", "/dev/block/ghost", "/ghost");\npackage_extract_dir("ghost", "/ghost");\n' updater-script >tmp;rm updater-script;mv tmp updater-script	
	echo step 4:zip the ghost_unzip
	cd ../../../../
	zip -r ../ghost_rezip.zip ./
	cd ../
	echo step 5:signature the ghost_unzip
	java -jar ../../../../../out/host/linux-x86/framework/signapk.jar -w ../../../../../build/target/product/security/testkey.x509.pem ../../../../../build/target/product/security/testkey.pk8 ./ghost_rezip.zip ghost_signed.zip
	echo step 6:encrypt the ghost_signed.zip
	cp -dpR ghost_signed.zip ghost.img
	echo step 7:clean the tmp file
        rm -rf ghost_unzip
	rm ghost_rezip.zip
	rm ghost_signed.zip
	#gen factory_update_param.aml script
	echo -e "--wipe_data\n"> factory_update_param.aml
	echo -e "--wipe_cache\n">> factory_update_param.aml
	echo -e "--wipe_media\n">> factory_update_param.aml
	echo -e "--update_package=/sdcard/ghost.img\n">> factory_update_param.aml
#	echo -e "--update_package=/sdcard/${release_dir}.zip\n">> factory_update_param.aml

	echo output file is ghost.img
        cd ../../../../..
	show_end_time comp_ghost
}
#add  by Gavin.Lei for the needing of back to factory 20150610 end

function comp_clean()
{
	show_begin_time comp_clean
  	top=$(pwd)
	build_env
	make clean
	svn revert $top/uboot $top/device/amlogic/$name/u-boot.bin $top/hardware/amlogic/nand/module/aml_nftl_dev.ko -R
	svn st uboot hardware | grep "?       " | xargs rm -rf $top/.ccache $top/v8.log $top/device/amlogic/$name/upgrade/u-boot.bin*
	show_end_time comp_clean
}
export SVN_INFO=`svn info | grep "Last Changed Rev:" | awk '{print $4}'`
echo SVN_INFO=$SVN_INFO

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
		mode=p212-userdebug-32
		PROJ_ID=p212
		UBOOT_CONFIG=gxl_p212_v1_config
		name=p212
		;;
	2)
		mode=Megafon-userdebug-32
		PROJ_ID=p212
		UBOOT_CONFIG=gxl_p212_v1_config
		name=Megafon
		UBOOT_PRJ_VALUE=Megafon
		PEOJECT_NAME=Megafon
		;;		
	
esac

case $2 in
	all)
		case $3 in
				antutu)
				top=$(pwd)
				patch -p0 < $top/antutu/antutu.patch
				if [ $? -ne 0 ]
				then
					echo "Error! The patch applied for raise antutu score is failed!!!"
					exit 1
				fi
				comp_all
				cd $top	
				patch -p0 -R < $top/antutu/antutu.patch
				if [ $? -ne 0 ]
				then
					echo "Error! Remove raise antutu score patch failed!!!"
					exit 1
				fi	
				;;
				*)
				comp_all	
					;;
		esac
		exit 0
		;;
		
	uboot)
		comp_uboot
		exit 0
		;;
	clean)
		comp_clean
		exit 0
		;;
	ota)
		comp_ota
		exit 0;
		;;
	facimg)
	        comp_factory_img
		exit 0;
		;;
esac
