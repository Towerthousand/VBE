#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <memory>
#include <iostream>
#include <VBE/math.hpp>
#include <VBE/graphics/TextureFormat.hpp>
#include <VBE/utils/NonCopyable.hpp>

class Image : public NonCopyable {
    public:
        Image();
        Image(void* data, vec2ui size, unsigned int channels);
        Image(Image&& rhs);
        Image& operator=(Image&& rhs);
        ~Image();
        friend void swap(Image& a, Image& b);

        void* getData() const { return data; }
        vec2ui getSize() const { return size; }
        unsigned int getChannels() const { return channels; }
        TextureFormat::Format getGlFormat() const { return TextureFormat::channelsToFormat(channels); }

        static Image load(std::unique_ptr<std::istream>in);
    private:
        void* data = nullptr;
        vec2ui size = vec2ui(0);
        unsigned int channels = 0;
};

#endif // IMAGE_HPP
