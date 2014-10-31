#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/log.h>
#include <android_native_app_glue.h>

#include <VBE/system/android/WindowImpl.hpp>
#include <VBE/config.hpp>

int main(int argc, char** argv);

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* app) {

	// Make sure glue isn't stripped.
	app_dummy();

	WindowImpl::app = app;

	LOGI("Hello World!");
	VBE_LOG("HELLO VBE WORLD");

	VBE_LOG("Starting main...");
	::main(0, NULL);
}