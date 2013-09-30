#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP
#include "../tools.hpp"

class AudioManager {
	public:
		static bool loadMusic(const std::string& trackID, const std::string& filePath);
		static sf::Music* getMusic(std::string trackID) { return musicBank.at(trackID);}
		static void eraseMusic(const std::string& trackID);

		static bool loadEffect(const std::string& effectID, const std::string& filePath);
		static sf::Sound* getEffect(const std::string& effectID) { return effectBank.at(effectID).second;}
		static void eraseEffect(const std::string& effectID);

		static void clear();

	private:
		static std::map<std::string,sf::Music*> musicBank;
		static std::map<std::string,std::pair<sf::SoundBuffer*,sf::Sound*>> effectBank;
		AudioManager();
		~AudioManager();
};

#endif // AUDIOMANAGER_HPP
