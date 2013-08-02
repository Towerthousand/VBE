#ifndef FontManager_HPP
#define FontManager_HPP
#include "tools.hpp"
class FontManager {
	public:
		FontManager();
		~FontManager();

		bool makeText(const std::string& textID, const std::string& textString,
					  int size, const vec2f& position,
					  const sf::Color& color, const sf::Text::Style& style, const bool& center_origin);
		sf::Text& getText(const std::string& textID);
		void deleteText(const std::string& textID);

		sf::Font globalFont;
	private:
		std::map<std::string,sf::Text> texts;

};

#endif // FontManager_HPP
