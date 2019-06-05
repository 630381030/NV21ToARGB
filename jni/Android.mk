LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := yuv
LOCAL_SRC_FILES := ../lib/$(APP_ABI)/libyuv.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := nv21_to_argb
LOCAL_SRC_FILES := ../src/main.cpp
LOCAL_SHARED_LIBRARIES := yuv
LOCAL_C_INCLUDES := ../include
include $(BUILD_EXECUTABLE)
