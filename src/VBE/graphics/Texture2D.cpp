#include <VBE/config.hpp>
#include <VBE/dependencies/stb_image/stb_image.hpp>
#include <VBE/graphics/Image.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/Texture2D.hpp>
#include <VBE/system/Log.hpp>


//static
Texture2D Texture2D::load(
        std::unique_ptr<std::istream> in,
        TextureFormat::Format format) {

    VBE_DLOG("* Loading new Texture2D from path ");

    Image img = Image::load(std::move(in));

    TextureFormat::Format sourceFormat = img.getGlFormat();
    if(format == TextureFormat::AUTO)
        format = sourceFormat;

    Texture2D res(img.getSize(), format);
    res.setData(img.getData(), sourceFormat, TextureFormat::UNSIGNED_BYTE);
    return res;
}

Texture2D::Texture2D() : Texture(Texture::Type2D) {
}

Texture2D::Texture2D(vec2ui size, TextureFormat::Format format) :
    Texture(Texture::Type2D, format), size(size) {
    setData(nullptr, TextureFormat::getBaseFormat(format), TextureFormat::UNSIGNED_BYTE);
}

void Texture2D::setData(
        const void *pixels,
        TextureFormat::Format sourceFormat,
        TextureFormat::SourceType sourceType) {
    VBE_ASSERT(TextureFormat::isBaseFormat(sourceFormat), "Only base formats are accepted as source format for pixel data on texture loads. Specify the sizing of your input through the sourceType only");

    Texture2D::bind(this, 0);
    GL_ASSERT(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
    GL_ASSERT(glPixelStorei(GL_PACK_ALIGNMENT, 1));
    GL_ASSERT(glTexImage2D(GL_TEXTURE_2D, 0, getFormat(), size.x, size.y, 0, sourceFormat, sourceType, (GLvoid*) pixels));
}

vec2ui Texture2D::getSize() const {
    return size;
}

Texture2D::Texture2D(Texture2D&& rhs) : Texture2D() {
    using std::swap;
    swap(*this, rhs);
}

Texture2D& Texture2D::operator=(Texture2D&& rhs) {
    using std::swap;
    swap(*this, rhs);
    return *this;
}

void swap(Texture2D& a, Texture2D& b) {
    using std::swap;
    swap(static_cast<Texture&>(a), static_cast<Texture&>(b));
    swap(a.size, b.size);
}
