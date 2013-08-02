#ifndef EFFECT_HPP
#define EFFECT_HPP
#include "tools.hpp"

class Effect
{
	public:
		Effect();
		~Effect();

		sf::Sound& getEffect();
		bool loadFromFile(const std::string& filePath);
	private:
		sf::Sound effect;
		sf::SoundBuffer buffer;
};

#endif // EFFECT_HPP
