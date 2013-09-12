#include "TextureManager.hpp"
#include "Texture.hpp"

std::map<std::string,Texture*> TextureManager::textureBank;

TextureManager::TextureManager() {
}

TextureManager::~TextureManager() {
}

bool TextureManager::load(const std::string& textureID, const std::string& filePath) {
	if (textureBank.count(textureID) != 0) {
		std::cout << "#WARNING \"" << textureID << "\" already loaded! Overwriting texture.." << std::endl;
		erase(textureID);
	}
	std::cout << "* Loading new texture: \"" << textureID << "\" from " << filePath << std::endl;
	Texture* newTexture = new Texture();
	if (!newTexture->load(filePath))
		return false;
	textureBank.insert(std::pair<std::string,Texture*>(textureID,newTexture));
	return true;
}

void TextureManager::use(const std::string& textureID, GLenum texUnit) {
	glActiveTexture(texUnit);
	textureBank.at(textureID)->bind();
	glActiveTexture(GL_TEXTURE0);
}

void TextureManager::erase(const std::string& textureID) {
	assert(textureBank.find(textureID) != textureBank.end());
	delete textureBank.at(textureID);
	textureBank.erase(textureID);
	std::cout << "* Deleting texture: \"" << textureID << "\"" << std::endl;
}

void TextureManager::clear() {
	while(!textureBank.empty())
		erase(textureBank.begin()->first);
}
