#ifndef TEXTURE3D_HPP
#define TEXTURE3D_HPP
#include "Texture.hpp"


// 3D textures are not supported in GLES2
#ifndef VBE_GLES2

class Texture3D : public Texture {
	public:
		~Texture3D();

		static Texture3D* createFromRaw(
				const void* pixels,
				unsigned int sizeX,
				unsigned int sizeY,
				unsigned int sizeZ,
				TextureFormat::Format format = TextureFormat::RGBA,
				TextureFormat::SourceType sourceType = TextureFormat::UNSIGNED_BYTE);

		static Texture3D* createEmpty(
				unsigned int sizeX,
				unsigned int sizeY,
				unsigned int sizeZ,
				TextureFormat::Format format = TextureFormat::RGBA);

		void loadFromRaw(
			const void* pixels,
				unsigned int sizeX,
				unsigned int sizeY,
				unsigned int sizeZ,
				TextureFormat::Format format = TextureFormat::RGBA,
				TextureFormat::SourceType sourceType = TextureFormat::UNSIGNED_BYTE);

		void loadEmpty(
				unsigned int sizeX,
				unsigned int sizeY,
				unsigned int sizeZ,
				TextureFormat::Format format = TextureFormat::RGBA);

		void resize(unsigned int sizeX, unsigned int sizeY, unsigned sizeZ);
		int getWidth() const;
		int getHeight() const;
		int getDepth() const;

		void setFilter(GLenum min, GLenum mag);
		void setWrap(GLenum wrap);
		void bind() const;

	private:
		Texture3D();
		vec3i size;
};

#endif // VBE_GLES2

#endif // Texture3D_HPP

