#ifndef RESOURCESTREAM_HPP
#define RESOURCESTREAM_HPP

#include <android/asset_manager.h>
#include <string>

#include "InputStream.hpp"

class ResourceStream : public InputStream {
	public :
		ResourceStream(const std::string& filename);
		virtual ~ResourceStream() {}
		virtual long int read(void* data, long int size);
		virtual long int seek(long int position);
		virtual long int tell();
		virtual long int getSize();

	private:
		AAsset* asset;
};

#endif // RESOURCESTREAM_HPP
