#ifndef Texture_HPP
#define Texture_HPP

#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/TextureFormat.hpp>
#include <VBE/utils/NonCopyable.hpp>

///
/// \brief Texture is the base class for all the OpenGL texture types.
///
class Texture : public NonCopyable {
    public:
        ///
        /// \brief The Type enum represents the different OpenGL texture Types, used by the subclasses.
        ///
        enum Type {
            Type2D = 0, //< GL_TEXTURE_2D
            Type2DArray, //< GL_TEXTURE_2D_ARRAY
            Type3D, //< GL_TEXTURE_3D
            TypeCubemap, //< GL_TEXTURE_CUBEMAP
            TypeCubemapArray, //< GL_TEXTURE_CUBE_MAP_ARRAY
            TypeCount
        };

        ///
        /// \brief Destructor
        ///
        virtual ~Texture();

        ///
        /// \brief Returns the OpenGL handle of this texture
        ///
        GLuint getHandle() const;

        ///
        /// \brief Returns this texture's pixel format
        ///
        TextureFormat::Format getFormat() const;

        ///
        /// \brief Returns the texture type
        /// \see Texture::Type
        ///
        Type getType() const;

#ifndef VBE_GLES2
        ///
        /// \brief Sets the comparison function and mode
        ///
        void setComparison(GLenum func, GLenum mode = GL_COMPARE_REF_TO_TEXTURE);
#endif
        ///
        /// \brief Sets the minification (when seen from afar) and magnification (when seen from up close) filter
        ///
        void setFilter(GLenum min, GLenum mag);

        ///
        /// \brief Sets the wrap function for texture fetches out of the (0..1) range
        ///
        void setWrap(GLenum wrap);

        ///
        /// \brief Generate mipmap levels
        ///
        /// This function should be called every time the texture data changes to keep mipmapping working
        /// In order to make use of mipmapping, the texture min/mag filters should be
        /// appropiately set to a filter that supports mipmap.
        ///
        /// \see Texture::setFilter
        ///
        void generateMipmap();

        ///
        /// \brief Returns the maximum number of texture that can be binded at the same time
        ///
        static unsigned int getMaxSlots();

        ///
        /// \brief Swap operator for the Texture class
        ///
        friend void swap(Texture& a, Texture& b);
    protected:
        Texture(Type type, TextureFormat::Format format = TextureFormat::RGBA);

        static void bind(Type type, const Texture* tex, unsigned int slot);
        static GLenum typeToGL(Type t);
    private:
        GLuint handle = 0;
        TextureFormat::Format format = TextureFormat::RGB;
        Type type = Type2D;

        static std::vector<std::vector<GLuint>> current;
        static unsigned int currentUnit;
        static int maxSlots;
};

///
/// \class Texture Texture.hpp <VBE/graphics/Texture.hpp>
/// \ingroup Graphics
///
/// This base class provides common functionality that is available for all textures, such as setting
/// the wrapping/filtering/comparing modes.
///

#endif // Texture_HPP
