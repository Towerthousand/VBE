#include<VBE/system/Screen.hpp>
#include<VBE/system/sdl2/ScreenImpl.hpp>


static std::vector<DisplayMode> Screen::getFullscreenModes();

// Crear la screen
Screen::Screen(DisplayMode mode, ContextSettings contextSettings) {
	instance = this;
	ScreenImpl::create(mode, contextSettings);
}

// Cerrar la screen
Screen::~Screen() {
	instance = nullptr;
	ScreenImpl::destroy();
}

// Run event loop. Must be called every frame.
void Screen::update() {
	ScreenImpl::update();
}

DisplayMode Screen::getDisplayMode() const {
	return displayMode;
}

void Screen::setDisplayMode(DisplayMode mode) {
	displayMode = mode;
	ScreenImpl::setDisplayMode(mode);
}

std::string Screen::getTitle() const {
	return title;
}

void Screen::setTitle(std::string newTitle) {
	title = newTitle;
	ScreenImpl::setTitle(title);
}

bool Screen::isFocused() const {
	return ScreenImpl::isFocused();
}

void Screen::setPosition(unsigned int x, unsigned int y) {
	ScreenImpl::setPosition(x, y);
}

void Screen::swapBuffers() const {
	ScreenImpl::swapBuffers();
}

Screen* Screen::instance = nullptr;

// static
Screen* Screen::getInstance() {
	return instance;
}

