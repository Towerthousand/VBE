#ifndef TEXTURECUBEMAP_HPP
#define TEXTURECUBEMAP_HPP

#include <memory>
#include "Texture.hpp"

///
/// \brief TextureCubemap represents a GL Cubemap Texture
///
class TextureCubemap : public Texture {
    public:

        ///
        /// \brief The cubeFaces enum
        ///
        enum cubeFaces {
            CUBEMAP_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
            CUBEMAP_NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
            CUBEMAP_POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
            CUBEMAP_NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
            CUBEMAP_POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
            CUBEMAP_NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
        };

        ///
        /// \brief Loads a new texture from a stream.
        ///
        /// The input stream may be an open file or a user-implemented stream.
        ///
        /// \see Storage
        ///
        static TextureCubemap load(
                std::vector<std::unique_ptr<std::istream>>& files,
                TextureFormat::Format format = TextureFormat::AUTO);

        ///
        /// \brief Default constructor. Generates an invalid texture with no pixels.
        ///
        /// This constructor will generate a texture of size 0. This texture is not
        /// meant for use in rendering.
        ///
        TextureCubemap();

        ///
        /// \brief Size and Format constructor.
        ///
        /// Will create an empty texture with the specified size and format.
        /// The cube faces are always square (same width and height).
        /// The initial contents of the texture are undefined.
        ///
        /// \param format Can be sized or not.
        ///
        /// \see TextureFormat::Format
        ///
        TextureCubemap(
                unsigned int size,
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
        /// \brief Bind a texture to any given slot
        ///
        /// Binding this texture will replace whatever texture was previously assigned for this slot
        ///
        static void bind(const TextureCubemap* tex, unsigned int slot) {
            Texture::bind(Texture::TypeCubemap, tex, slot);
        }

        ///
        /// \brief Move constructor
        ///
        TextureCubemap(TextureCubemap&& rhs);

        ///
        /// \brief Move operator=
        ///
        TextureCubemap& operator=(TextureCubemap&& rhs);

        ///
        /// \brief Swap operator for the TextureCubemap class
        ///
        friend void swap(TextureCubemap& a, TextureCubemap& b);
    private:
        unsigned int size = 0;
};
///
/// \class TextureCubemap TextureCubemap.hpp <VBE/graphics/TextureCubemap.hpp>
/// \ingroup Graphics
///

#endif // TEXTURECUBEMAP_HPP
