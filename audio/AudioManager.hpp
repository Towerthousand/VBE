#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP
#include "Music.hpp"
#include "SoundEffect.hpp"

class AudioManager {
	public:
		static bool loadMusic(const std::string& trackID, const std::string& filePath);
		static void deleteMusic(const std::string& trackID);

		static bool loadEffect(const std::string& effectID, const std::string& filePath);
		static void deleteEffect(const std::string& effectID);

		static std::map<std::string,Music*> musicBank;
		static std::map<std::string,SoundEffect*> effectBank;
	private:
		AudioManager();
		~AudioManager();
};

#endif // AUDIOMANAGER_HPP
