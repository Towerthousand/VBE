#ifndef Texture_HPP
#define Texture_HPP
#include "../tools.hpp"

class Texture {
	public:
		enum SourceFormat {
			DEPTH_COMPONENT	= GL_DEPTH_COMPONENT,
			DEPTH_STENCIL	= GL_DEPTH_STENCIL,
			RED				= GL_RED,
			GREEN			= GL_GREEN,
			BLUE			= GL_BLUE,
			RG				= GL_RG,
			RGB				= GL_RGB,
			RGBA			= GL_RGBA,
			BGR				= GL_BGR,
			BGRA			= GL_BGRA,
			RED_INTEGER		= GL_RED_INTEGER,
			GREEN_INTEGER	= GL_GREEN_INTEGER,
			BLUE_INTEGER	= GL_BLUE_INTEGER,
			RG_INTEGER		= GL_RG_INTEGER,
			RGB_INTEGER		= GL_RGB_INTEGER,
			RGBA_INTEGER	= GL_RGBA_INTEGER,
			BGR_INTEGER		= GL_BGR_INTEGER,
			BGRA_INTEGER	= GL_BGRA_INTEGER
		};
		
		enum InternalFormat	{
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
			RGBA4				= GL_RGBA4,
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

			DEPTH_COMPONENT16	= GL_DEPTH_COMPONENT16,
			DEPTH_COMPONENT24	= GL_DEPTH_COMPONENT24,
			DEPTH_COMPONENT32	= GL_DEPTH_COMPONENT32,
			DEPTH_COMPONENT32F	= GL_DEPTH_COMPONENT32F,
			DEPTH24_STENCIL8	= GL_DEPTH24_STENCIL8,
			DEPTH32F_STENCIL8	= GL_DEPTH32F_STENCIL8
		};

		enum SourceType {
			UNSIGNED_BYTE					= GL_UNSIGNED_BYTE,
			BYTE							= GL_BYTE,
			UNSIGNED_SHORT					= GL_UNSIGNED_SHORT,
			SHORT							= GL_SHORT,
			UNSIGNED_INT					= GL_UNSIGNED_INT,
			INT								= GL_INT,
			HALF_FLOAT						= GL_HALF_FLOAT,
			FLOAT							= GL_FLOAT,
			UNSIGNED_BYTE_3_3_2				= GL_UNSIGNED_BYTE_3_3_2,
			UNSIGNED_BYTE_2_3_3_REV			= GL_UNSIGNED_BYTE_2_3_3_REV,
			UNSIGNED_SHORT_5_6_5			= GL_UNSIGNED_SHORT_5_6_5,
			UNSIGNED_SHORT_5_6_5_REV		= GL_UNSIGNED_SHORT_5_6_5_REV,
			UNSIGNED_SHORT_4_4_4_4			= GL_UNSIGNED_SHORT_4_4_4_4,
			UNSIGNED_SHORT_4_4_4_4_REV		= GL_UNSIGNED_SHORT_4_4_4_4_REV,
			UNSIGNED_SHORT_5_5_5_1			= GL_UNSIGNED_SHORT_5_5_5_1,
			UNSIGNED_SHORT_1_5_5_5_REV		= GL_UNSIGNED_SHORT_1_5_5_5_REV,
			UNSIGNED_INT_8_8_8_8			= GL_UNSIGNED_INT_8_8_8_8,
			UNSIGNED_INT_8_8_8_8_REV		= GL_UNSIGNED_INT_8_8_8_8_REV,
			UNSIGNED_INT_10_10_10_2			= GL_UNSIGNED_INT_10_10_10_2,
			UNSIGNED_INT_2_10_10_10_REV		= GL_UNSIGNED_INT_2_10_10_10_REV,
			UNSIGNED_INT_24_8				= GL_UNSIGNED_INT_24_8,
			UNSIGNED_INT_10F_11F_11F_REV	= GL_UNSIGNED_INT_10F_11F_11F_REV,
			UNSIGNED_INT_5_9_9_9_REV		= GL_UNSIGNED_INT_5_9_9_9_REV,
			FLOAT_32_UNSIGNED_INT_24_8_REV	= GL_FLOAT_32_UNSIGNED_INT_24_8_REV
		};
		
		~Texture();

		static Texture* createEmpty(unsigned int sizeX, unsigned int sizeY, Texture::InternalFormat format = RGBA8, int slot = -1);
		static Texture* createFromFile(const std::string& filePath, Texture::SourceFormat sourceFormat = RGBA, Texture::SourceType sourceType = UNSIGNED_BYTE, Texture::InternalFormat internalFormat = RGBA8, bool mipmap = false, int slot = -1);
		static Texture* createFromRaw(const void* pixels, unsigned int sizeX, unsigned int sizeY, Texture::SourceFormat sourceFormat = RGBA, Texture::SourceType sourceType = UNSIGNED_BYTE, Texture::InternalFormat internalFormat = RGBA8, bool mipmap = false, int slot = -1);


		void loadEmpty(unsigned int sizeX, unsigned int sizeY, Texture::InternalFormat format = RGBA8, int slot = -1);
		void loadFromFile(const std::string& filePath, Texture::SourceFormat sourceFormat = RGBA, Texture::SourceType sourceType = UNSIGNED_BYTE, Texture::InternalFormat internalFormat = RGBA8, bool mipmap = false, int slot = -1);
		void loadFromRaw(const void* pixels, unsigned int sizeX, unsigned int sizeY, Texture::SourceFormat sourceFormat = RGBA, Texture::SourceType sourceType = UNSIGNED_BYTE, Texture::InternalFormat internalFormat = RGBA8, bool mipmap = false, int slot = -1);
		void resize(unsigned int sizeX, unsigned int sizeY);

		void setFilter(GLenum min, GLenum mag);
		void setWrap(GLenum wrap) const;
		void setComparison(GLenum func, GLenum mode = GL_COMPARE_REF_TO_TEXTURE);
		void setSlot(unsigned int newSlot);
		unsigned int getSlot() const;
		int getWidth() const;
		int getHeight() const;
		void bind() const;
		GLuint getHandle() const;
	private:
		Texture();

		GLuint handle;
		unsigned int slot;
		vec2i size;
		InternalFormat format;
		static unsigned int lastSlot;
};

#endif // Texture_HPP
