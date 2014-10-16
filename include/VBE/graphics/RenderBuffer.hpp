#ifndef RENDERBUFFER_HPP
#define RENDERBUFFER_HPP

#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/TextureFormat.hpp>

class RenderBuffer {
	public:
		RenderBuffer(int width, int height, TextureFormat::Format format);
		~RenderBuffer();

		void resize(int width, int height);
		void bind() const;
		GLuint getHandle() const;
	private:
		TextureFormat::Format format;
		GLuint handle;
};

#endif // RENDERBUFFER_HPP
