#include "Keyboard.hpp"

Keyboard::Keyboard() : focus(true) {
}

Keyboard::~Keyboard() {
}

void Keyboard::update() {
	keysPressed = std::set<Key>();
	keysReleased = std::set<Key>();
}
