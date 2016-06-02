#include <cstring>

#include <VBE/dependencies/stb_image/stb_image.hpp>
#include <VBE/config.hpp>
#include <VBE/graphics/Image.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/Texture2DArray.hpp>
#include <VBE/system/Log.hpp>

// Texture arrays are not supported in GLES2
#ifndef VBE_GLES2

//static
Texture2DArray Texture2DArray::load(
        std::vector<std::unique_ptr<std::istream>>& files,
        TextureFormat::Format format) {
    unsigned int slices = files.size();
    VBE_ASSERT(slices > 0, "You must provide at least one slice (one filepath)");

    vec2ui size;
    unsigned int channels = 0;

    unsigned char* pixels = nullptr;
    for (unsigned int i = 0; i < slices; i++) {
        Image img = Image::load(std::move(files[i]));
        if (i == 0) {
            size = img.getSize();
            channels = img.getChannels();
            pixels = new unsigned char[4*size.x*size.y*slices];
        }
        VBE_ASSERT(size == img.getSize(), "Image " << i << " has a different size.");
        VBE_ASSERT(img.getChannels() == channels, "Image " << i << " has a different channel count.");

        const int sliceSize = channels*size.x*size.y*sizeof(unsigned char);
        memcpy(pixels + sliceSize*i, img.getData(), sliceSize);
    }

    TextureFormat::Format sourceFormat = TextureFormat::channelsToFormat(channels);
    if(format == TextureFormat::AUTO)
        format = sourceFormat;

    Texture2DArray res(vec3ui(size.x, size.y, slices), format);
    res.setData(pixels, sourceFormat, TextureFormat::UNSIGNED_BYTE);
    delete[] pixels;
    return res;
}

Texture2DArray::Texture2DArray() : Texture(Texture::Type2DArray) {
}

Texture2DArray::Texture2DArray(vec3ui size, TextureFormat::Format format) :
    Texture(Texture::Type2DArray, format), size(size) {
    setData(nullptr, TextureFormat::getBaseFormat(format), TextureFormat::UNSIGNED_BYTE);
}

void Texture2DArray::setData(
        const void *pixels,
        TextureFormat::Format sourceFormat,
        TextureFormat::SourceType sourceType) {
    VBE_ASSERT(TextureFormat::isBaseFormat(sourceFormat), "Only base formats are accepted as source format for pixel data on texture loads. Specify the sizing of your input through the sourceType only");

    Texture2DArray::bind(this, 0);
    GL_ASSERT(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, getFormat(), size.x, size.y, size.z, 0, sourceFormat, sourceType, (GLvoid*) pixels));
}

vec3ui Texture2DArray::getSize() const {
    return size;
}

Texture2DArray::Texture2DArray(Texture2DArray&& rhs) : Texture2DArray() {
    using std::swap;
    swap(*this, rhs);
}

Texture2DArray& Texture2DArray::operator=(Texture2DArray&& rhs) {
    using std::swap;
    swap(*this, rhs);
    return *this;
}

void swap(Texture2DArray& a, Texture2DArray& b) {
    using std::swap;
    swap(static_cast<Texture&>(a), static_cast<Texture&>(b));
    swap(a.size, b.size);
}

#endif // VBE_GLES2
