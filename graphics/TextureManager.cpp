#include "TextureManager.hpp"
#include "Texture.hpp"

std::map<std::string,Texture*> TextureManager::textureBank;

TextureManager::TextureManager() {
}

TextureManager::~TextureManager() {
}

bool TextureManager::load(const std::string& textureID, const std::string& filePath, unsigned int slot) {
	if (textureBank.count(textureID) != 0) {
		std::cout << "#WARNING \"" << textureID << "\" already loaded! Overwriting texture.." << std::endl;
		erase(textureID);
	}
	Texture* newTexture = new Texture(slot);
	if (!newTexture->load(filePath))
		return false;
	textureBank.insert(std::pair<std::string,Texture*>(textureID,newTexture));
	return true;
}

Texture* TextureManager::get(const std::string& textureID) {
	return textureBank.at(textureID);
}

void TextureManager::erase(const std::string& textureID) {
	delete textureBank.at(textureID);
	textureBank.erase(textureID);
}

void TextureManager::clear() {
	while(!textureBank.empty())
		erase(textureBank.begin()->first);
}
