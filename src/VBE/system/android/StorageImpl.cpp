#include <streambuf>
#include <vector>
#include <cstring>

#include <VBE/system/android/StorageImpl.hpp>
#include <VBE/system/android/WindowImpl.hpp>

// Streambufs are terrible
// Here's some info to make them less terrible
// http://www.mr-edd.co.uk/blog/beginners_guide_streambuf

class AssetBuf : public std::streambuf
{
    public:
        explicit AssetBuf(const std::string& filename, std::size_t buff_sz = 256, std::size_t put_back = 8);

    private:
        int_type underflow() override;
        pos_type seekoff(off_type off, std::ios_base::seekdir way, std::ios_base::openmode which) override;
        pos_type seekpos(pos_type pos, std::ios_base::openmode which) override;

    private:
        AAsset* asset;
        const std::size_t put_back_;
        std::vector<char> buffer_;
};

AssetBuf::AssetBuf(const std::string& filename, size_t buff_sz, size_t put_back) :
    put_back_(std::max(put_back, size_t(1))),
    buffer_(std::max(buff_sz, put_back_) + put_back_)
{
    asset = AAssetManager_open(WindowImpl::app->activity->assetManager, filename.c_str(), AASSET_MODE_UNKNOWN);
    VBE_ASSERT(asset != nullptr, "Could not open asset: "+filename);
    char *end = &buffer_.front() + buffer_.size();
    setg(end, end, end);
}

std::streambuf::int_type AssetBuf::underflow()
{
    if (gptr() < egptr()) // buffer not exhausted
        return traits_type::to_int_type(*gptr());

    char *base = &buffer_.front();
    char *start = base;

    if (eback() == base) // true when this isn't the first fill
    {
        // Make arrangements for putback characters
        std::memmove(base, egptr() - put_back_, put_back_);
        start += put_back_;
    }

    // start is now the start of the buffer, proper.
    // Read from fptr_ in to the provided buffer
    size_t n = AAsset_read(asset, start, buffer_.size() - (start - base));
    if (n == 0)
        return traits_type::eof();

    // Set buffer pointers
    setg(base, start, start + n);

    return traits_type::to_int_type(*gptr());
}

AssetBuf::pos_type AssetBuf::seekoff(AssetBuf::off_type off, std::ios_base::seekdir way, std::ios_base::openmode which)
{
    if(way == std::ios_base::cur)
        AAsset_seek(asset, off, SEEK_CUR);
    else if(way == std::ios_base::end)
        AAsset_seek(asset, off, SEEK_END);
    else
        AAsset_seek(asset, off, SEEK_SET);

    setg(eback(), egptr(), egptr());

    return AAsset_getLength(asset) - AAsset_getRemainingLength(asset);
}

AssetBuf::pos_type AssetBuf::seekpos(AssetBuf::pos_type pos, std::ios_base::openmode which)
{
    return seekoff(off_type(pos), std::ios_base::beg, which);
}

// static
std::unique_ptr<std::istream> StorageImpl::openAsset(const std::string& filename) {
    return std::unique_ptr<std::istream>(new std::istream(new AssetBuf(filename)));
}
