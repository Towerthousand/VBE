#include <VBE/system/Storage.hpp>
#include <VBE/system/StorageImpl.hpp>

// static
std::unique_ptr<std::istream> Storage::openAsset(const std::string& filename) {
	return StorageImpl::openAsset(filename);
}

