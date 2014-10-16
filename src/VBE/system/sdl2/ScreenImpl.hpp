#ifndef SCREENIMPL_HPP
#define SCREENIMPL_HPP

#include <string>

#include <VBE/system/Screen.hpp>
#include <VBE/system/ContextSettings.hpp>

class ScreenImpl {
	public:
		static void create(Screen::DisplayMode mode, ContextSettings contextSettings);
		static void destroy();

		static void setDisplayMode(Screen::DisplayMode mode);

		static void update();
		static void setTitle(std::string newTitle);
		static bool isFocused();
		static void setPosition(unsigned int x, unsigned int y);

		static void swapBuffers();
};

#endif // SCREENIMPL_HPP
