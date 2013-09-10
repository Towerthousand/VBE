#include "AudioManager.hpp"

std::map<std::string,Music*> AudioManager::musicBank;
std::map<std::string,SoundEffect*> AudioManager::effectBank;

AudioManager::AudioManager() {
}

AudioManager::~AudioManager() {
}

bool AudioManager::loadMusic(const std::string &trackID, const std::string &filePath) {
	if (musicBank.count(trackID) != 0) {
		std::cout << "#WARNING " << trackID << " already loaded! Overwriting.." << std::endl;
		deleteMusic(trackID);
	}
	std::cout << "* Loading new music track: \"" << trackID << "\" from " << filePath << std::endl;
	Music * newTrack = new Music;
	if (!newTrack->loadFromFile(filePath)) {
		std::cout << "#ERROR " << filePath << " didn't load" << std::endl;
		return false;
	}
	musicBank[trackID] = newTrack;
	return true;
}

void AudioManager::deleteMusic(const std::string &trackID) {
	if (musicBank.count(trackID) != 0) {
		std::cout << "* Deleting music track \"" << trackID << "\"" << std::endl;
		delete musicBank[trackID];
		musicBank.erase(trackID);
	}
	else
		std::cout << "#WARNING Music track " << trackID << " doesn't exist! Failed to delete" << std::endl;
}

bool AudioManager::loadEffect(const std::string &effectID, const std::string &filePath) {
	if (effectBank.count(effectID) != 0) {
		std::cout << "#WARNING " << effectID << " already loaded! Overwriting.." << std::endl;
		deleteEffect(effectID);
	}
	std::cout << "* Loading new sound effect: \"" << effectID << "\" from " + filePath << std::endl;
	SoundEffect* newEffect = new SoundEffect;
	if (!newEffect->loadFromFile(filePath)) {
		std::cout << "#ERROR " << filePath << " didn't load" << std::endl;
		return false;
	}
	effectBank[effectID] = newEffect;
	return true;
}

void AudioManager::deleteEffect(const std::string &effectID) {
	if (effectBank.count(effectID) != 0) {
		std::cout << "* Deleting sound effect \"" << effectID << "\"" << std::endl;
		delete effectBank[effectID];
		effectBank.erase(effectID);
	}
	else
		std::cout << "#WARNING Effect " << effectID << " doesn't exist! Failed to delete" << std::endl;
}
