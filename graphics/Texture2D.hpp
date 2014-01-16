#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP
#include "Texture.hpp"

class Texture2D : public Texture {
	public:
		Texture2D();
		~Texture2D();

		static Texture2D* createEmpty(unsigned int sizeX, unsigned int sizeY, Texture::InternalFormat format = RGBA8, int slot = -1);
		static Texture2D* createFromFile(const std::string& filePath, Texture::SourceFormat sourceFormat = RGBA, Texture::SourceType sourceType = UNSIGNED_BYTE, Texture::InternalFormat internalFormat = RGBA8, bool mipmap = false, int slot = -1);
		static Texture2D* createFromRaw(const void* pixels, unsigned int sizeX, unsigned int sizeY, Texture::SourceFormat sourceFormat = RGBA, Texture::SourceType sourceType = UNSIGNED_BYTE, Texture::InternalFormat internalFormat = RGBA8, bool mipmap = false, int slot = -1);

		void loadEmpty(unsigned int sizeX, unsigned int sizeY, Texture::InternalFormat format = RGBA8, int slot = -1);
		void loadFromFile(const std::string& filePath, Texture::SourceFormat sourceFormat = RGBA, Texture::SourceType sourceType = UNSIGNED_BYTE, Texture::InternalFormat internalFormat = RGBA8, bool mipmap = false, int slot = -1);
		void loadFromRaw(const void* pixels, unsigned int sizeX, unsigned int sizeY, Texture::SourceFormat sourceFormat = RGBA, Texture::SourceType sourceType = UNSIGNED_BYTE, Texture::InternalFormat internalFormat = RGBA8, bool mipmap = false, int slot = -1);

		void resize(unsigned int sizeX, unsigned int sizeY);
		void setComparison(GLenum func, GLenum mode = GL_COMPARE_REF_TO_TEXTURE);
		int getWidth() const;
		int getHeight() const;

		void setFilter(GLenum min, GLenum mag);
		void setWrap(GLenum wrap);
		void bind() const;

	private:
		vec2i size;
};

#endif // TEXTURE2D_HPP
