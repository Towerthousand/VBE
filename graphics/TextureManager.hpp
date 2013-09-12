#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP
#include "tools.hpp"

class Texture;
class TextureManager{
	public:
		static bool loadTexture(const std::string& textureID, const std::string& filePath);
		static void useTexture(const std::string& textureID, GLenum texUnit);
		static void deleteTexture(const std::string& textureID);
		static void clear();
	private:
		TextureManager();
		~TextureManager();
		static std::map<std::string,Texture*> textureBank;
};

#endif // TEXTUREMANAGER_HPP
