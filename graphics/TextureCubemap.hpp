#ifndef TEXTURECUBEMAP_HPP
#define TEXTURECUBEMAP_HPP
#include "Texture.hpp"

class TextureCubemap : public Texture {
	public:

		enum cubeFaces {
			CUBEMAP_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			CUBEMAP_NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			CUBEMAP_POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			CUBEMAP_NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			CUBEMAP_POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			CUBEMAP_NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
		};

		TextureCubemap();
		~TextureCubemap();

		static TextureCubemap* createEmpty(unsigned int size, Texture::InternalFormat format = RGBA8, int slot = -1);
		static TextureCubemap* createFromFiles(const std::vector<std::string>& filePaths, Texture::SourceFormat sourceFormat = RGBA, Texture::SourceType sourceType = UNSIGNED_BYTE, Texture::InternalFormat internalFormat = RGBA8, bool mipmap = false, int slot = -1);
		static TextureCubemap* createFromRaw(const void* pixels, unsigned int size, Texture::SourceFormat sourceFormat = RGBA, Texture::SourceType sourceType = UNSIGNED_BYTE, Texture::InternalFormat internalFormat = RGBA8, bool mipmap = false, int slot = -1);

		void loadEmpty(unsigned int size, Texture::InternalFormat format = RGBA8, int slot = -1);
		void loadFromFiles(const std::vector<std::string>& filePaths, Texture::SourceFormat sourceFormat = RGBA, Texture::SourceType sourceType = UNSIGNED_BYTE, Texture::InternalFormat internalFormat = RGBA8, bool mipmap = false, int slot = -1);
		void loadFromRaw(const void* pixels, unsigned int size, Texture::SourceFormat sourceFormat = RGBA, Texture::SourceType sourceType = UNSIGNED_BYTE, Texture::InternalFormat internalFormat = RGBA8, bool mipmap = false, int slot = -1);

		void resize(unsigned int newSize);
		void setComparison(GLenum func, GLenum mode = GL_COMPARE_REF_TO_TEXTURE);
		int getWidth() const;
		int getHeight() const;

		void setFilter(GLenum min, GLenum mag);
		void setWrap(GLenum wrap);
		void bind() const;

	private:
		int size;
};

#endif // TEXTURECUBEMAP_HPP
