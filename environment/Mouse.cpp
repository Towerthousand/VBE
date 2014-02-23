#include "Mouse.hpp"
#include "Environment.hpp"

Mouse::Mouse() : mousePos(0, 0), mousePosOld(0, 0) {
	for(int i = 0; i < _BUTTON_SIZE; i++)
		buttonsHeld[i] = buttonsHeldOld[i] = false;
}

void Mouse::setMousePos(int x, int y) {
	SDL_WarpMouseInWindow(Environment::getScreen()->window, x, y);
	mousePos = vec2i(x, y);
	mousePosOld = vec2i(x, y);
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
			mousePos = vec2i(e.motion.x, e.motion.y);
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
			VBE_ASSERT(false, "Invalid SDL Button value.");
			return Left;
	}
}

void Mouse::update() {
	memcpy(buttonsHeldOld, buttonsHeld, sizeof(buttonsHeld));
	mousePosOld = mousePos;
}
