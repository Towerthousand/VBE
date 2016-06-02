#ifndef TextureFormat_HPP
#define TextureFormat_HPP

#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/system/Log.hpp>

///
/// \brief In the TextureFormat class you will find enums for all sized and base GL pixel formats and pixel source types
///
class TextureFormat {
    public:

        ///
        /// \brief The Format enum has all available formats, sized and unsized.
        ///
        /// Sized formats are only available on Desktop OpenGL. The only formats
        /// available in the GLES2 spec are ALPHA, RGB, RGBA, LUMINANCE, RED and LUMINANCE_ALPHA.
        /// Furthermore, ALPHA, LUMINANCE and LUMINANCE_ALPHA are only available on GLES2
        ///
        enum Format {
            AUTO = 0,

#ifdef VBE_GLES2
            ALPHA           = GL_ALPHA,
            RGB             = GL_RGB,
            RGBA            = GL_RGBA,
            LUMINANCE       = GL_LUMINANCE,
            RED             = GL_LUMINANCE,
            LUMINANCE_ALPHA = GL_LUMINANCE_ALPHA,
#else
            DEPTH_COMPONENT	= GL_DEPTH_COMPONENT,
            DEPTH_STENCIL	= GL_DEPTH_STENCIL,
            RED				= GL_RED,
            RG				= GL_RG,
            RGB				= GL_RGB,
            RGBA			= GL_RGBA,
            BGR				= GL_BGR,
            BGRA			= GL_BGRA,
            RED_INTEGER		= GL_RED_INTEGER,
            RG_INTEGER		= GL_RG_INTEGER,
            RGB_INTEGER		= GL_RGB_INTEGER,
            RGBA_INTEGER	= GL_RGBA_INTEGER,
            BGR_INTEGER		= GL_BGR_INTEGER,
            BGRA_INTEGER	= GL_BGRA_INTEGER,
#endif

            // Sized formats, only in desktop OpenGL
#ifndef VBE_GLES2
            R8					= GL_R8,
            R8_SNORM			= GL_R8_SNORM,
            R8I					= GL_R8I,
            R8UI				= GL_R8UI,
            R16					= GL_R16,
            R16_SNORM			= GL_R16_SNORM,
            R16F				= GL_R16F,
            R16I				= GL_R16I,
            R16UI				= GL_R16UI,
            R32F				= GL_R32F,
            R32I				= GL_R32I,
            R32UI				= GL_R32UI,

            RG8					= GL_RG8,
            RG8_SNORM			= GL_RG8_SNORM,
            RG8I				= GL_RG8I,
            RG8UI				= GL_RG8UI,
            RG16				= GL_RG16,
            RG16_SNORM			= GL_RG16_SNORM,
            RG16F				= GL_RG16F,
            RG16I				= GL_RG16I,
            RG16UI				= GL_RG16UI,
            RG32F				= GL_RG32F,
            RG32I				= GL_RG32I,
            RG32UI				= GL_RG32UI,

            RGB4				= GL_RGB4,
            RGB5				= GL_RGB5,
            RGB8				= GL_RGB8,
            RGB8_SNORM			= GL_RGB8_SNORM,
            RGB8I				= GL_RGB8I,
            RGB8UI				= GL_RGB8UI,
            RGB10				= GL_RGB10,
            RGB12				= GL_RGB12,
            RGB16_SNORM			= GL_RGB16_SNORM,
            RGB16F				= GL_RGB16F,
            RGB16I				= GL_RGB16I,
            RGB16UI				= GL_RGB16UI,
            RGB32F				= GL_RGB32F,
            RGB32I				= GL_RGB32I,
            RGB32UI				= GL_RGB32UI,

            RGBA2				= GL_RGBA2,
            RGBA8				= GL_RGBA8,
            RGBA8_SNORM			= GL_RGBA8_SNORM,
            RGBA12				= GL_RGBA12,
            RGBA16				= GL_RGBA16,
            RGBA16F				= GL_RGBA16F,
            RGBA32F				= GL_RGBA32F,
            RGBA8I				= GL_RGBA8I,
            RGBA8UI				= GL_RGBA8UI,
            RGBA16I				= GL_RGBA16I,
            RGBA16UI			= GL_RGBA16UI,
            RGBA32I				= GL_RGBA32I,
            RGBA32UI			= GL_RGBA32UI,

            DEPTH_COMPONENT24	= GL_DEPTH_COMPONENT24,
            DEPTH_COMPONENT32	= GL_DEPTH_COMPONENT32,
            DEPTH_COMPONENT32F	= GL_DEPTH_COMPONENT32F,
            DEPTH24_STENCIL8	= GL_DEPTH24_STENCIL8,
            DEPTH32F_STENCIL8	= GL_DEPTH32F_STENCIL8,

            SRGB8				= GL_SRGB8,
            SRGBA8				= GL_SRGB8_ALPHA8,
#endif
        };

