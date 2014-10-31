#include <VBE/system/android/WindowImpl.hpp>
#include <VBE/system/android/InputImpl.hpp>
#include <VBE/system/Log.hpp>

// static
bool WindowImpl::focused = false;
bool WindowImpl::closing = false;
EGLDisplay WindowImpl::display;
EGLSurface WindowImpl::surface;
EGLContext WindowImpl::context;
int WindowImpl::width;
int WindowImpl::height;
android_app* WindowImpl::app;

// static
std::vector<Window::DisplayMode> WindowImpl::getFullscreenModes() {
	std::vector<Window::DisplayMode> v;
	Window::DisplayMode dm(1024, 768, 60, Window::DisplayMode::Fullscreen);
	v.push_back(dm);
	return v;
}

// static
void WindowImpl::create(Window::DisplayMode mode, ContextSettings config) {
	focused = false;
	// Wait for Android to focus and start our window.
	update();

	// Init input
	InputImpl::init();
}

// static
void WindowImpl::destroy() {
}

// static
void WindowImpl::setDisplayMode(Window::DisplayMode mode) {
}

// static
void WindowImpl::update() {
	app->onAppCmd = handleAndroidAppCmd;
//	state->onInputEvent = engine_handle_input;

	// Read all pending events.
	int ident;
	int events;
	struct android_poll_source* source;

	// If focused, we loop until all events are read, then continue
	// to draw the next frame of animation.
	// If not, we wait for events, blocking if needed, until we become focused.
	while (focused && (ident=ALooper_pollAll(focused ? 0 : -1, NULL, &events,
			(void**)&source)) >= 0) {

		// Process this event.
		if (source != NULL) {
			source->process(app, source);
		}
	}
}

// static
void WindowImpl::setTitle(std::string newTitle) {
	// Not applicable
}

// static
void WindowImpl::setClosing(bool newClosing) {
	closing = newClosing;
}

// static
vec2ui WindowImpl::getSize() {
	return vec2ui(width, height);
}

// static
bool WindowImpl::isFocused() {
	return focused;
}

// static
bool WindowImpl::isClosing() {
	return closing;
}

// static
void WindowImpl::setPosition(unsigned int x, unsigned int y) {
	// Not applicable
}

// static
void WindowImpl::swapBuffers() {
	eglSwapBuffers(display, surface);
}

// static
void WindowImpl::handleAndroidAppCmd(struct android_app* app, int32_t cmd) {
	switch (cmd) {
		case APP_CMD_SAVE_STATE:
			// cool story bro
			break;
		case APP_CMD_INIT_WINDOW:
			initWindow();
			break;
		case APP_CMD_TERM_WINDOW:
			termWindow();
			break;
		case APP_CMD_GAINED_FOCUS:
			focused = true;
			break;
		case APP_CMD_LOST_FOCUS:
			focused = false;
			break;
	}
}

void WindowImpl::initWindow() {

	display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	eglInitialize(display, 0, 0);

	/*
	 * Here specify the attributes of the desired configuration.
	 * Below, we select an EGLConfig with at least 8 bits per color
	 * component compatible with on-screen windows
	 */
	const EGLint attribs[] = {
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_BLUE_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8,
			EGL_NONE
	};
	/* Here, the application chooses the configuration it desires. In this
	 * sample, we have a very simplified selection process, where we pick
	 * the first EGLConfig that matches our criteria */
	EGLint numConfigs;
	EGLConfig eglConfig;
	eglChooseConfig(display, attribs, &eglConfig, 1, &numConfigs);

	/* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
	 * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
	 * As soon as we picked a EGLConfig, we can safely reconfigure the
	 * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
	EGLint format;
	eglGetConfigAttrib(display, eglConfig, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(app->window, 0, 0, format);

	surface = eglCreateWindowSurface(display, eglConfig, app->window, NULL);
	context = eglCreateContext(display, eglConfig, NULL, NULL);
		
	VBE_ASSERT(eglMakeCurrent(display, surface, surface, context) == EGL_TRUE, "Unable to eglMakeCurrent");

	eglQuerySurface(display, surface, EGL_WIDTH, &width);
	eglQuerySurface(display, surface, EGL_HEIGHT, &height);

}

void WindowImpl::termWindow() {

	if (display != EGL_NO_DISPLAY) {
		eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if (context != EGL_NO_CONTEXT) {
			eglDestroyContext(display, context);
		}
		if (surface != EGL_NO_SURFACE) {
			eglDestroySurface(display, surface);
		}
		eglTerminate(display);
	}
	focused = false;
	display = EGL_NO_DISPLAY;
	context = EGL_NO_CONTEXT;
	surface = EGL_NO_SURFACE;
}
