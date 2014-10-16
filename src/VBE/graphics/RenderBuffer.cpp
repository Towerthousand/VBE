#include "RenderBuffer.hpp"

RenderBuffer::RenderBuffer(int width, int height, TextureFormat::Format format) : format(format){
	GL_ASSERT(glGenRenderbuffers(1, &handle));
	resize(width, height);
}

RenderBuffer::~RenderBuffer() {
	GL_ASSERT(glDeleteRenderbuffers(1, &handle));
}

void RenderBuffer::resize(int width, int height) {
	bind();
	GL_ASSERT(glRenderbufferStorage(GL_RENDERBUFFER, format, width, height));
}

void RenderBuffer::bind() const {
	GL_ASSERT(glBindRenderbuffer(GL_RENDERBUFFER, handle));
}

GLuint RenderBuffer::getHandle() const {
	return handle;
}
