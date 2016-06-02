#include <VBE/graphics/Image.hpp>
#include <VBE/dependencies/stb_image/stb_image.hpp>

Image::Image() {
}

Image::Image(void* data, vec2ui size, unsigned int channels) :
    data(data), size(size), channels(channels) {
    VBE_ASSERT(data != nullptr, "Image data cannot be nullptr");
}

Image::Image(Image&& rhs) : Image() {
    using std::swap;
    swap(*this, rhs);
}

Image& Image::operator=(Image&& rhs) {
    using std::swap;
    swap(*this, rhs);
    return *this;
}

Image::~Image() {
    if(data != nullptr)
        free(data);
}

void swap(Image& a, Image& b) {
    using std::swap;

    swap(a.data, b.data);
    swap(a.size, b.size);
    swap(a.channels, b.channels);
}

static int stb_eof(void * user) {
    std::istream* stream = reinterpret_cast<std::istream*>(user);
    return stream->eof() || stream->bad() || stream->fail();
}

static int stb_read(void * user, char * data, int size) {
    if (size < 0)
        size = 0;

    std::istream* stream = reinterpret_cast<std::istream*>(user);
    stream->read(data, static_cast<size_t>(size));
    return stream->gcount();
}

static void stb_skip(void * user, unsigned n) {
    std::istream* stream = reinterpret_cast<std::istream*>(user);
    stream->ignore(static_cast<std::streamsize>(n));
}

static const STBI::stbi_io_callbacks stb_callbacks = {
    stb_read,
    stb_skip,
    stb_eof
};

// static
Image Image::load(std::unique_ptr<std::istream> in) {
    int sizeX, sizeY, channels;
    unsigned char* ptr = STBI::stbi_load_from_callbacks(&stb_callbacks, in.get(), &sizeX, &sizeY, &channels, 0);
    VBE_ASSERT(ptr && sizeX && sizeY, "Failed to load image. Reason : " << STBI::stbi_failure_reason());

    return Image(ptr, vec2ui(sizeX, sizeY), channels);
}
