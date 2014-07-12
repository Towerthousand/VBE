#ifndef RENDERBUFFER_HPP
#define RENDERBUFFER_HPP
#include "../tools.hpp"
#include "Texture.hpp"

class RenderBuffer {
	public:
		RenderBuffer(int width, int height, Texture::InternalFormat format);
		~RenderBuffer();

		void resize(int width, int height);
		void bind() const;
		GLuint getHandle() const;
	private:
		Texture::InternalFormat format;
		GLuint handle;
};

#endif // RENDERBUFFER_HPP
