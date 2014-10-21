#ifndef Texture_HPP
#define Texture_HPP

#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/TextureFormat.hpp>
#include <VBE/utils/NonCopyable.hpp>

class Texture : public NonCopyable {
	public:
		enum Type {
			Type2D,
			Type2DArray,
			Type3D,
			TypeCubemap,
			TypeCount
		};

		static GLenum typeToGL(Type t) {
			switch(t) {
				case Type2D: return GL_TEXTURE_2D;
				case Type2DArray: return GL_TEXTURE_2D_ARRAY;
				case Type3D: return GL_TEXTURE_3D;
				case TypeCubemap: return GL_TEXTURE_CUBE_MAP;
				default:
					VBE_ASSERT(false, "Invalid Texture::Type value: " << t);
					return 0;
			}
		}

		virtual ~Texture();

		void setSlot(unsigned int newSlot);
		unsigned int getSlot() const;
		GLuint getHandle() const;
		TextureFormat::Format getFormat() const;
		Type getType() const;

#ifndef VBE_GLES2
		void setComparison(GLenum func, GLenum mode = GL_COMPARE_REF_TO_TEXTURE);
#endif
		void setFilter(GLenum min, GLenum mag);
		void setWrap(GLenum wrap);

		static unsigned int getMaxSlots();

	protected:
		Texture(Type type);

		GLuint handle;
		unsigned int slot;
		TextureFormat::Format format;

		static void bind(Type type, const Texture* tex);
	private:
		Type type;

		static unsigned int lastSlot;
		static int maxSlots;
		static const Texture* current[TypeCount];
};

#endif // Texture_HPP
