#ifndef RESOURCESTREAM_HPP
#define RESOURCESTREAM_HPP

#include <android/asset_manager.h>
#include <string>
#include <iostream>

class ResourceStream : public std::istream {
	public :
		ResourceStream(const std::string& filename);
		virtual ~ResourceStream() {}

	private:
		AAsset* asset;
};

#endif // RESOURCESTREAM_HPP
