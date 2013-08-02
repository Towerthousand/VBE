#ifndef MUSIC_HPP
#define MUSIC_HPP
#include "tools.hpp"

class Music
{
	public:
		Music();
		~Music();
		bool loadFromFile(const std::string& filePath);
		sf::Music& getTrack();
	private:
		sf::Music track;
};

#endif // MUSIC_HPP
