#include "Mouse.hpp"
#include "Environment.hpp"

Mouse::Mouse() : mousePos(0, 0), mousePosRel(0, 0) {
	for(int i = 0; i < _BUTTON_SIZE; i++)
		buttonsHeld[i] = buttonsHeldOld[i] = false;
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
			buttonsHeld[sdlButtonToButton(e.button.button)] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			buttonsHeld[sdlButtonToButton(e.button.button)] = false;
			break;
		case SDL_MOUSEMOTION:
			//VBE_LOG(e.motion.x<<" "<<e.motion.y<<" "<<e.motion.xrel<<" "<<e.motion.yrel);
			mousePos = vec2i(e.motion.x, e.motion.y);
			mousePosRel += vec2i(e.motion.xrel, e.motion.yrel);
			break;
		default:
			break;
	}
}

Mouse::Button Mouse::sdlButtonToButton(int button) {
	switch(button) {
		case SDL_BUTTON_LEFT: return Left;
		case SDL_BUTTON_MIDDLE: return Middle;
		case SDL_BUTTON_RIGHT: return Right;
		case SDL_BUTTON_X1: return X1;
		case SDL_BUTTON_X2: return X2;
		default:
			VBE_ASSERT(false, "Invalid SDL Button value: " << button);
			return Left;
	}
}

void Mouse::update() {
	memcpy(buttonsHeldOld, buttonsHeld, sizeof(buttonsHeld));
	mousePosRel = vec2i(0, 0);
}

void Mouse::hideCursor() {
	SDL_ShowCursor(false);
}

void Mouse::showCursor() {
	SDL_ShowCursor(true);
}

void Mouse::setGrab(bool grab) {
	VBE_ASSERT(Environment::getScreen()->window != nullptr, "Window must be initialized before calling setGrab");
	SDL_SetWindowGrab(Environment::getScreen()->window, (grab? SDL_TRUE : SDL_FALSE));
	SDL_SetRelativeMouseMode((grab? SDL_TRUE : SDL_FALSE));
}
