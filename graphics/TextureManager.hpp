#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP
#include "Texture.hpp"

class TextureManager
{
	public:
		static bool loadTexture(const std::string& textureID, const std::string& filePath);
		static void useTexture(const std::string& textureID, GLenum texUnit);
		static void deleteTexture(const std::string& textureID);
	private:
		TextureManager();
		~TextureManager();
		static std::map<std::string,Texture*> textureBank;
};

#endif // TEXTUREMANAGER_HPP
