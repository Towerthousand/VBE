#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <iostream>
#include <memory>

#include <VBE/graphics/Texture.hpp>

///
/// \brief Texture2D represents a GL 2D Texture
///
class Texture2D : public Texture {
    public:
        ///
        /// \brief Loads a new texture from a stream.
        ///
        /// The input stream may be an open file or a user-implemented stream.
        ///
        /// \see Storage
        ///
        static Texture2D load(
                std::unique_ptr<std::istream> in,
                TextureFormat::Format format = TextureFormat::AUTO);

        ///
        /// \brief Default constructor. Generates an invalid texture with no pixels.
        ///
        /// This constructor will generate a texture of size 0. This texture is not
        /// meant for use in rendering.
        ///
        Texture2D();

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
        Texture2D(vec2ui size,
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
        void setData(const void* pixels,
                     TextureFormat::Format sourceFormat = TextureFormat::RGBA,
                     TextureFormat::SourceType sourceType = TextureFormat::UNSIGNED_BYTE);

        ///
        /// \brief Returns the texture size
        ///
        vec2ui getSize() const;

        ///
        /// \brief Bind a texture to any given slot
        ///
        /// Binding this texture will replace whatever texture was previously assigned for this slot
        ///
        static void bind(const Texture2D* tex, unsigned int slot) {
            Texture::bind(Texture::Type2D, tex, slot);
        }

        ///
        /// \brief Move constructor
        ///
        Texture2D(Texture2D&& rhs);

        ///
        /// \brief Move operator=
        ///
        Texture2D& operator=(Texture2D&& rhs);

        ///
        /// \brief Swap operator for the Texture2D class
        ///
        friend void swap(Texture2D& a, Texture2D& b);

    private:
        vec2ui size = vec2ui(0);
};
///
/// \class Texture2D Texture2D.hpp <VBE/graphics/Texture2D.hpp>
/// \ingroup Graphics
///

#endif // TEXTURE2D_HPP
