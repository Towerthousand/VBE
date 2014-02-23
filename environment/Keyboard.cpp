#include "Keyboard.hpp"

Keyboard::Keyboard() : focus(true) {
}

Keyboard::~Keyboard() {
}


void Keyboard::processEvent(const SDL_Event& e) {
	switch(e.type) {
		case SDL_KEYUP:
			keysHeld.insert((Key) e.key.keysym.sym);
			break;
		case SDL_KEYDOWN:
			keysHeld.erase((Key) e.key.keysym.sym);
			break;
		default:
			break;
	}
}

void Keyboard::update() {
	keysHeldOld = keysHeld;
}
