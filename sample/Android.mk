LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
ifeq ($(shell test $(PLATFORM_SDK_VERSION) -ge 26 && echo OK),OK)
LOCAL_MODULE_PATH_32 := $(TARGET_OUT_VENDOR)/bin
endif

LIBDIR:=../libcve

LOCAL_SRC_FILES := sample_comm_cve.c
LOCAL_SRC_FILES += sample_cve_main.c
LOCAL_SRC_FILES += sample_cve_tof.c
LOCAL_SRC_FILES += sample_cve_dma.c
LOCAL_SRC_FILES += sample_cve_gmm.c

LOCAL_C_INCLUDES := \
		$(LOCAL_PATH) \
		$(LOCAL_PATH)/../cve_include \
		$(LOCAL_PATH)/$(LIBDIR)\

#LOCAL_SHARED_LIBRARIES := libion libcve
LOCAL_SHARED_LIBRARIES := libion
LOCAL_STATIC_LIBRARIES := libcve

LOCAL_CFLAGS := -Wall -Wno-unused-variable -Wno-sign-compare
LOCAL_CFLAGS += -Wno-multichar -Wno-sometimes-uninitialized -Wno-format
#LOCAL_CFLAGS += -UNDEBUG

LOCAL_MODULE_TAGS := optional

LOCAL_MODULE:= sample-cve

include $(BUILD_EXECUTABLE)
