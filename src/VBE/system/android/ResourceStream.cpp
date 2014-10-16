#include "ResourceStream.hpp"

ResourceStream::ResourceStream(const std::string& filename) : asset(nullptr)
{
	ActivityStates* states = getActivity(NULL);
	asset = AAssetManager_open(states->activity->assetManager, filename.c_str(), AASSET_MODE_UNKNOWN);
}


ResourceStream::~ResourceStream()
{
	AAsset_close(asset);
}


long int ResourceStream::read(void *data, long int size)
{
	return AAsset_read(asset, data, size);
}


long int ResourceStream::seek(long int position)
{
	AAsset_seek(asset, position, SEEK_SET);
}


long int ResourceStream::tell()
{
	return getSize() - AAsset_getRemainingLength(asset);
}


long int ResourceStream::getSize()
{
	return AAsset_getLength(asset);
}