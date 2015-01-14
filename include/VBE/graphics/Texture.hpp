#ifndef Texture_HPP
#define Texture_HPP

#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/TextureFormat.hpp>
#include <VBE/utils/NonCopyable.hpp>

class Texture : public NonCopyable {
	public:
		enum Type {
			Type2D = 0,
			Type2DArray,
			Type3D,
			TypeCubemap,
			TypeCount
		};

		virtual ~Texture();

		GLuint getHandle() const;
		TextureFormat::Format getFormat() const;
		Type getType() const;

#ifndef VBE_GLES2
		void setComparison(GLenum func, GLenum mode = GL_COMPARE_REF_TO_TEXTURE);
#endif
		void setFilter(GLenum min, GLenum mag);
		void setWrap(GLenum wrap);
		static unsigned int getMaxSlots();

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

#endif // Texture_HPP
