#ifndef TEXTURE3D_HPP
#define TEXTURE3D_HPP
#include "Texture.hpp"

class Texture3D : public Texture {
	public:
		Texture3D();
		~Texture3D();

		static Texture3D* createEmpty(unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ, Texture::InternalFormat format = RGBA8, int slot = -1);
		static Texture3D* createFromRaw(const void* pixels, unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ, Texture::SourceFormat sourceFormat = RGBA, Texture::SourceType sourceType = UNSIGNED_BYTE, Texture::InternalFormat internalFormat = RGBA8, bool mipmap = false, int slot = -1);

		void loadEmpty(unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ, Texture::InternalFormat format = RGBA8, int slot = -1);
		void loadFromRaw(const void* pixels, unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ, Texture::SourceFormat sourceFormat = RGBA, Texture::SourceType sourceType = UNSIGNED_BYTE, Texture::InternalFormat internalFormat = RGBA8, bool mipmap = false, int slot = -1);

		void resize(unsigned int sizeX, unsigned int sizeY, unsigned sizeZ);
		int getWidth() const;
		int getHeight() const;
		int getDepth() const;

		void setFilter(GLenum min, GLenum mag);
		void setWrap(GLenum wrap);
		void bind() const;

	private:
		vec3i size;
};

#endif // Texture3D_HPP
