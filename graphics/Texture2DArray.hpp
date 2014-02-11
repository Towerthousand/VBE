#ifndef TEXTURE2DARRAY_HPP
#define TEXTURE2DARRAY_HPP
#include "Texture.hpp"

class Texture2DArray : public Texture {
	public:
		Texture2DArray();
		~Texture2DArray();

		static Texture2DArray* createEmpty(unsigned int sizeX, unsigned int sizeY, unsigned int slices, Texture::InternalFormat format = RGBA8, int slot = -1);
		static Texture2DArray* createFromFiles(const std::vector<std::string>& filePaths, Texture::SourceFormat sourceFormat = RGBA, Texture::SourceType sourceType = UNSIGNED_BYTE, Texture::InternalFormat internalFormat = RGBA8, bool mipmap = false, int slot = -1);
		static Texture2DArray* createFromRaw(const void* pixels, unsigned int sizeX, unsigned int sizeY, unsigned int slices, Texture::SourceFormat sourceFormat = RGBA, Texture::SourceType sourceType = UNSIGNED_BYTE, Texture::InternalFormat internalFormat = RGBA8, bool mipmap = false, int slot = -1);

		void loadEmpty(unsigned int sizeX, unsigned int sizeY, unsigned int slices, Texture::InternalFormat format = RGBA8, int slot = -1);
		void loadFromFiles(const std::vector<std::string>& filePaths, Texture::SourceFormat sourceFormat = RGBA, Texture::SourceType sourceType = UNSIGNED_BYTE, Texture::InternalFormat internalFormat = RGBA8, bool mipmap = false, int slot = -1);
		void loadFromRaw(const void* pixels, unsigned int sizeX, unsigned int sizeY, unsigned int slices, Texture::SourceFormat sourceFormat = RGBA, Texture::SourceType sourceType = UNSIGNED_BYTE, Texture::InternalFormat internalFormat = RGBA8, bool mipmap = false, int slot = -1);

		void resize(unsigned int sizeX, unsigned int sizeY, unsigned int slices);
		void setComparison(GLenum func, GLenum mode = GL_COMPARE_REF_TO_TEXTURE);
		int getWidth()  const;
		int getHeight() const;
		int getSlices() const;

		void setFilter(GLenum min, GLenum mag);
		void setWrap(GLenum wrap);
		void bind() const;

	private:
		vec3i size;
};

#endif // TEXTURE2DARRAY_HPP
