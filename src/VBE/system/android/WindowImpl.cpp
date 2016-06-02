#include <VBE/system/android/WindowImpl.hpp>
#include <VBE/system/android/InputImpl.hpp>
#include <VBE/system/Log.hpp>

// static
bool WindowImpl::focused = false;
bool WindowImpl::closing = false;
EGLDisplay WindowImpl::display = EGL_NO_DISPLAY;
EGLSurface WindowImpl::surface = EGL_NO_SURFACE;
EGLContext WindowImpl::context = EGL_NO_CONTEXT;
EGLConfig WindowImpl::eglConfig;
EGLint WindowImpl::eglFormat;
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
    VBE_LOG("Creating WindowImpl");
    focused = false;
    closing = false;
    // Wait for Android to focus and start our window.
    update();

    VBE_ASSERT(!closing, "Closing app when creating window??");

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
    struct android_poll_source* source = NULL;

    // If focused, we loop until all events are read, then continue
    // to draw the next frame of animation.
    // If not, we wait for events, blocking if needed, until we become focused.
    while (!closing && ((ident=ALooper_pollAll(focused ? 0 : -1, NULL, &events, (void**)&source)) >= 0 || !focused)) {
        // Process this event.
        if (source != NULL) {
            source->process(app, source);
        }
        source = NULL;
    }
}

// static
void WindowImpl::setVsync(Window::VsyncMode mode) {
    // TODO (n/a?)
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
            // OMG YOLO SWAG
            break;
        case APP_CMD_INIT_WINDOW:
            VBE_LOG("Init window");
            initWindow();
            break;
        case APP_CMD_TERM_WINDOW:
            VBE_LOG("Term window");
            termWindow();
            break;
        case APP_CMD_GAINED_FOCUS:
            VBE_LOG("Gained focus");
            focused = true;
            break;
        case APP_CMD_LOST_FOCUS:
            VBE_LOG("Lost focus");
            focused = false;
            break;
        case APP_CMD_DESTROY:
            // Ask the user to quit.
            // We can't call destroyDisplay() yet, because quitting will release GL resources.
            // Even worse, here the window surface is destroyed, but the user needs the GL context
            // to free the GL resources properly.
            // Therefore, we create a temporary offscreen surface and use it to bind the context, until
            // main returns, then we'll call destroyDisplay().
            //
            // Yes, this is a terrible hack. Someone kill me.

            EGLint attrib_list[] = {
                EGL_WIDTH, 1,
                EGL_HEIGHT,1,
                EGL_NONE
            };

            surface = eglCreatePbufferSurface(display, eglConfig, attrib_list);
            VBE_ASSERT(eglMakeCurrent(display, surface, surface, context) == EGL_TRUE, "Unable to eglMakeCurrent");

            closing = true;
            break;
    }
}

void WindowImpl::initWindow() {

    if(display == EGL_NO_DISPLAY) {
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

        eglInitialize(display, 0, 0);

        /*
         * Here specify the attributes of the desired configuration.
         * Below, we select an EGLConfig with at least 8 bits per color
         * component compatible with on-screen windows
         */
        const EGLint attribs[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
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
        eglChooseConfig(display, attribs, &eglConfig, 1, &numConfigs);

        /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
         * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
         * As soon as we picked a EGLConfig, we can safely reconfigure the
         * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
        eglGetConfigAttrib(display, eglConfig, EGL_NATIVE_VISUAL_ID, &eglFormat);
    }

    ANativeWindow_setBuffersGeometry(app->window, 0, 0, eglFormat);

    surface = eglCreateWindowSurface(display, eglConfig, app->window, NULL);

    if(context == EGL_NO_CONTEXT) {
        VBE_LOG("Creating EGL Context");
        EGLint context_attr[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
        };
        context = eglCreateContext(display, eglConfig, NULL, context_attr);
    }

    VBE_ASSERT(eglMakeCurrent(display, surface, surface, context) == EGL_TRUE, "Unable to eglMakeCurrent");

    eglQuerySurface(display, surface, EGL_WIDTH, &width);
    eglQuerySurface(display, surface, EGL_HEIGHT, &height);

    VBE_LOG("+++++++++++++++++++++++++++++++++++++++++++++++");
    VBE_LOG((const char*) glGetString(GL_VERSION));
    VBE_LOG("+++++++++++++++++++++++++++++++++++++++++++++++");
}

void WindowImpl::termWindow() {

    if (surface != EGL_NO_SURFACE) {
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglDestroySurface(display, surface);
        surface = EGL_NO_SURFACE;
        //eglTerminate(display);
    }

    focused = false;
}

void WindowImpl::destroyDisplay() {
    VBE_LOG("destroyDisplay()");
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

    display = EGL_NO_DISPLAY;
    context = EGL_NO_CONTEXT;
    surface = EGL_NO_SURFACE;
}

extern int main(int argc, char** argv);

void WindowImpl::main(struct android_app* app) {
    // Make sure glue isn't stripped.
    app_dummy();

    WindowImpl::app = app;

    // Call user's main.
    ::main(0, NULL);

    ANativeActivity_finish(app->activity);
    destroyDisplay();

    exit(0);
}

void android_main(struct android_app* app) {
    WindowImpl::main(app);
}
