#include "TextureManager.hpp"
#include "Texture.hpp"

std::map<std::string,Texture*> TextureManager::textureBank;

TextureManager::TextureManager() {
}

TextureManager::~TextureManager() {
}

bool TextureManager::load(const std::string& textureID, const std::string& filePath, unsigned int slot) {
	VBE_ASSERT(textureBank.find(textureID) == textureBank.end(), "Failed to load texture. Texture " << textureID << " already exists");
	VBE_LOG("* Loading new texture with ID " << textureID << " from " << filePath << " with initial slot " << slot);
	Texture* newTexture = new Texture(slot);
	if (!newTexture->load(filePath))
		return false;
	textureBank.insert(std::pair<std::string,Texture*>(textureID,newTexture));
	return true;
}

Texture* TextureManager::get(const std::string& textureID) {
	VBE_ASSERT(textureBank.find(textureID) != textureBank.end(), "Failed to get texture. Texture " << textureID << " doesn't exist");
	return textureBank.at(textureID);
}

void TextureManager::erase(const std::string& textureID) {
	VBE_ASSERT(textureBank.find(textureID) != textureBank.end(), "Failed to erase texture. Texture " << textureID << " doesn't exist");
	VBE_LOG("* Deleting texture with ID " << textureID );
	delete textureBank.at(textureID);
	textureBank.erase(textureID);
}

void TextureManager::clear() {
	while(!textureBank.empty())
		erase(textureBank.begin()->first);
}
