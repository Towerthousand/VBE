#ifndef WINDOWIMPL_HPP
#define WINDOWIMPL_HPP

#include <string>

#include <VBE/math.hpp>
#include <VBE/system/Window.hpp>
#include <VBE/system/ContextSettings.hpp>
#include <VBE/system/sdl2/sdl2.hpp>

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

    private:
        // Initializes SDL if needed.
        static void initSDL();

        static void processEvent(const SDL_Event& e);

        static bool isSDLInit;
        static SDL_Window* window;
        static SDL_GLContext context;
        static bool focused;
        static bool closing;

        friend class InputImpl;
};

#endif // WINDOWIMPL_HPP
