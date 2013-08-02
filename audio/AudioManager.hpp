#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP
#include "Music.hpp"
#include "Effect.hpp"

class AudioManager {
	public:
		AudioManager();
		~AudioManager();

		bool loadMusic(const std::string& trackID, const std::string& filePath);
		void deleteMusic(const std::string& trackID);

		bool loadEffect(const std::string& effectID, const std::string& filePath);
		void deleteEffect(const std::string& effectID);

		std::map<std::string,Music*> musicBank;
		std::map<std::string,Effect*> effectBank;
};

#endif // AUDIOMANAGER_HPP
