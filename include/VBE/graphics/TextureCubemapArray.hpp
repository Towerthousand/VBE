#ifndef TEXTURECUBEMAPARRAY_HPP
#define TEXTURECUBEMAPARRAY_HPP

#include <memory>
#include "Texture.hpp"

// Texture arrays are not supported in GLES2
#ifndef VBE_GLES2

///
/// \brief TextureCubemapArray represents a GL Cubemap Array Texture
///
class TextureCubemapArray : public Texture {
	public:
		///
		/// \brief Loads a new texture from a stream.
		///
		/// The input stream may be an open file or a user-implemented stream.
		///
		/// \see Storage
		/// 
		static TextureCubemapArray load(
				std::vector<std::unique_ptr<std::istream>>& files,
				TextureFormat::Format format = TextureFormat::AUTO);

		///
		/// \brief Default constructor. Generates an invalid texture with no pixels.
		///
		/// This constructor will generate a texture of size 0. This texture is not
		/// meant for use in rendering.
		///
		TextureCubemapArray();
		
		///
		/// \brief Size and Format constructor. 
		///
		/// Will create an empty texture with the specified size and format.
		/// The initial contents of the texture are undefined.
		///
		/// \param format Can be sized or not.
		///
		/// \see TextureFormat::Format
		///
		TextureCubemapArray(
				unsigned int size,
				unsigned int slices,
				TextureFormat::Format format = TextureFormat::RGBA);

		///
		/// \brief Sets the content of the texture
		///
		/// The pixels pointer must hold enough data to fill the texture, otherwise the behaviour is undefined
		///
		/// \param sourceFormat The format of the pixels pointer
		/// \param sourceType The data type of the pixels pointer
		/// 
		/// \see TextureFormat::Format
		/// \see TextureFormat::SourceType
		///
		void setData(
				const void* pixels,
				TextureFormat::Format sourceFormat = TextureFormat::RGBA,
				TextureFormat::SourceType sourceType = TextureFormat::UNSIGNED_BYTE);

		///
		/// \brief Returns the texture size
		///
		unsigned int getSize() const;

		///
		/// \brief Returns the number of cubemaps in the array
		///
		unsigned int getSlices() const;

		///
		/// \brief Bind a texture to any given slot
		///
		/// Binding this texture will replace whatever texture was previously assigned for this slot
		///
		static void bind(const TextureCubemapArray* tex, unsigned int slot) {
			Texture::bind(Texture::TypeCubemapArray, tex, slot);
		}

		///
		/// \brief Move constructor
		///
		TextureCubemapArray(TextureCubemapArray&& rhs);
		
		///
		/// \brief Move operator=
		///
		TextureCubemapArray& operator=(TextureCubemapArray&& rhs);
		
		///
		/// \brief Swap operator for the Texture2DArray class
		///
		friend void swap(TextureCubemapArray& a, TextureCubemapArray& b);

	private:
		unsigned int size = 0;
		unsigned int slices = 0;
};
///
/// \class Texture2DArray Texture2DArray.hpp <VBE/graphics/Texture2DArray.hpp>
/// \ingroup Graphics
///

#endif // VBE_GLES2
#endif // TEXTURECUBEMAPARRAY_HPP
