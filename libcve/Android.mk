LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := lib_cve.c
LOCAL_SRC_FILES += cve_check_params.c
LOCAL_SRC_FILES += cve_alloc.c
LOCAL_SRC_FILES += IONmem.c
LOCAL_SRC_FILES += test_dma.c
LOCAL_C_INCLUDES := \
		$(LOCAL_PATH)/../cve_include \
		$(LOCAL_PATH)

#LOCAL_SHARED_LIBRARIES := libion
LOCAL_STATIC_LIBRARIES := libion
LOCAL_CFLAGS := -Werror
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := libcve

LOCAL_MODULE_PATH32 := $(TARGET_OUT_VENDOR)/lib/
LOCAL_MODULE_PATH64 := $(TARGET_OUT_VENDOR)/lib64/
#LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_CLASS := STATIC_LIBRARIES

ifeq ($(shell test $(PLATFORM_SDK_VERSION) -ge 26 && echo OK),OK)
LOCAL_PROPRIETARY_MODULE := true
endif

#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)
