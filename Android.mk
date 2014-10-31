LOCAL_PATH := $(call my-dir)

###########################
#
# VBE static library
#
###########################

include $(CLEAR_VARS)

LOCAL_MODULE := VBE_static
LOCAL_MODULE_FILENAME := libVBE

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include $(LOCAL_PATH)/src
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/src/VBE/dependencies/stb_image/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/VBE/geometry/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/VBE/graphics/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/VBE/scenegraph/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/VBE/system/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/VBE/system/android/*.cpp) \
	)

LOCAL_CFLAGS += -DGL_GLEXT_PROTOTYPES
LOCAL_CFLAGS += -std=c++11
LOCAL_EXPORT_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog -landroid
LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_STATIC_LIBRARY)

$(call import-module,android/native_app_glue)
