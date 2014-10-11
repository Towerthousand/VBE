LOCAL_PATH := $(call my-dir)

###########################
#
# VBE shared library
#
###########################

include $(CLEAR_VARS)

LOCAL_MODULE := VBE

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

LOCAL_SHARED_LIBRARIES := SDL2

LOCAL_CFLAGS += -DGL_GLEXT_PROTOTYPES
LOCAL_CFLAGS += -std=c++11
LOCAL_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog -landroid
APP_STL := gnustl_static

include $(BUILD_SHARED_LIBRARY)
