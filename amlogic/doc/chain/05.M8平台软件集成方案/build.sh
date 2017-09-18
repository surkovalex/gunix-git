#!/bin/bash
#set -x

SYSTEM_DIR=$1
CURRENT_DIR=$2
FACTORY=$3
VERSION=$4
PLATFORM_PUBLIC=$5
CUSTOMER_PUBLIC_DIR=$6
APP=app
PRIV_APP=priv-app
JB_REMOVE_UNUSED_PACKAGE=true
CUSTOM_NEED_GAPPS=true
PRIV_REMOVE_PACKAGE=true
CUSTOM_NEED_VMX=true
CUSTOM_NEED_PLAYREADY=true
CUSTOM_NEED_WIFI_COM=true
CUSTOM_NEED_DLNA=true

CONTEXT_DIR=$CURRENT_DIR/private.system

BUILD_NAME="Normal-"
BUILD_VERSION="$VERSION"
BUILD_DATE="-`date +%Y%m%d`"
BUILD_ID="$BUILD_NAME$BUILD_VERSION$BUILD_DATE"
echo "ro.build.id=$BUILD_ID" > $CONTEXT_DIR/tmp.prop
echo "ro.sdmc.firmware.ver=$BUILD_VERSION" >> $CONTEXT_DIR/tmp.prop
cat $CONTEXT_DIR/build_device.prop >> $CONTEXT_DIR/tmp.prop

echo "CURRENT_DIR is $CURRENT_DIR"
echo "CONTEXT_DIR is $CONTEXT_DIR"
echo "SYSTEM_DIR is $SYSTEM_DIR"
echo "VERSION is $VERSION"
echo "PLATFORM_PUBLIC is $PLATFORM_PUBLIC"


cp -rf $PLATFORM_PUBLIC/system/* $SYSTEM_DIR/

if [ "$CUSTOM_NEED_GAPPS" = "true" ] ;then
	echo "install google apps..."
	cp -rf $PLATFORM_PUBLIC/google/* $SYSTEM_DIR/
fi

if [ "$CUSTOM_NEED_VMX" = "true" ] ;then
	echo "install VMX..."
	cp -rf $PLATFORM_PUBLIC/vmx/* $SYSTEM_DIR/
fi

if [ "$CUSTOM_NEED_PLAYREADY" = "true" ] ;then
	echo "install wifi..."
	cp -rf $PLATFORM_PUBLIC/playready/* $SYSTEM_DIR/
fi

if [ "$CUSTOM_NEED_WIFI_COM" = "true" ] ;then
	echo "install wifi..."
	cp -rf $PLATFORM_PUBLIC/wifi/* $SYSTEM_DIR/
fi


if [ "$CUSTOM_NEED_DLNA" = "true" ] ;then
	echo "install CUSTOM_NEED_DLNA..."
	cp -rf $PLATFORM_PUBLIC/dlna/* $SYSTEM_DIR/
fi

echo "CUSTOMER_PUBLIC_DIR is $CUSTOMER_PUBLIC_DIR"
cp -rf $PLATFORM_PUBLIC/dtv/* $SYSTEM_DIR/
cp -rf $CUSTOMER_PUBLIC_DIR/lib/* $SYSTEM_DIR/lib
#cp -rf $CUSTOMER_PUBLIC_DIR/app/* $SYSTEM_DIR/priv-app
#cp -rf $CUSTOMER_PUBLIC_DIR/framework/* $SYSTEM_DIR/framework

cp -rf $CONTEXT_DIR/tmp.prop $SYSTEM_DIR/build_device.prop
cp -rf $CONTEXT_DIR/build.prop  $SYSTEM_DIR/
cp -rf $CONTEXT_DIR/app/* $SYSTEM_DIR/$PRIV_APP
cp -rf $CONTEXT_DIR/lib/* $SYSTEM_DIR/lib
cp -rf $CONTEXT_DIR/etc/* $SYSTEM_DIR/etc
cp -rf $CONTEXT_DIR/media/* $SYSTEM_DIR/media
cp -rf $CONTEXT_DIR/usr/* $SYSTEM_DIR/usr
cp -rf $CONTEXT_DIR/xbin/* $SYSTEM_DIR/xbin
cp -rf $CONTEXT_DIR/bin/* $SYSTEM_DIR/bin
cp -rf $CONTEXT_DIR/hdtv/* $SYSTEM_DIR/hdtv
cp -rf $CONTEXT_DIR/framework/* $SYSTEM_DIR/framework

rm -rf $SYSTEM_DIR/lib/libdrmplayreadyplugin.so
rm -rf $SYSTEM_DIR/lib/libplayready2.0.so
rm -rf $SYSTEM_DIR/lib/libprwmv.so
rm -rf $SYSTEM_DIR/lib/ibsmoothstreaming_test.so
rm -rf $SYSTEM_DIR/preinstall/*
cp -rf $CONTEXT_DIR/preinstall $SYSTEM_DIR/




if [ "$FACTORY" = "yes" ] ;then
	echo "install factory info files..."
	cp -rf $CONTEXT_DIR/factory_info/* $SYSTEM_DIR/
fi

if [ "$JB_REMOVE_UNUSED_PACKAGE" = "true" ] ;then
	echo "remove jelly bean unused apks ..."
	rm -rf $SYSTEM_DIR/preinstall/More*
	rm -rf $SYSTEM_DIR/app/Calculator.*
	rm -rf $SYSTEM_DIR/app/Calendar.*
	rm -rf $SYSTEM_DIR/app/CalendarProvider.*
	rm -rf $SYSTEM_DIR/app/DeskClock.*
	rm -rf $SYSTEM_DIR/app/Development.*
	rm -rf $SYSTEM_DIR/app/DLNA.*
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
	rm -rf $SYSTEM_DIR/app/MusicPlayer.*
	rm -rf $SYSTEM_DIR/app/Bluetooth.*
	rm -rf $SYSTEM_DIR/app/MiracastSink.*
	rm -rf $SYSTEM_DIR/app/MediaBoxLauncher.*
	rm -rf $SYSTEM_DIR/app/FileBrowser.*
	rm -rf $SYSTEM_DIR/app/MboxSetting.*
	rm -rf $SYSTEM_DIR/app/Email.*
	rm -rf $SYSTEM_DIR/app/Camera2.*
	
fi

if [ "$PRIV_REMOVE_PACKAGE" = "true" ]; then
	echo "remove unused private apks ..."
	rm -rf $SYSTEM_DIR/$PRIV_APP/Contacts.*
	rm -rf $SYSTEM_DIR/$PRIV_APP/ContactsProvider.*
	rm -rf $SYSTEM_DIR/$PRIV_APP/DLNA.odex
fi
echo "removed and copy finish ..."
