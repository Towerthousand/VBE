#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP
#include "../tools.hpp"

class Texture;
class TextureManager{
	public:
		static bool load(const std::string& textureID, const std::string& filePath, unsigned int slot = 0, bool mipmap = false);
		static bool loadRaw(const std::string& textureID, const void* pixels, unsigned int sizeX, unsigned int sizeY, unsigned int slot, bool mipmap = false);
		static Texture* get(const std::string& textureID);
		static void erase(const std::string& textureID);
		static void clear();
	private:
		TextureManager();
		~TextureManager();
		static std::map<std::string,Texture*> textureBank;
};

#endif // TEXTUREMANAGER_HPP
