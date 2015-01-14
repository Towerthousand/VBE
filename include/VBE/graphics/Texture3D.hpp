#ifndef TEXTURE3D_HPP
#define TEXTURE3D_HPP
#include "Texture.hpp"

// 3D textures are not supported in GLES2
#ifndef VBE_GLES2

class Texture3D : public Texture {
	public:
		Texture3D();

		Texture3D(
				vec3ui size,
				TextureFormat::Format internalFormat = TextureFormat::RGBA);

		void setData(
				const void* pixels,
				TextureFormat::Format sourceFormat = TextureFormat::RGBA,
				TextureFormat::SourceType sourceType = TextureFormat::UNSIGNED_BYTE);

		vec3ui getSize() const;

		static void bind(const Texture3D* tex, unsigned int slot) {
			Texture::bind(Texture::Type3D, tex, slot);
		}

		Texture3D(Texture3D&& rhs);
		Texture3D& operator=(Texture3D&& rhs);
		friend void swap(Texture3D& a, Texture3D& b);

	private:
		vec3ui size = vec3ui(0);
};

#endif // VBE_GLES2

#endif // Texture3D_HPP

