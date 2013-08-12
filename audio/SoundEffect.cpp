#include "SoundEffect.hpp"

SoundEffect::SoundEffect() {
}

SoundEffect::~SoundEffect() {
}

bool SoundEffect::loadFromFile(const std::string& filePath) {
	if (!buffer.loadFromFile(filePath)) {
		return false;
	}
	effect.setBuffer(buffer);
	return true;
}

sf::Sound& SoundEffect::getEffect() {
	return effect;
}
