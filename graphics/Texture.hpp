#ifndef Texture_HPP
#define Texture_HPP
#include "../tools.hpp"

class Texture
{
	public:
		Texture(unsigned int slot);
		~Texture();

		bool loadFromFile(const std::string& filePath, bool mipmap = false);
		bool loadRawRGBA8888(const void* pixels, unsigned int sizeX, unsigned int sizeY, bool mipmap = false); //assumes RGBA format

		void setFilter(GLenum min, GLenum mag);
		void setWrap(GLenum wrap) const;
		void setSlot(unsigned int newSlot);
		unsigned int getSlot() const;
		int getWidth() const;
		int getHeight() const;
		void bind() const;
	private:
		GLuint getHandle() const;
		GLuint sampler;
		GLuint handle;
		unsigned int slot;
		vec2i size;
};

#endif // Texture_HPP
