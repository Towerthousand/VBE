#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP
#include "Texture.hpp"

class TextureManager
{
	public:
		TextureManager();
		~TextureManager();

		bool loadTexture(const std::string& textureID, const std::string& filePath);
		void useTexture(const std::string& textureID, GLenum texUnit);
		void deleteTexture(const std::string& textureID);
	private:
		std::map<std::string,Texture*> textureBank;
};

#endif // TEXTUREMANAGER_HPP
