#ifndef SCREENIMPL_HPP
#define SCREENIMPL_HPP

#include <string>

#include <VBE/math.hpp>
#include <VBE/system/Screen.hpp>
#include <VBE/system/ContextSettings.hpp>
#include <VBE/system/sdl2/sdl2.hpp>

class ScreenImpl {
	public:
		static std::vector<Screen::DisplayMode> getFullscreenModes();
		static void create(Screen::DisplayMode mode, ContextSettings contextSettings);
		static void destroy();

		static void setDisplayMode(Screen::DisplayMode mode);
		static vec2ui getSize();

		static void update();
		static void setTitle(std::string newTitle);
		static bool isFocused();
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

		friend class InputImpl;
};

#endif // SCREENIMPL_HPP
