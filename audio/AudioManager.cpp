#include "AudioManager.hpp"

AudioManager::AudioManager() {
}

AudioManager::~AudioManager() {
}

bool AudioManager::loadMusic(const std::string &trackID, const std::string &filePath) {
	if (musicBank.count(trackID) != 0) {
		outLog("#WARNING " + trackID + " already loaded! Overwriting..");
		deleteMusic(trackID);
	}
	outLog("* Loading new music track: \"" + trackID + "\" from " + filePath );
	Music * newTrack = new Music;
	if (!newTrack->loadFromFile(filePath)) {
		outLog("#ERROR " + filePath + " didn't load");
		return false;
	}
	musicBank[trackID] = newTrack;
	return true;
}

void AudioManager::deleteMusic(const std::string &trackID) {
	if (musicBank.count(trackID) != 0) {
		outLog("* Deleting music track \"" + trackID + "\"" );
		delete musicBank[trackID];
		musicBank.erase(trackID);
	}
	else
		outLog("#WARNING Music track " + trackID + " doesn't exist! Failed to delete");
}

bool AudioManager::loadEffect(const std::string &effectID, const std::string &filePath) {
	if (effectBank.count(effectID) != 0) {
		outLog("#WARNING " + effectID + " already loaded! Overwriting..");
		deleteEffect(effectID);
	}
	outLog("* Loading new sound effect: \"" + effectID + "\" from " + filePath );
	Effect* newEffect = new Effect;
	if (!newEffect->loadFromFile(filePath)) {
		outLog("#ERROR " + filePath + " didn't load");
		return false;
	}
	effectBank[effectID] = newEffect;
	return true;
}

void AudioManager::deleteEffect(const std::string &effectID) {
	if (effectBank.count(effectID) != 0) {
		outLog("* Deleting sound effect \"" + effectID + "\"" );
		delete effectBank[effectID];
		effectBank.erase(effectID);
	}
	else
		outLog("#WARNING Effect " + effectID + " doesn't exist! Failed to delete");
}
