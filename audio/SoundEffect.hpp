#ifndef EFFECT_HPP
#define EFFECT_HPP
#include "tools.hpp"

class SoundEffect
{
	public:
		SoundEffect();
		~SoundEffect();

		sf::Sound& getEffect();
		bool loadFromFile(const std::string& filePath);
	private:
		sf::Sound effect;
		sf::SoundBuffer buffer;
};

#endif // SOUNDEFFECT_HPP
