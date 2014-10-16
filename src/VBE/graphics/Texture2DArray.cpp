#include <cstring>

#include <VBE/dependencies/stb_image/stb_image.hpp>
#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/Texture2DArray.hpp>
#include <VBE/system/Log.hpp>

// Texture arrays are not supported in GLES2
#ifndef VBE_GLES2

Texture2DArray::Texture2DArray() : size(0) {
	texType = GL_TEXTURE_2D_ARRAY;
}

Texture2DArray::~Texture2DArray() {
}


// static
Texture2DArray* Texture2DArray::createFromFiles(const std::vector<std::string>& filePaths) {
	Texture2DArray* t = new Texture2DArray();
	t->loadFromFiles(filePaths);
	return t;
}

// static
Texture2DArray* Texture2DArray::createFromRaw(
		const void* pixels,
		unsigned int sizeX,
		unsigned int sizeY,
		unsigned int slices,
		TextureFormat::Format format,
		TextureFormat::SourceType sourceType) {

	Texture2DArray* t = new Texture2DArray();
	t->loadFromRaw(pixels, sizeX, sizeY, slices, format, sourceType);
	return t;
}

// static
Texture2DArray* Texture2DArray::createEmpty(
		unsigned int sizeX,
		unsigned int sizeY,
		unsigned int slices,
		TextureFormat::Format format) {

	Texture2DArray* t = new Texture2DArray();
	t->loadEmpty(sizeX, sizeY, slices, format);
	return t;
}

void Texture2DArray::loadFromFiles(const std::vector<std::string>& filePaths) {
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
	loadFromRaw(pixels, sizeX, sizeY, slices, TextureFormat::channelsToFormat(channels));
	delete[] pixels;
}


void Texture2DArray::loadFromRaw(
		const void* pixels,
		unsigned int sizeX,
		unsigned int sizeY,
		unsigned int slices,
		TextureFormat::Format format,
		TextureFormat::SourceType sourceType) {
	this->format = format;
	size = vec3i(sizeX, sizeY, slices);
	bind();
	GL_ASSERT(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, format, sizeX, sizeY, slices, 0, TextureFormat::getBaseFormat(format), sourceType, (GLvoid*) pixels));
	setFilter(GL_LINEAR, GL_LINEAR);
	setWrap(GL_REPEAT);
}

void Texture2DArray::loadEmpty(
		unsigned int sizeX,
		unsigned int sizeY,
		unsigned int slices,
		TextureFormat::Format format) {
	loadFromRaw(nullptr, sizeX, sizeY, slices, format);
}

void Texture2DArray::resize(unsigned int sizeX, unsigned int sizeY, unsigned int slices) {
	loadEmpty(sizeX, sizeY, slices, format);
}

#ifndef VBE_GLES2
void Texture2DArray::setComparison(GLenum func, GLenum mode) {
	VBE_ASSERT(TextureFormat::isDepth(format), "Can't set comparison for a non-depth, non_stencil texture");
	bind();
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_FUNC, func));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_MODE, mode));
}
#endif

unsigned int Texture2DArray::getWidth() const {
	return size.x;
}

unsigned int Texture2DArray::getHeight() const {
	return size.y;
}

unsigned int Texture2DArray::getSlices() const {
	return size.z;
}

vec3ui Texture2DArray::getSize() const {
	return size;
}

void Texture2DArray::bind() const {
	VBE_ASSERT(handle !=0, "Trying to bind nullptr texture into slot " << slot);
	GL_ASSERT(glActiveTexture(GL_TEXTURE0 + slot));
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D_ARRAY, handle));
}

void Texture2DArray::setFilter(GLenum min, GLenum mag) {
	bind();
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, min));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, mag));
}

void Texture2DArray::setWrap(GLenum wrap) {
	bind();
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, wrap));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, wrap));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_R, wrap));
}

#endif // VBE_GLES2
