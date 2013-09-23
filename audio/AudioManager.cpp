#include "AudioManager.hpp"

std::map<std::string,sf::Music*> AudioManager::musicBank;
std::map<std::string,std::pair<sf::SoundBuffer*,sf::Sound*>> AudioManager::effectBank;

AudioManager::AudioManager() {
}

AudioManager::~AudioManager() {
}

bool AudioManager::loadMusic(const std::string &trackID, const std::string &filePath) {
	VBE_ASSERT(musicBank.find(trackID) == musicBank.end(), "Loading failed: track " << trackID << " already exists");
	VBE_LOG("* Loading new music track: \"" << trackID << "\" from " << filePath );
	sf::Music * newTrack = new sf::Music();
	if (!newTrack->openFromFile(filePath)) {
		VBE_LOG("#ERROR " << filePath << " didn't load" );
		return false;
	}
	musicBank.insert(std::pair<std::string,sf::Music*>(trackID,newTrack));
	return true;
}

void AudioManager::eraseMusic(const std::string &trackID) {
	VBE_ASSERT(musicBank.find(trackID) != musicBank.end(), "Deleting failed: track " << trackID << " doesn't exist");
	VBE_LOG("* Deleting music track \"" << trackID << "\"" );
	delete musicBank.at(trackID);
	musicBank.erase(trackID);
}

bool AudioManager::loadEffect(const std::string &effectID, const std::string &filePath) {
	VBE_ASSERT(effectBank.find(effectID) == effectBank.end(), "Loading failed: effect " << effectID << " already exists");
	VBE_LOG("* Loading new sound effect: \"" << effectID << "\" from " + filePath );
	std::pair<sf::SoundBuffer*,sf::Sound*> newEffect = std::pair<sf::SoundBuffer*,sf::Sound*>(new sf::SoundBuffer(),new sf::Sound());
	if (!newEffect.first->loadFromFile(filePath)) {
		VBE_LOG("#ERROR " << filePath << " didn't load" );
		return false;
	}
	newEffect.second->setBuffer(*newEffect.first);
	effectBank.insert(std::pair<std::string,std::pair<sf::SoundBuffer*,sf::Sound*>>(effectID,newEffect));
	return true;
}

void AudioManager::eraseEffect(const std::string &effectID) {
	VBE_ASSERT(effectBank.find(effectID) != effectBank.end(), "Deleting failed: effect " << effectID << " doesn't exist");
	VBE_LOG("* Deleting sound effect \"" << effectID << "\"" );
	delete effectBank.at(effectID).first;
	delete effectBank.at(effectID).second;
	effectBank.erase(effectID);
}


void AudioManager::clear() {
	while(!effectBank.empty())
		eraseEffect(effectBank.begin()->first);
	while(!musicBank.empty())
		eraseMusic(musicBank.begin()->first);
}
