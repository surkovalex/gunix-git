#!/bin/bash

SYSTEM_DIR=$1
CURRENT_DIR=$2
FACTORY=$3
VERSION=$4
APP=app
PRIV_APP=priv-app
ICS_REMOVE_UNUSED_PACKAGE=false
JB_REMOVE_UNUSED_PACKAGE=true
CUSTOM_NEED_CUBER=false
CUSTOM_NEED_GAPPS=true
PRIV_REMOVE_PACKAGE=true

CONTEXT_DIR=$CURRENT_DIR/private.system

BUILD_NAME="Normal-"
BUILD_VERSION="$VERSION"
BUILD_DATE="-`date +%Y%m%d`"
BUILD_ID="$BUILD_NAME$BUILD_VERSION$BUILD_DATE"
echo "ro.build.id=$BUILD_ID" > $CONTEXT_DIR/tmp.prop
cat $CONTEXT_DIR/build_device.prop >> $CONTEXT_DIR/tmp.prop

echo "CURRENT_DIR is $CURRENT_DIR"
echo "CONTEXT_DIR is $CONTEXT_DIR"
echo "SYSTEM_DIR is $SYSTEM_DIR"

cp -rf $CONTEXT_DIR/tmp.prop $SYSTEM_DIR/build_device.prop
cp -rf $CONTEXT_DIR/app/* $SYSTEM_DIR/app
cp -rf $CONTEXT_DIR/lib/* $SYSTEM_DIR/lib
cp -rf $CONTEXT_DIR/etc/* $SYSTEM_DIR/etc
mv $SYSTEM_DIR/etc/Vendor_0001_Product_0001.kl $SYSTEM_DIR/usr/keylayout/
cp -rf $CONTEXT_DIR/media/* $SYSTEM_DIR/media
cp -rf $CONTEXT_DIR/usr/* $SYSTEM_DIR/usr
cp -rf $CONTEXT_DIR/xbin/* $SYSTEM_DIR/xbin
cp -rf $CONTEXT_DIR/bin/* $SYSTEM_DIR/bin
cp -rf $CURRENT_DIR/device_init.sh $SYSTEM_DIR/bin


if [ "$CUSTOM_NEED_GAPPS" = "true" ] ;then
	echo "install google apps..."
	cp -rf $CONTEXT_DIR/google/* $SYSTEM_DIR/
fi

if [ "$CUSTOM_NEED_CUBER" = "true" ] ;then
	echo "install cuber launcher..."
	rm -rf $SYSTEM_DIR/app/Launcher2.*
	rm -rf $SYSTEM_DIR/app/sdmc_signed.*
	cp -rf $CONTEXT_DIR/CuberLauncher/app/* $SYSTEM_DIR/app
	cp -rf $CONTEXT_DIR/CuberLauncher/etc/* $SYSTEM_DIR/etc
	cp -rf $CONTEXT_DIR/CuberLauncher/lib/* $SYSTEM_DIR/lib
fi

if [ "$FACTORY" = "yes" ] ;then
	echo "install factory info files..."
	cp -rf $CONTEXT_DIR/factory_info/* $SYSTEM_DIR/
fi

if [ "$JB_REMOVE_UNUSED_PACKAGE" = "true" ] ;then
	echo "remove jelly bean unused apks ..."
	rm -rf $SYSTEM_DIR/app/Calculator.*
	rm -rf $SYSTEM_DIR/app/Calendar.*
	rm -rf $SYSTEM_DIR/app/CalendarProvider.*
	rm -rf $SYSTEM_DIR/app/DeskClock.*
	rm -rf $SYSTEM_DIR/app/Development.*
	rm -rf $SYSTEM_DIR/app/Email.*
	rm -rf $SYSTEM_DIR/app/dongle_launcher.*
	rm -rf $SYSTEM_DIR/app/Galaxy4.*
	rm -rf $SYSTEM_DIR/app/OTAUpgrade.*
	rm -rf $SYSTEM_DIR/app/RC_Server.*
	rm -rf $SYSTEM_DIR/app/SoundRecorder.*
	rm -rf $SYSTEM_DIR/app/SpeechRecorder.*
	rm -rf $SYSTEM_DIR/app/Update.*
	rm -rf $SYSTEM_DIR/app/MusicFX.*
	rm -rf $SYSTEM_DIR/app/Samba.*
	rm -rf $SYSTEM_DIR/app/Gallery2.*
	rm -rf $SYSTEM_DIR/app/OOBE.*
	rm -rf $SYSTEM_DIR/app/Phone.*
	rm -rf $SYSTEM_DIR/app/PPPoE.*
	rm -rf $SYSTEM_DIR/app/QuickSearchBox.*
	rm -rf $SYSTEM_DIR/app/OpenWnn.*
	rm -rf $SYSTEM_DIR/app/RemoteIME.*
	rm -rf $SYSTEM_DIR/app/PicturePlayer.*
	rm -rf $SYSTEM_DIR/app/Camera2.*
	rm -rf $SYSTEM_DIR/app/TelephonyProvider.*
fi

if [ "$ICS_REMOVE_UNUSED_PACKAGE" = "true" ]; then
	echo "remove unused apks ..."
	rm -rf $SYSTEM_DIR/app/Aml2DLauncher_mbx.*
	rm -rf $SYSTEM_DIR/app/Camera.*
	rm -rf $SYSTEM_DIR/app/Calendar.*
	rm -rf $SYSTEM_DIR/app/Contacts.*
	rm -rf $SYSTEM_DIR/app/Gallery2.*
	rm -rf $SYSTEM_DIR/app/DeskClock.*
	rm -rf $SYSTEM_DIR/app/MusicPlayer.*
	rm -rf $SYSTEM_DIR/app/OOBE.*
	rm -rf $SYSTEM_DIR/app/Phone.*
	rm -rf $SYSTEM_DIR/app/PPPoE.*
	rm -rf $SYSTEM_DIR/app/Samba.*
	rm -rf $SYSTEM_DIR/app/Update.*
	rm -rf $SYSTEM_DIR/app/PicturePlayer.*
	rm -rf $SYSTEM_DIR/app/SoftMediaPlayerVer.*
	rm -rf $SYSTEM_DIR/app/sdmc_2.3.*
	rm -rf $SYSTEM_DIR/app/launcher_work1.*
fi

if [ "$PRIV_REMOVE_PACKAGE" = "true" ]; then
	echo "remove unused private apks ..."
	rm -rf $SYSTEM_DIR/$PRIV_APP/Contacts.*
	rm -rf $SYSTEM_DIR/$PRIV_APP/ContactsProvider.*
fi
echo "removed and copy finish ..."
