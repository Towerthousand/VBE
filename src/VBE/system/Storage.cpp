#include <VBE/system/Storage.hpp>
#include <VBE/system/StorageImpl.hpp>

// static
std::unique_ptr<std::istream> Storage::openAsset(const std::string& filename) {
    return StorageImpl::openAsset(filename);
}

// static
std::string Storage::readToString(std::unique_ptr<std::istream> file){
    // get length of file
    file->seekg(0, std::ios::end);
    int length = (int) file->tellg();
    file->seekg(0, std::ios::beg);

    // allocate memory
    std::string s(length, 0);

    // read data as a block
    file->read(&s[0], length);

    return s;
}

// static
void Storage::setAssetPath(std::string path) {
    StorageImpl::setAssetPath(path);
}
