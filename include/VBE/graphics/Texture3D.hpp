#ifndef TEXTURE3D_HPP
#define TEXTURE3D_HPP
#include "Texture.hpp"

// 3D textures are not supported in GLES2
#ifndef VBE_GLES2

class Texture3D : public Texture {
	public:
		Texture3D();

		void loadEmpty(
				vec3ui size,
				TextureFormat::Format internalFormat = TextureFormat::RGBA);

		void loadFromRaw(
				const void* pixels,
				vec3ui size,
				TextureFormat::Format sourceFormat = TextureFormat::RGBA,
				TextureFormat::SourceType sourceType = TextureFormat::UNSIGNED_BYTE,
				TextureFormat::Format internalFormat = TextureFormat::AUTO);

		vec3ui getSize() const;

		static void bind(const Texture3D* tex, unsigned int slot) {
			Texture::bind(Texture::Type3D, tex, slot);
		}

	private:
		vec3ui size;
};

#endif // VBE_GLES2

#endif // Texture3D_HPP

