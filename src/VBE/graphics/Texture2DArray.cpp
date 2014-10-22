#include <cstring>

#include <VBE/dependencies/stb_image/stb_image.hpp>
#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/Texture2DArray.hpp>
#include <VBE/system/Log.hpp>

// Texture arrays are not supported in GLES2
#ifndef VBE_GLES2

Texture2DArray::Texture2DArray() : Texture(Texture::Type2DArray), size(0) {
}

void Texture2DArray::loadFromFiles(
		const std::vector<std::string>& filePaths,
		TextureFormat::Format internalFormat) {

	unsigned int slices = filePaths.size();
	VBE_ASSERT(slices > 0, "You must provide at least one slice (one filepath)");

	unsigned int sizeX = 0;
	unsigned int sizeY = 0;
	unsigned int channels = 0;

	unsigned char* pixels = nullptr;
	for (unsigned int i = 0; i < slices; i++) {
		VBE_DLOG("* Loading new Texture2DArray slice from path " << filePaths[i]);
		int sliceSizeX, sliceSizeY, sliceChannels;
		unsigned char* ptr = STBI::stbi_load(filePaths[i].c_str(), &sliceSizeX, &sliceSizeY, &sliceChannels, 0);
		VBE_ASSERT(ptr && sliceSizeX && sliceSizeY, "Failed to load image \"" << filePaths[i] << "\". Reason : " << STBI::stbi_failure_reason());
		if (i == 0) {
			sizeX = sliceSizeX;
			sizeY = sliceSizeY;
			channels = sliceChannels;
			pixels = new unsigned char[4*sizeX*sizeY*slices];
		}
		VBE_ASSERT(sliceSizeX == int(sizeX) && sliceSizeY == int(sizeY), "Image " << i << ": " << filePaths[i] << " has a different size.");
		VBE_ASSERT(sliceChannels == int(channels), "Image " << i << ": " << filePaths[i] << " has a different channel count.");

		const int sliceSize = channels*sizeX*sizeY*sizeof(unsigned char);
		memcpy(pixels + sliceSize*i, ptr, sliceSize);
		STBI::stbi_image_free(ptr);
	}

	TextureFormat::Format sourceFormat = TextureFormat::channelsToFormat(channels);
	if(internalFormat == TextureFormat::AUTO)
		internalFormat = sourceFormat;

	loadFromRaw(pixels, vec3ui(sizeX, sizeY, slices), sourceFormat, TextureFormat::UNSIGNED_BYTE, internalFormat);
	delete[] pixels;
}

void Texture2DArray::loadEmpty(
		vec3ui size,
		TextureFormat::Format internalFormat) {
	loadFromRaw(nullptr, size, TextureFormat::getBaseFormat(internalFormat), TextureFormat::UNSIGNED_BYTE, internalFormat);
}

void Texture2DArray::loadFromRaw(
		const void *pixels,
		vec3ui size,
		TextureFormat::Format sourceFormat,
		TextureFormat::SourceType sourceType,
		TextureFormat::Format internalFormat) {

	if (internalFormat == TextureFormat::AUTO)
		internalFormat = sourceFormat;

	this->format = internalFormat;
	this->size = size;
	Texture2DArray::bind(this, 0);
	GL_ASSERT(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, internalFormat, size.x, size.y, size.z, 0, sourceFormat, sourceType, (GLvoid*) pixels));
	setFilter(GL_LINEAR, GL_LINEAR);
	setWrap(GL_REPEAT);
}

vec3ui Texture2DArray::getSize() const {
	return size;
}

#endif // VBE_GLES2
