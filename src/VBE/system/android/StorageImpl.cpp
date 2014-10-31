#include <fstream>

#include <VBE/system/android/StorageImpl.hpp>
#include <VBE/system/android/ResourceStream.hpp>

// static
std::istream* StorageImpl::openAsset(const std::string& filename) {
	return new ResourceStream(filename);
}
