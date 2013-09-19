#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP
#include "../tools.hpp"

class AudioManager {
	public:
		static bool loadMusic(const std::string& trackID, const std::string& filePath);
		static sf::Music* getMusic(std::string trackID) { return s_musicBank.at(trackID);}
		static void deleteMusic(const std::string& trackID);

		static bool loadEffect(const std::string& effectID, const std::string& filePath);
		static sf::Sound* getEffect(const std::string& effectID) { return s_effectBank.at(effectID).second;}
		static void deleteEffect(const std::string& effectID);

	private:
		static std::map<std::string,sf::Music*> s_musicBank;
		static std::map<std::string,std::pair<sf::SoundBuffer*,sf::Sound*>> s_effectBank;
		AudioManager();
		~AudioManager();
};

#endif // AUDIOMANAGER_HPP
