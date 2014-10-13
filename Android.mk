LOCAL_PATH := $(call my-dir)

###########################
#
# VBE static library
#
###########################

include $(CLEAR_VARS)

LOCAL_MODULE := VBE_static
LOCAL_MODULE_FILENAME := libVBE

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/*.cpp) \
	$(wildcard $(LOCAL_PATH)/dependencies/*.cpp) \
	$(wildcard $(LOCAL_PATH)/dependencies/stb_image/*.cpp) \
	$(wildcard $(LOCAL_PATH)/environment/*.cpp) \
	$(wildcard $(LOCAL_PATH)/geometry/*.cpp) \
	$(wildcard $(LOCAL_PATH)/graphics/*.cpp) \
	$(wildcard $(LOCAL_PATH)/scene/*.cpp) \
	$(wildcard $(LOCAL_PATH)/utils/*.cpp) \
	)

LOCAL_STATIC_LIBRARIES := SDL2_static

LOCAL_CFLAGS += -DGL_GLEXT_PROTOTYPES
LOCAL_CFLAGS += -std=c++11
LOCAL_EXPORT_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog -landroid

include $(BUILD_STATIC_LIBRARY)
