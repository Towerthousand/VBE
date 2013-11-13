#ifndef Texture_HPP
#define Texture_HPP
#include "../tools.hpp"

class Texture {
	public:
		enum Format {
			DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
			DEPTH_STENCIL = GL_DEPTH_STENCIL,
			RED = GL_RED,
			GREEN = GL_GREEN,
			BLUE = GL_BLUE,
			RG = GL_RG,
			RGB = GL_RGB,
			RED_INTEGER = GL_RED_INTEGER,
			GREEN_INTEGER = GL_GREEN_INTEGER,
			BLUE_INTEGER = GL_BLUE_INTEGER,
			RG_INTEGER = GL_RG_INTEGER,
			RGB_INTEGER = GL_RGB_INTEGER,
			RGBA_INTEGER = GL_RGBA_INTEGER,
			BGR_INTEGER = GL_BGR_INTEGER,
			BGRA_INTEGER = GL_BGRA_INTEGER,
			RGBA = GL_RGBA,
			BGR = GL_BGR,
			BGRA = GL_BGRA
		};

		~Texture();

		static Texture* loadFromFile(const std::string& filePath, Texture::Format format = Texture::RGBA, bool mipmap = false, int slot = -1);
		static Texture* loadFromRaw(const void* pixels, unsigned int sizeX, unsigned int sizeY, Texture::Format format = Texture::RGBA, bool mipmap = false, int slot = -1);

		void setFilter(GLenum min, GLenum mag);
		void setWrap(GLenum wrap) const;
		void setComparison(GLenum func, GLenum mode = GL_COMPARE_REF_TO_TEXTURE);
		void setSlot(unsigned int newSlot);
		unsigned int getSlot() const;
		int getWidth() const;
		int getHeight() const;
		void bind() const;
		GLuint getHandle() const;
	private:
		Texture();

		GLuint handle;
		unsigned int slot;
		vec2i size;
		Format format;
		static unsigned int lastSlot;
};

#endif // Texture_HPP
