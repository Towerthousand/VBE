#ifndef Texture_HPP
#define Texture_HPP

#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/TextureFormat.hpp>
#include <VBE/utils/NonCopyable.hpp>

class Texture : public NonCopyable {
	public:
		enum Type {
			Type2D = GL_TEXTURE_2D,
			Type2DArray = GL_TEXTURE_2D_ARRAY,
			Type3D = GL_TEXTURE_3D,
			TypeCubemap = GL_TEXTURE_CUBE_MAP,
			TypeCount
		};

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
		static const Texture** current;
};

#endif // Texture_HPP
