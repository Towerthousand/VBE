#include "Mouse.hpp"
#include "Environment.hpp"

Mouse::Mouse() : mousePos(0, 0), mousePosRel(0, 0), cursor(nullptr) {
	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	SDL_SetCursor(cursor);
	SDL_ShowCursor(1);
}

Mouse::~Mouse() {
	SDL_FreeCursor(cursor);
}

void Mouse::setMousePos(int x, int y) {
	if(!Environment::getScreen()->isFocused())
		return;

	SDL_WarpMouseInWindow(Environment::getScreen()->window, x, y);
	mousePos = vec2i(x, y);
	mousePosRel = vec2i(0, 0);
}

void Mouse::processEvent(const SDL_Event& e) {
	switch(e.type) {
		case SDL_MOUSEBUTTONDOWN:
			buttonsHeld.insert((Button) e.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			buttonsHeld.erase((Button) e.button.button);
			break;
		case SDL_MOUSEMOTION:
			mousePos = vec2i(e.motion.x, e.motion.y);
			mousePosRel += vec2i(e.motion.xrel, e.motion.yrel);
			break;
		default:
			break;
	}
}

void Mouse::update() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	buttonsHeldOld = buttonsHeld;
	mousePosRel = vec2i(0, 0);
}

void Mouse::hideCursor() {
	SDL_ShowCursor(SDL_DISABLE);
}

void Mouse::showCursor() {
	SDL_ShowCursor(SDL_ENABLE);
}

void Mouse::setGrab(bool grab) {
	VBE_ASSERT(Environment::getScreen()->window != nullptr, "Window must be initialized before calling setGrab");
	SDL_SetWindowGrab(Environment::getScreen()->window, (grab? SDL_TRUE : SDL_FALSE));
}

void Mouse::setRelativeMouseMode(bool relative) {
	VBE_ASSERT(Environment::getScreen()->window != nullptr, "Window must be initialized before calling setRelativeMouseMode");
	SDL_SetRelativeMouseMode((relative? SDL_TRUE : SDL_FALSE));
}
