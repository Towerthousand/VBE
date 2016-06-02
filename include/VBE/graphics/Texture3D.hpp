#ifndef TEXTURE3D_HPP
#define TEXTURE3D_HPP
#include "Texture.hpp"

// 3D textures are not supported in GLES2
#ifndef VBE_GLES2

///
/// \brief The Texture3D class represents a GL 3D Texture
///
class Texture3D : public Texture {
    public:
        ///
        /// \brief Default constructor. Generates invalid texture with no pixels
        ///
        /// This constructor will generate a texture of size 0. This texture is not
        /// meant for use in rendering.
        ///
        Texture3D();

        ///
        /// \brief Size and Format constructor.
        ///
        /// Will create an empty texture with the specified size and format.
        /// The initial contents of the texture are undefined.
        ///
        /// \param internalFormat Can be sized or not.
        ///
        /// \see TextureFormat::Format
        ///
        Texture3D(
                vec3ui size,
                TextureFormat::Format internalFormat = TextureFormat::RGBA);

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
        static void bind(const Texture3D* tex, unsigned int slot) {
            Texture::bind(Texture::Type3D, tex, slot);
        }

        ///
        /// \brief Move constructor
        ///
        Texture3D(Texture3D&& rhs);

        ///
        /// \brief Move operator=
        ///
        Texture3D& operator=(Texture3D&& rhs);

        ///
        /// \brief Swap operator for the Texture3D class
        ///
        friend void swap(Texture3D& a, Texture3D& b);

    private:
        vec3ui size = vec3ui(0);
};
///
/// \class Texture3D Texture3D.hpp <VBE/graphics/Texture3D.hpp>
/// \ingroup Graphics
///

#endif // VBE_GLES2

#endif // Texture3D_HPP

