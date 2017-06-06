LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := chipid.c

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libutils

LOCAL_MODULE := read_chipid

LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)

