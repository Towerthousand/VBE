#include "TextureCubemap.hpp"

TextureCubemap::TextureCubemap() : size(0) {
	texType = GL_TEXTURE_CUBE_MAP;
}

TextureCubemap::~TextureCubemap() {
}

// static
TextureCubemap* TextureCubemap::createFromFiles(const std::vector<std::string>& filePaths) {
	TextureCubemap* t = new TextureCubemap();
	t->loadFromFiles(filePaths);
	return t;
}

// static
TextureCubemap* TextureCubemap::createFromRaw(
		const void* pixels,
		unsigned int size,
		TextureFormat::Format format,
		TextureFormat::SourceType sourceType) {

	TextureCubemap* t = new TextureCubemap();
	t->loadFromRaw(pixels, size, format, sourceType);
	return t;
}

// static
TextureCubemap* TextureCubemap::createEmpty(
		unsigned int size,
		TextureFormat::Format format) {

	TextureCubemap* t = new TextureCubemap();
	t->loadEmpty(size, format);
	return t;
}


void TextureCubemap::loadFromFiles(const std::vector<std::string>& filePaths) {
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
			pixels = new unsigned char[4*size*size*slices];
		}
		VBE_ASSERT(sliceSizeX == int(size), "Image " << i << ": " << filePaths[i] << " has a different size.");
		VBE_ASSERT(sliceChannels == int(channels), "Image " << i << ": " << filePaths[i] << " has a different channel count.");

		const int sliceSize = channels*size*size*sizeof(unsigned char);
		memcpy(pixels + sliceSize*i, ptr, sliceSize);
		STBI::stbi_image_free(ptr);
	}
	loadFromRaw(pixels, size, TextureFormat::channelsToFormat(channels));
	delete[] pixels;
}


void TextureCubemap::loadFromRaw(
		const void* pixels,
		unsigned int size,
		TextureFormat::Format format,
		TextureFormat::SourceType sourceType) {
	this->format = format;
	this->size = size;
	bind();

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
			GL_ASSERT(glTexImage2D(target, 0, format, size, size, 0, TextureFormat::getBaseFormat(format), sourceType, (GLvoid*)(pface + i*size*size*4)));
		else
			GL_ASSERT(glTexImage2D(target, 0, format, size, size, 0, TextureFormat::getBaseFormat(format), sourceType, 0));
	}

	setFilter(GL_LINEAR, GL_LINEAR);
	setWrap(GL_CLAMP_TO_EDGE);
}

void TextureCubemap::loadEmpty(
		unsigned int size,
		TextureFormat::Format format) {
	loadFromRaw(nullptr, size, format);
}

void TextureCubemap::resize(unsigned int newSize) {
	loadEmpty(newSize, format);
}

#ifndef VBE_GLES2
void TextureCubemap::setComparison(GLenum func, GLenum mode) {
	VBE_ASSERT(TextureFormat::isDepth(format), "Can't set comparison for a non-depth, non_stencil texture");
	bind();
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_FUNC, func));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, mode));
}
#endif

int TextureCubemap::getWidth() const {
	return size;
}

int TextureCubemap::getHeight() const {
	return size;
}

void TextureCubemap::bind() const {
	VBE_ASSERT(handle !=0, "Trying to bind nullptr texture into slot " << slot);
	GL_ASSERT(glActiveTexture(GL_TEXTURE0 + slot));
	GL_ASSERT(glBindTexture(GL_TEXTURE_CUBE_MAP, handle));
}

void TextureCubemap::setFilter(GLenum min, GLenum mag) {
	bind();
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, min));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, mag));
}

void TextureCubemap::setWrap(GLenum wrap) {
	bind();
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, wrap));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, wrap));
}