        ///
        /// \brief The Format enum has all available formats, sized and unsized.
        ///
        /// Most sized are only available on Desktop OpenGL. The only types
        /// available in the GLES2 spec are INT, USIGNED_BYTE, UNSIGNED_SHORT_5_6_5,
        /// UNSIGNED_SHORT_4_4_4_4 and UNSIGNED_SHORT_5_5_5_1.
        ///
        enum SourceType {
            INT								= GL_INT,
            UNSIGNED_BYTE					= GL_UNSIGNED_BYTE,
            UNSIGNED_SHORT_5_6_5			= GL_UNSIGNED_SHORT_5_6_5,
            UNSIGNED_SHORT_4_4_4_4			= GL_UNSIGNED_SHORT_4_4_4_4,
            UNSIGNED_SHORT_5_5_5_1			= GL_UNSIGNED_SHORT_5_5_5_1,

#ifndef VBE_GLES2
            BYTE							= GL_BYTE,
            UNSIGNED_SHORT					= GL_UNSIGNED_SHORT,
            SHORT							= GL_SHORT,
            UNSIGNED_INT					= GL_UNSIGNED_INT,
            HALF_FLOAT						= GL_HALF_FLOAT,
            FLOAT							= GL_FLOAT,
            UNSIGNED_BYTE_3_3_2				= GL_UNSIGNED_BYTE_3_3_2,
            UNSIGNED_BYTE_2_3_3_REV			= GL_UNSIGNED_BYTE_2_3_3_REV,
            UNSIGNED_SHORT_5_6_5_REV		= GL_UNSIGNED_SHORT_5_6_5_REV,
            UNSIGNED_SHORT_4_4_4_4_REV		= GL_UNSIGNED_SHORT_4_4_4_4_REV,
            UNSIGNED_SHORT_1_5_5_5_REV		= GL_UNSIGNED_SHORT_1_5_5_5_REV,
            UNSIGNED_INT_8_8_8_8			= GL_UNSIGNED_INT_8_8_8_8,
            UNSIGNED_INT_8_8_8_8_REV		= GL_UNSIGNED_INT_8_8_8_8_REV,
            UNSIGNED_INT_10_10_10_2			= GL_UNSIGNED_INT_10_10_10_2,
            UNSIGNED_INT_2_10_10_10_REV		= GL_UNSIGNED_INT_2_10_10_10_REV,
            UNSIGNED_INT_24_8				= GL_UNSIGNED_INT_24_8,
            UNSIGNED_INT_10F_11F_11F_REV	= GL_UNSIGNED_INT_10F_11F_11F_REV,
            UNSIGNED_INT_5_9_9_9_REV		= GL_UNSIGNED_INT_5_9_9_9_REV,
            FLOAT_32_UNSIGNED_INT_24_8_REV	= GL_FLOAT_32_UNSIGNED_INT_24_8_REV
#endif
        };

        ///
        /// \brief Returns base format of any given format.
        ///
        /// Base format for any format is commonly the same format
        /// without any specific channel width
        ///
        inline static Format getBaseFormat(Format f) {
            switch(f) {
#ifndef VBE_GLES2
                case R8:
                case R8_SNORM:
                case R8I:
                case R8UI:
                case R16:
                case R16_SNORM:
                case R16F:
                case R16I:
                case R16UI:
                case R32F:
                case R32I:
                case R32UI:
                    return RED;
                case RG8:
                case RG8_SNORM:
                case RG8I:
                case RG8UI:
                case RG16:
                case RG16_SNORM:
                case RG16F:
                case RG16I:
                case RG16UI:
                case RG32F:
                case RG32I:
                case RG32UI:
                    return RG;
                case RGB4:
                case RGB5:
                case RGB8:
                case RGB8_SNORM:
                case RGB8I:
                case RGB8UI:
                case RGB10:
                case RGB12:
                case RGB16_SNORM:
                case RGB16F:
                case RGB16I:
                case RGB16UI:
                case RGB32F:
                case RGB32I:
                case RGB32UI:
                    return RGB;
                case RGBA2:
                case RGBA8:
                case RGBA8_SNORM:
                case RGBA12:
                case RGBA16:
                case RGBA16F:
                case RGBA32F:
                case RGBA8I:
                case RGBA8UI:
                case RGBA16I:
                case RGBA16UI:
                case RGBA32I:
                case RGBA32UI:
                    return RGBA;
                case DEPTH_COMPONENT24:
                case DEPTH_COMPONENT32:
                case DEPTH_COMPONENT32F:
                    return DEPTH_COMPONENT;
                case DEPTH24_STENCIL8:
                case DEPTH32F_STENCIL8:
                    return DEPTH_STENCIL;
                case SRGB8:
                    return RGB;
                case SRGBA8:
                    return RGBA;
#endif
                default:
                    return f;
            }
        }

        ///
        /// \brief Returns base format for any given number of channels.
        ///
        /// On GLES2 there is no ordinary 2-channel texture format so that
        /// is not supported.
        ///
        inline static Format channelsToFormat(int channels) {
            switch(channels) {
                case 1:
                    return RED;
#ifndef VBE_GLES2
                    // The closest we can get to a 2-component texture in GLES2 is
                    // LUMINANCE_ALPHA, but it behaves differently when reading it
                    // so it's not compatible.
                case 2:
                    return RG;
#endif
                case 3:
                    return RGB;
                case 4:
                    return RGBA;
                default:
                    VBE_ASSERT(false, "Invalid component count: " << channels);
                    return RGBA;
            }
        }

#ifndef VBE_GLES2

        ///
        /// \brief Returns wether the given format has a depth channel or not
        ///
        inline static bool isDepth(Format f) {
            switch(f) {
                case DEPTH24_STENCIL8:
                case DEPTH32F_STENCIL8:
                case DEPTH_COMPONENT:
                case DEPTH_COMPONENT24:
                case DEPTH_COMPONENT32:
                case DEPTH_COMPONENT32F:
                case DEPTH_STENCIL:
                    return true;
                default:
                    return false;
            }
            return false;
        }

        ///
        /// \brief Returns wether the given format is a base format or not
        ///
        inline static bool isBaseFormat(Format f) {
            return f == TextureFormat::getBaseFormat(f);
        }
#endif

    private:
        TextureFormat();
};
///
/// \class TextureFormat TextureFormat.hpp <VBE/graphics/TextureFormat.hpp>
///	\ingroup Graphics
///
///

#endif // TextureFormat_HPP


