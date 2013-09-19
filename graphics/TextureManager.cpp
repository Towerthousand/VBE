#include "TextureManager.hpp"
#include "Texture.hpp"

std::map<std::string,Texture*> TextureManager::s_textureBank;

TextureManager::TextureManager() {
}

TextureManager::~TextureManager() {
}

bool TextureManager::load(const std::string& textureID, const std::string& filePath, unsigned int slot) {
	VBE_ASSERT(s_textureBank.find(textureID) == s_textureBank.end(), "Failed to load texture. Texture " << textureID << " already exists")
	std::cout << "* Loading new texture with ID " << textureID << " from " << filePath << " with initial slot " << slot <<  std::endl;
	Texture* newTexture = new Texture(slot);
	if (!newTexture->load(filePath))
		return false;
	s_textureBank.insert(std::pair<std::string,Texture*>(textureID,newTexture));
	return true;
}

Texture* TextureManager::get(const std::string& textureID) {
	VBE_ASSERT(s_textureBank.find(textureID) != s_textureBank.end(), "Failed to get texture. Texture " << textureID << " doesn't exist")
	return s_textureBank.at(textureID);
}

void TextureManager::erase(const std::string& textureID) {
	VBE_ASSERT(s_textureBank.find(textureID) != s_textureBank.end(), "Failed to erase texture. Texture " << textureID << " doesn't exist")
	std::cout << "* Deleting texture with ID " << textureID << std::endl;
	delete s_textureBank.at(textureID);
	s_textureBank.erase(textureID);
}

void TextureManager::clear() {
	while(!s_textureBank.empty())
		erase(s_textureBank.begin()->first);
}
