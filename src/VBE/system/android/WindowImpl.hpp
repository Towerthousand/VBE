#ifndef WINDOWIMPL_HPP
#define WINDOWIMPL_HPP

#include <string>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <android_native_app_glue.h>

#include <VBE/math.hpp>
#include <VBE/system/Window.hpp>
#include <VBE/system/ContextSettings.hpp>

class WindowImpl {
    public:
        static std::vector<Window::DisplayMode> getFullscreenModes();
        static void create(Window::DisplayMode mode, ContextSettings contextSettings);
        static void destroy();

        static void setDisplayMode(Window::DisplayMode mode);
        static void setVsync(Window::VsyncMode mode);
        static vec2ui getSize();

        static void update();
        static void setTitle(std::string newTitle);
        static void setClosing(bool newClosing);
        static bool isFocused();
        static bool isClosing();
        static void setPosition(unsigned int x, unsigned int y);

        static void swapBuffers();

        // This is filled by android_main.
        static android_app* app;
        // This is called as a callback from the android app
        static void handleAndroidAppCmd(struct android_app* app, int32_t cmd);

        // Main entry point, called from android_main
        static void main(struct android_app* app);

    private:
        //		static void processEvent(const SDL_Event& e);

        static void initWindow();
        static void termWindow();
        static void destroyDisplay();

        static bool isSDLInit;
        static bool focused;
        static bool closing;

        static EGLDisplay display;
        static EGLSurface surface;
        static EGLContext context;
        static EGLConfig eglConfig;
        static EGLint eglFormat;
        static int width;
        static int height;

        friend class InputImpl;
};

#endif // WINDOWIMPL_HPP
