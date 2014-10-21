#include <cstring>

#include <VBE/config.hpp>
#include <VBE/dependencies/stb_image/stb_image.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/TextureCubemap.hpp>
#include <VBE/system/Log.hpp>

TextureCubemap::TextureCubemap() : Texture(Texture::TypeCubemap), size(0) {
}

void TextureCubemap::loadFromFiles(
		const std::vector<std::string>& filePaths,
		TextureFormat::Format internalFormat) {
	VBE_ASSERT(filePaths.size() == 6, "You must provide 6 filepaths to load a cubemap");
	const int slices = 6;

	unsigned int size = 0;
	unsigned int channels = 0;

	unsigned char* pixels = nullptr;
	for (unsigned int i = 0; i < slices; i++) {
		VBE_DLOG("* Loading new TextureCubemap slice from path " << filePaths[i]);
		int sliceSizeX, sliceSizeY, sliceChannels;
		unsigned char* ptr = STBI::stbi_load(filePaths[i].c_str(), &sliceSizeX, &sliceSizeY, &sliceChannels, 0);
		VBE_ASSERT(ptr && sliceSizeX && sliceSizeY, "Failed to load image \"" << filePaths[i] << "\". Reason : " << STBI::stbi_failure_reason());
		VBE_ASSERT(sliceSizeX == sliceSizeY, "Failed to load image \"" << filePaths[i] << "\". Images in a cubemap must be square");
		if (i == 0) {
			size = sliceSizeX;
			channels = sliceChannels;
			pixels = new unsigned char[channels*size*size*slices];
		}
		VBE_ASSERT(sliceSizeX == int(size), "Image " << i << ": " << filePaths[i] << " has a different size.");
		VBE_ASSERT(sliceChannels == int(channels), "Image " << i << ": " << filePaths[i] << " has a different channel count.");

		const int sliceSize = channels*size*size*sizeof(unsigned char);
		memcpy(pixels + sliceSize*i, ptr, sliceSize);
		STBI::stbi_image_free(ptr);
	}

	TextureFormat::Format sourceFormat = TextureFormat::channelsToFormat(channels);
	if(internalFormat == TextureFormat::AUTO)
		internalFormat = sourceFormat;

	loadFromRaw(pixels, size, sourceFormat, TextureFormat::UNSIGNED_BYTE, internalFormat);

	delete[] pixels;
}

void TextureCubemap::loadFromRaw(
		const void* pixels,
		unsigned int size,
		TextureFormat::Format sourceFormat,
		TextureFormat::SourceType sourceType,
		TextureFormat::Format internalFormat) {

	if (internalFormat == TextureFormat::AUTO)
		internalFormat = sourceFormat;

	this->format = internalFormat;
	this->size = size;
	TextureCubemap::bind(this);

	unsigned char* pface = (unsigned char*)pixels;
	for (int i = 0; i < 6; i++) {
		cubeFaces target;
		switch (i) {
			case 0:	target = CUBEMAP_POSITIVE_X; break;
			case 1:	target = CUBEMAP_NEGATIVE_X; break;
			case 2:	target = CUBEMAP_POSITIVE_Y; break;
			case 3:	target = CUBEMAP_NEGATIVE_Y; break;
			case 4: target = CUBEMAP_POSITIVE_Z; break;
			case 5:	target = CUBEMAP_NEGATIVE_Z; break;
		}
		if (pface)
			GL_ASSERT(glTexImage2D(target, 0, internalFormat, size, size, 0, sourceFormat, sourceType, (GLvoid*)(pface + i*size*size*4)));
		else
			GL_ASSERT(glTexImage2D(target, 0, internalFormat, size, size, 0, sourceFormat, sourceType, 0));
	}

	setFilter(GL_LINEAR, GL_LINEAR);
	setWrap(GL_CLAMP_TO_EDGE);
}


void TextureCubemap::loadEmpty(
		unsigned int size,
		TextureFormat::Format internalFormat) {
	loadFromRaw(nullptr, size, TextureFormat::getBaseFormat(internalFormat), TextureFormat::UNSIGNED_BYTE, internalFormat);
}

unsigned int TextureCubemap::getSize() const {
	return size;
}
