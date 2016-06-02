#include <VBE/graphics/RenderBuffer.hpp>

RenderBuffer::RenderBuffer() {
}

RenderBuffer::RenderBuffer(vec2ui size, TextureFormat::Format format) : size(size), format(format) {
    GL_ASSERT(glGenRenderbuffers(1, &handle));
    resize(size);
}

RenderBuffer::RenderBuffer(RenderBuffer&& rhs) : RenderBuffer() {
    using std::swap;
    swap(*this, rhs);
}

RenderBuffer& RenderBuffer::operator=(RenderBuffer&& rhs) {
    using std::swap;
    swap(*this, rhs);
    return *this;
}

RenderBuffer::~RenderBuffer() {
    if(handle != 0) {
        GL_ASSERT(glDeleteRenderbuffers(1, &handle));
    }
}

void swap(RenderBuffer& a, RenderBuffer& b) {
    using std::swap;

    swap(a.format, b.format);
    swap(a.size, b.size);
    swap(a.handle, b.handle);
}

void RenderBuffer::resize(vec2ui size) {
    if(handle == 0) return;
    bind();
    GL_ASSERT(glRenderbufferStorage(GL_RENDERBUFFER, format, size.x, size.y));
    this->size = size;
}

vec2ui RenderBuffer::getSize() const {
    return size;
}

void RenderBuffer::bind() const {
    if(handle == 0) return;
    GL_ASSERT(glBindRenderbuffer(GL_RENDERBUFFER, handle));
}

GLuint RenderBuffer::getHandle() const {
    return handle;
}
