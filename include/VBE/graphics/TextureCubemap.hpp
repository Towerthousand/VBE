#ifndef TEXTURECUBEMAP_HPP
#define TEXTURECUBEMAP_HPP

#include <memory>
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

		static TextureCubemap load(
				std::vector<std::unique_ptr<std::istream>>& files,
				TextureFormat::Format format = TextureFormat::AUTO);

		TextureCubemap();

		TextureCubemap(
				unsigned int size,
				TextureFormat::Format format = TextureFormat::RGBA);

		void setData(
				const void* pixels,
				TextureFormat::Format sourceFormat = TextureFormat::RGBA,
				TextureFormat::SourceType sourceType = TextureFormat::UNSIGNED_BYTE);

		unsigned int getSize() const;

		static void bind(const TextureCubemap* tex, unsigned int slot) {
			Texture::bind(Texture::TypeCubemap, tex, slot);
		}

		TextureCubemap(TextureCubemap&& rhs);
		TextureCubemap& operator=(TextureCubemap&& rhs);
		friend void swap(TextureCubemap& a, TextureCubemap& b);
	private:
		unsigned int size;
};

#endif // TEXTURECUBEMAP_HPP
