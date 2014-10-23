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

		void loadFromFiles(
				const std::vector<std::string>& filePaths,
				TextureFormat::Format internalFormat = TextureFormat::AUTO);

		void loadEmpty(
				unsigned int size,
				TextureFormat::Format internalFormat = TextureFormat::RGBA);

		void loadFromRaw(
				const void* pixels,
				unsigned int size,
				TextureFormat::Format sourceFormat = TextureFormat::RGBA,
				TextureFormat::SourceType sourceType = TextureFormat::UNSIGNED_BYTE,
				TextureFormat::Format internalFormat = TextureFormat::AUTO);

		unsigned int getSize() const;

		static void bind(const TextureCubemap* tex, unsigned int slot) {
			Texture::bind(Texture::TypeCubemap, tex, slot);
		}

	private:
		unsigned int size;
};

#endif // TEXTURECUBEMAP_HPP
