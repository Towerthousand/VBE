#include "Music.hpp"

Music::Music() {
}

Music::~Music() {
}


bool Music::loadFromFile(const std::string& filePath) {
	if (!track.openFromFile(filePath)) {
		return false;
	}
	return true;
}

sf::Music& Music::getTrack() {
	return track;
}
