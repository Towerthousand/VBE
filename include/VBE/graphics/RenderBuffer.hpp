#ifndef RENDERBUFFER_HPP
#define RENDERBUFFER_HPP

#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/TextureFormat.hpp>

class RenderBuffer {
    public:
        RenderBuffer();
        RenderBuffer(vec2ui size, TextureFormat::Format format);
        RenderBuffer(RenderBuffer&& rhs);
        RenderBuffer& operator=(RenderBuffer&& rhs);
        ~RenderBuffer();
        friend void swap(RenderBuffer& a, RenderBuffer& b);

        void resize(vec2ui size);
        vec2ui getSize() const;
        void bind() const;
        GLuint getHandle() const;
    private:
        vec2ui size = vec2ui(0);
        TextureFormat::Format format = TextureFormat::RGB;
        GLuint handle = 0;
};

#endif // RENDERBUFFER_HPP
