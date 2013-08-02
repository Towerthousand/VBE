#include "FontManager.hpp"

FontManager::FontManager() {
}

FontManager::~FontManager() {
}


bool FontManager::makeText(const std::string& textID, const std::string& textString,
						   int size, const vec2f& position,
						   const sf::Color& color, const sf::Text::Style& style,
						   const bool& center_origin) {
	if (texts.count(textID) != 0)
		deleteText(textID);
	sf::Text text;
	text.setFont(globalFont);
	text.setString(textString);
	text.setCharacterSize(size);
	text.setColor(color);
	text.setStyle(style);
	if (center_origin)
		text.setOrigin(text.getLocalBounds().width/2,
					   text.getLocalBounds().height/2);
	text.setOrigin(text.getOrigin().x + text.getLocalBounds().left, //deviation restored
				   text.getOrigin().y + text.getLocalBounds().top); //deviation restored
	text.setPosition(sf::Vector2f(position.x,position.y));
	texts[textID] = text;
	return true;
}

sf::Text& FontManager::getText(const std::string& textID) {
	return texts[textID];
}

void FontManager::deleteText(const std::string &textID) {
	if (texts.count(textID) != 0)
		texts.erase(textID);
}
