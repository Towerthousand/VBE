#include "Effect.hpp"

Effect::Effect() {
}

Effect::~Effect() {
}

bool Effect::loadFromFile(const std::string& filePath) {
	if (!buffer.loadFromFile(filePath)) {
		return false;
	}
	effect.setBuffer(buffer);
	return true;
}

sf::Sound& Effect::getEffect() {
	return effect;
}
