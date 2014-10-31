#include <fstream>

#include <VBE/system/sdl2/StorageImpl.hpp>

// static
std::unique_ptr<std::istream> StorageImpl::openAsset(const std::string& filename) {
	// Open in binary mode so Windows doesn't change LF to CRLF,
	// which will corrupt binary files such as images.
	return std::unique_ptr<std::istream>(new std::ifstream("assets/"+filename, std::ios::binary));
}
