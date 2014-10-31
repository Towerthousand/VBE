#include <VBE/graphics/RenderBuffer.hpp>

RenderBuffer::RenderBuffer(vec2ui size, TextureFormat::Format format) : size(size), format(format), handle(0){
	GL_ASSERT(glGenRenderbuffers(1, &handle));
	resize(size);
}

RenderBuffer::~RenderBuffer() {
	GL_ASSERT(glDeleteRenderbuffers(1, &handle));
}

void RenderBuffer::resize(vec2ui size) {
	bind();
	GL_ASSERT(glRenderbufferStorage(GL_RENDERBUFFER, format, size.x, size.y));
}

vec2ui RenderBuffer::getSize() const {
	return size;
}

void RenderBuffer::bind() const {
	GL_ASSERT(glBindRenderbuffer(GL_RENDERBUFFER, handle));
}

GLuint RenderBuffer::getHandle() const {
	return handle;
}
