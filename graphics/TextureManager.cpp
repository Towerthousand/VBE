#include "TextureManager.hpp"

std::map<std::string,Texture*> TextureManager::textureBank;

TextureManager::TextureManager() {
}

TextureManager::~TextureManager() {
	for(std::map<std::string,Texture*>::iterator it = textureBank.begin(); it != textureBank.end(); ++it)
		delete (*it).second;
}

bool TextureManager::loadTexture(const std::string& textureID, const std::string& filePath) {
	if (textureBank.count(textureID) != 0) {
		std::cout << "#WARNING \"" << textureID << "\" already loaded! Overwriting texture.." << std::endl;
		deleteTexture(textureID);
	}
	std::cout << "* Loading new texture: \"" << textureID << "\" from " << filePath << std::endl;
	Texture* newTexture = new Texture();
	if (!newTexture->load(filePath))
		return false;
	textureBank[textureID] = newTexture;
	return true;
}

void TextureManager::useTexture(const std::string& textureID, GLenum texUnit) {
	glActiveTexture(texUnit);
	if (textureBank.count(textureID) == 0) {
		std::cout << "#WARNING Trying to bind unexisting textureID: \"" << textureID << "\"" << std::endl;
	}
	else textureBank[textureID]->bind();
	glActiveTexture(GL_TEXTURE0);
}

void TextureManager::deleteTexture(const std::string& textureID) {
	if (textureBank.count(textureID) != 0) {
		delete textureBank[textureID];
		textureBank.erase(textureID);
		std::cout << "* Deleting texture: \"" << textureID << "\"" << std::endl;
	}
	else
		std::cout << "#WARNING Texture \"" << textureID << "\" doesn't exist! Unable to delete" << std::endl;
}

