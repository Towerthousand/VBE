#ifndef TEXTURE2DARRAY_HPP
#define TEXTURE2DARRAY_HPP

#include <memory>
#include "Texture.hpp"

// Texture arrays are not supported in GLES2
#ifndef VBE_GLES2

class Texture2DArray : public Texture {
	public:

		static Texture2DArray load(
				std::vector<std::unique_ptr<std::istream>>& files,
				TextureFormat::Format format = TextureFormat::AUTO);

		Texture2DArray();
		Texture2DArray(
				vec3ui size,
				TextureFormat::Format format = TextureFormat::RGBA);

		void setData(
				const void* pixels,
				TextureFormat::Format sourceFormat = TextureFormat::RGBA,
				TextureFormat::SourceType sourceType = TextureFormat::UNSIGNED_BYTE);

		vec3ui getSize() const;

		static void bind(const Texture2DArray* tex, unsigned int slot) {
			Texture::bind(Texture::Type2DArray, tex, slot);
		}

		Texture2DArray(Texture2DArray&& rhs);
		Texture2DArray& operator=(Texture2DArray&& rhs);
		friend void swap(Texture2DArray& a, Texture2DArray& b);

	private:
		vec3ui size = vec3ui(0);
};

#endif // VBE_GLES2
#endif // TEXTURE2DARRAY_HPP
