#include<VBE/system/Screen.hpp>
#include<VBE/system/sdl2/ScreenImpl.hpp>
#include<VBE/system/Log.hpp>


// static
std::vector<Screen::DisplayMode> Screen::getFullscreenModes() {
	return ScreenImpl::getFullscreenModes();
}

// Crear la screen
Screen::Screen(Screen::DisplayMode mode, ContextSettings contextSettings) {
	VBE_ASSERT(instance == nullptr, "Only one screen can exist at a time");

	instance = this;
	ScreenImpl::create(mode, contextSettings);
}

// Cerrar la screen
Screen::~Screen() {
	VBE_ASSERT(instance == this, "wtf");

	instance = nullptr;
	ScreenImpl::destroy();
}

// Run event loop. Must be called every frame.
void Screen::update() {
	ScreenImpl::update();
}

vec2ui Screen::getSize() const {
	return ScreenImpl::getSize();
}

void Screen::setDisplayMode(DisplayMode mode) {
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

