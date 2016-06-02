#include <cstring>

#include <VBE/config.hpp>
#include <VBE/dependencies/stb_image/stb_image.hpp>
#include <VBE/graphics/Image.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/TextureCubemap.hpp>
#include <VBE/system/Log.hpp>

//static
TextureCubemap TextureCubemap::load(
        std::vector<std::unique_ptr<std::istream>>& files,
        TextureFormat::Format format) {
    VBE_ASSERT(files.size() == 6, "You must provide 6 filepaths to load a cubemap");
    const int slices = 6;

    unsigned int size = 0;
    unsigned int channels = 0;

    unsigned char* pixels = nullptr;
    for (unsigned int i = 0; i < slices; i++) {
        Image img = Image::load(std::move(files[i]));
        VBE_ASSERT(img.getSize().x == img.getSize().y, "Images in a cubemap must be square");
        if (i == 0) {
            size = img.getSize().x;
            channels = img.getChannels();
            pixels = new unsigned char[channels*size*size*slices];
        }
        VBE_ASSERT(img.getSize().x == size, "Image " << i << " has a different size.");
        VBE_ASSERT(img.getChannels() == channels, "Image " << i << " has a different channel count.");

        const int sliceSize = channels*size*size*sizeof(unsigned char);
        memcpy(pixels + sliceSize*i, img.getData(), sliceSize);
    }

    TextureFormat::Format sourceFormat = TextureFormat::channelsToFormat(channels);
    if(format == TextureFormat::AUTO)
        format = sourceFormat;

    TextureCubemap res(size, format);
    res.setData(pixels, sourceFormat, TextureFormat::UNSIGNED_BYTE);
    delete[] pixels;
    return res;
}

TextureCubemap::TextureCubemap() : Texture(Texture::TypeCubemap) {
}


TextureCubemap::TextureCubemap(unsigned int size, TextureFormat::Format format) :
    Texture(Texture::TypeCubemap, format), size(size) {
    setData(nullptr, TextureFormat::getBaseFormat(format), TextureFormat::UNSIGNED_BYTE);
}

void TextureCubemap::setData(
        const void* pixels,
        TextureFormat::Format sourceFormat,
        TextureFormat::SourceType sourceType) {
    VBE_ASSERT(TextureFormat::isBaseFormat(sourceFormat), "Only base formats are accepted as source format for pixel data on texture loads. Specify the sizing of your input through the sourceType only");

    TextureCubemap::bind(this, 0);

    unsigned char* pface = (unsigned char*)pixels;
    for (int i = 0; i < 6; i++) {
        cubeFaces target;
        switch (i) {
            case 0:	target = CUBEMAP_POSITIVE_X; break;
            case 1:	target = CUBEMAP_NEGATIVE_X; break;
            case 2:	target = CUBEMAP_POSITIVE_Y; break;
            case 3:	target = CUBEMAP_NEGATIVE_Y; break;
            case 4: target = CUBEMAP_POSITIVE_Z; break;
            case 5:	target = CUBEMAP_NEGATIVE_Z; break;
        }
        if (pface)
            GL_ASSERT(glTexImage2D(target, 0, getFormat(), size, size, 0, sourceFormat, sourceType, (GLvoid*)(pface + i*size*size*4)));
        else
            GL_ASSERT(glTexImage2D(target, 0, getFormat(), size, size, 0, sourceFormat, sourceType, 0));
    }

    setFilter(GL_LINEAR, GL_LINEAR);
    setWrap(GL_CLAMP_TO_EDGE);
}

unsigned int TextureCubemap::getSize() const {
    return size;
}

TextureCubemap::TextureCubemap(TextureCubemap&& rhs) : TextureCubemap() {
    using std::swap;
    swap(*this, rhs);
}

TextureCubemap& TextureCubemap::operator=(TextureCubemap&& rhs) {
    using std::swap;
    swap(*this, rhs);
    return *this;
}

void swap(TextureCubemap& a, TextureCubemap& b) {
    using std::swap;
    swap(static_cast<Texture&>(a), static_cast<Texture&>(b));
    swap(a.size, b.size);
}
