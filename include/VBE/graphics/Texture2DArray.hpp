#ifndef TEXTURE2DARRAY_HPP
#define TEXTURE2DARRAY_HPP

#include <memory>
#include "Texture.hpp"

// Texture arrays are not supported in GLES2
#ifndef VBE_GLES2

///
/// \brief Texture2DArray represents a GL 2D Array Texture
///
class Texture2DArray : public Texture {
    public:
        ///
        /// \brief Loads a new texture from a stream.
        ///
        /// The input stream may be an open file or a user-implemented stream.
        ///
        /// \see Storage
        ///
        static Texture2DArray load(
                std::vector<std::unique_ptr<std::istream>>& files,
                TextureFormat::Format format = TextureFormat::AUTO);

        ///
        /// \brief Default constructor. Generates an invalid texture with no pixels.
        ///
        /// This constructor will generate a texture of size 0. This texture is not
        /// meant for use in rendering.
        ///
        Texture2DArray();

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
        Texture2DArray(
                vec3ui size,
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
        vec3ui getSize() const;

        ///
        /// \brief Bind a texture to any given slot
        ///
        /// Binding this texture will replace whatever texture was previously assigned for this slot
        ///
        static void bind(const Texture2DArray* tex, unsigned int slot) {
            Texture::bind(Texture::Type2DArray, tex, slot);
        }

        ///
        /// \brief Move constructor
        ///
        Texture2DArray(Texture2DArray&& rhs);

        ///
        /// \brief Move operator=
        ///
        Texture2DArray& operator=(Texture2DArray&& rhs);

        ///
        /// \brief Swap operator for the Texture2DArray class
        ///
        friend void swap(Texture2DArray& a, Texture2DArray& b);

    private:
        vec3ui size = vec3ui(0);
};
///
/// \class Texture2DArray Texture2DArray.hpp <VBE/graphics/Texture2DArray.hpp>
/// \ingroup Graphics
///

#endif // VBE_GLES2
#endif // TEXTURE2DARRAY_HPP
