#include "AudioManager.hpp"

std::map<std::string,sf::Music*> AudioManager::musicBank;
std::map<std::string,std::pair<sf::SoundBuffer*,sf::Sound*>> AudioManager::effectBank;

AudioManager::AudioManager() {
}

AudioManager::~AudioManager() {
}

bool AudioManager::loadMusic(const std::string &trackID, const std::string &filePath) {
	if (musicBank.find(trackID) != musicBank.end()) {
		std::cout << "#WARNING " << trackID << " already loaded! Overwriting.." << std::endl;
		deleteMusic(trackID);
	}
	std::cout << "* Loading new music track: \"" << trackID << "\" from " << filePath << std::endl;
	sf::Music * newTrack = new sf::Music();
	if (!newTrack->openFromFile(filePath)) {
		std::cout << "#ERROR " << filePath << " didn't load" << std::endl;
		return false;
	}
	musicBank[trackID] = newTrack;
	return true;
}

void AudioManager::deleteMusic(const std::string &trackID) {
	if (musicBank.find(trackID) != musicBank.end()) {
		std::cout << "* Deleting music track \"" << trackID << "\"" << std::endl;
		delete musicBank[trackID];
		musicBank.erase(trackID);
	}
	else
		std::cout << "#WARNING Music track " << trackID << " doesn't exist! Failed to delete" << std::endl;
}

bool AudioManager::loadEffect(const std::string &effectID, const std::string &filePath) {
	if (effectBank.find(effectID) != effectBank.end()) {
		std::cout << "#WARNING " << effectID << " already loaded! Overwriting.." << std::endl;
		deleteEffect(effectID);
	}
	std::cout << "* Loading new sound effect: \"" << effectID << "\" from " + filePath << std::endl;
	std::pair<sf::SoundBuffer*,sf::Sound*> newEffect = std::pair<sf::SoundBuffer*,sf::Sound*>(new sf::SoundBuffer(),new sf::Sound());
	if (!newEffect.first->loadFromFile(filePath)) {
		std::cout << "#ERROR " << filePath << " didn't load" << std::endl;
		return false;
	}
	newEffect.second->setBuffer(*newEffect.first);
	effectBank[effectID] = newEffect;
	return true;
}

void AudioManager::deleteEffect(const std::string &effectID) {
	if (effectBank.find(effectID) != effectBank.end()) {
		std::cout << "* Deleting sound effect \"" << effectID << "\"" << std::endl;
		delete effectBank[effectID].first;
		delete effectBank[effectID].second;
		effectBank.erase(effectID);
	}
	else
		std::cout << "#WARNING Effect " << effectID << " doesn't exist! Failed to delete" << std::endl;
}
