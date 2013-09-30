#ifndef Texture_HPP
#define Texture_HPP
#include "../tools.hpp"

class Texture
{
	public:
		Texture(unsigned int slot);
		~Texture();

		void setFilter(GLenum min, GLenum mag);
		void setWrap(GLenum wrap) const;
		void setSlot(unsigned int newSlot);
		void generateMipmap();
		unsigned int getSlot() const;
		int getWidth() const;
		int getHeight() const;
		void bind() const;
	private:
		GLuint getHandle() const;
		bool loadFromFile(const std::string& filePath);
		bool loadRawRGBA8888(const void* pixels, unsigned int sizeX, unsigned int sizeY); //assumes RGBA format
		GLuint sampler;
		GLuint handle;
		unsigned int slot;
		vec2i size;

		friend class TextureManager;
};

#endif // Texture_HPP
