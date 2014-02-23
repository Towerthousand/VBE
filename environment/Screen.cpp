#include "Screen.hpp"

Screen::Screen() : window(nullptr), height(0), width(0), fullscreen(false) {
}

Screen::~Screen() {
	if(window != nullptr) {
		SDL_DestroyWindow(window);
		window = nullptr;
		SDL_GL_DeleteContext(context);
	}
}

void Screen::initWindow(std::string name, unsigned int width, unsigned int height, unsigned long int flags) {
	VBE_ASSERT(window == nullptr, "Window was already init");
	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	VBE_ASSERT(window != nullptr, "Failed to init window");
	SDL_GetWindowSize(window, &this->width, &this->height);
	context = SDL_GL_CreateContext(window);
	fullscreen = (flags & WINDOW_FULLSCREEN);
}

void Screen::goFullscreen(unsigned int displayMode, unsigned int displayIndex) {
	VBE_ASSERT(window != nullptr, "Window must be initialized before calling goFullscreen");
	VBE_WARN(!fullscreen, "Going fullscreen on an already fullscreen window");
	SDL_SetWindowFullscreen(window,WINDOW_FULLSCREEN);
	fullscreen = true;
	setDisplayMode(displayMode, displayIndex);
}

void Screen::goWindowed(unsigned int newWidth, unsigned int newHeight) {
	VBE_ASSERT(window != nullptr, "Window must be initialized before calling goWindowed");
	VBE_WARN(fullscreen, "Going windowed on an already windowed window");
	SDL_SetWindowFullscreen(window,0);
	fullscreen = false;
	resize(newWidth,newHeight);
}

void Screen::swapBuffers() const {
	SDL_GL_SwapWindow(window);
}

void Screen::setTitle(std::string newTitle) {
	VBE_ASSERT(window != nullptr, "Window must be initialized before calling setTitle");
	SDL_SetWindowTitle(window, newTitle.c_str());
}

void Screen::setDisplayMode(unsigned int displayMode, unsigned int displayIndex) {
	VBE_ASSERT(window != nullptr, "Window must be initialized before calling setDisplayMode");
	VBE_ASSERT(fullscreen, "Trying to set a display mode for a non-fullscreen window" << Log::Line
			   << "Display modes are only for fullscreen windows" << Log::Line
			   << "To set the size of a non-fullscreen window use resize()");
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex, displayMode, &mode);
	SDL_SetWindowDisplayMode(window,&mode);
	width = mode.w;
	height = mode.h;
}

void Screen::resize(unsigned int newWidth, unsigned int newHeight) {
	VBE_ASSERT(window != nullptr, "Window must be initialized before calling resize");
	VBE_ASSERT(!fullscreen, "Trying to resize a fullscreen window" << Log::Line
			   << "Resizing is only for fullscreen windows" << Log::Line
			   << "To set the display mode of a fullscreen window use setDisplayMode()");
	SDL_SetWindowSize(window, newWidth, newHeight);
	height = newHeight;
	width = newWidth;
}

void Screen::setPosition(unsigned int x, unsigned int y) {
	VBE_ASSERT(window != nullptr, "Window must be initialized before calling setPosition");
	VBE_ASSERT(!fullscreen, "Window must not be fullscreen to call setPosition");
	SDL_SetWindowPosition(window, x, y);
}

void Screen::setGrab(bool grab) {
	VBE_ASSERT(window != nullptr, "Window must be initialized before calling setGrab");
	SDL_SetWindowGrab(window, (grab? SDL_TRUE : SDL_FALSE));
}

void Screen::setBorder(bool border) {
	VBE_ASSERT(window != nullptr, "Window must be initialized before calling setBorder");
	SDL_SetWindowBordered(window, (border? SDL_TRUE : SDL_FALSE));
}

unsigned int Screen::getDisplayCount() const {
	return SDL_GetNumVideoDisplays();
}

std::vector<Screen::DisplayMode> Screen::getDisplayModes(unsigned int displayIndex) const {
	std::vector<DisplayMode> v;
	int numModes = SDL_GetNumDisplayModes(displayIndex);
	for(int i = 0; i < numModes; ++i) {
		SDL_DisplayMode mode;
		SDL_GetDisplayMode(displayIndex, i, &mode);
		v.push_back(DisplayMode(mode.h, mode.w, mode.refresh_rate));
	}
	return v;
}

Screen::DisplayMode Screen::getCurrentDisplayMode(int displayIndex) const {
	VBE_ASSERT(window != nullptr, "Window must be initialized before calling getCurrentDisplayMode");
	VBE_ASSERT(fullscreen, "Cannot get current display mode of non-fullscreen window" << Log::Line
			   << "Display modes are for fullscreens windows only" << Log::Line
			   << "To get the size of a non-fullscreen window use Screen::getSize()");
	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(displayIndex, &mode);
	return DisplayMode(mode.h, mode.w, mode.refresh_rate);
}

std::string Screen::getTitle() const {
	VBE_ASSERT(window != nullptr, "Window must be initialized before calling getTitle");
	return std::string(SDL_GetWindowTitle(window));
}
