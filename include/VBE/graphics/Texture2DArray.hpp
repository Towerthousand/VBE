#ifndef TEXTURE2DARRAY_HPP
#define TEXTURE2DARRAY_HPP
#include "Texture.hpp"

// Texture arrays are not supported in GLES2
#ifndef VBE_GLES2

class Texture2DArray : public Texture {
	public:
		Texture2DArray();

		void loadFromFiles(
				const std::vector<std::string>& filePaths,
				TextureFormat::Format internalFormat = TextureFormat::AUTO);

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

		static void bind(const Texture2DArray* tex) {
			Texture::bind(Texture::Type2DArray, tex);
		}

	private:
		vec3ui size;
};

#endif // VBE_GLES2
#endif // TEXTURE2DARRAY_HPP
