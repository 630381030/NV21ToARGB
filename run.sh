#!/bin/bash
ndk-build clean
ndk-build -C jni/
adb push images/ /data/local/tmp
adb push obj/local/arm64-v8a/libyuv.so /data/local/tmp
adb push obj/local/arm64-v8a/nv21_to_argb /data/local/tmp
adb shell "cd /data/local/tmp;export LD_LIBRARY_PATH=.;./nv21_to_argb 640x480 images/640x480-nv21.yuv ./640x480.argb"
adb pull /data/local/tmp/640x480.argb ./
