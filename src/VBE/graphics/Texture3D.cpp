#include <VBE/config.hpp>
#include <VBE/dependencies/stb_image/stb_image.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/Texture3D.hpp>
#include <VBE/system/Log.hpp>

// 3D textures are not supported in GLES2
#ifndef VBE_GLES2

Texture3D::Texture3D() : Texture(Texture::Type3D) {
}

Texture3D::Texture3D(vec3ui size, TextureFormat::Format format) :
    Texture(Texture::Type3D, format), size(size) {
    setData(nullptr, TextureFormat::getBaseFormat(format), TextureFormat::UNSIGNED_BYTE);
}

void Texture3D::setData(
        const void *pixels,
        TextureFormat::Format sourceFormat,
        TextureFormat::SourceType sourceType) {
    VBE_ASSERT(TextureFormat::isBaseFormat(sourceFormat), "Only base formats are accepted as source format for pixel data on texture loads. Specify the sizing of your input through the sourceType only");
    Texture3D::bind(this, 0);
    GL_ASSERT(glTexImage3D(GL_TEXTURE_3D, 0, getFormat(), size.x, size.y, size.z, 0, sourceFormat, sourceType, (GLvoid*) pixels));
}

vec3ui Texture3D::getSize() const {
    return size;
}

Texture3D::Texture3D(Texture3D&& rhs) : Texture3D() {
    using std::swap;
    swap(*this, rhs);
}

Texture3D& Texture3D::operator=(Texture3D&& rhs) {
    using std::swap;
    swap(*this, rhs);
    return *this;
}

void swap(Texture3D& a, Texture3D& b) {
    using std::swap;
    swap(static_cast<Texture&>(a), static_cast<Texture&>(b));
    swap(a.size, b.size);
}

#endif // VBE_GLES2
