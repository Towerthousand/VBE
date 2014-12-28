#include <cstring>

#include <VBE/dependencies/stb_image/stb_image.hpp>
#include <VBE/config.hpp>
#include <VBE/graphics/Image.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/Texture2DArray.hpp>
#include <VBE/system/Log.hpp>

// Texture arrays are not supported in GLES2
#ifndef VBE_GLES2

Texture2DArray::Texture2DArray() : Texture(Texture::Type2DArray), size(0) {
}

void Texture2DArray::load(
		std::vector<std::unique_ptr<std::istream>>& files,
		TextureFormat::Format internalFormat) {
	unsigned int slices = files.size();
	VBE_ASSERT(slices > 0, "You must provide at least one slice (one filepath)");

	vec2ui size;
	unsigned int channels = 0;

	unsigned char* pixels = nullptr;
	for (unsigned int i = 0; i < slices; i++) {
		Image img = Image::load(std::move(files[i]));
		if (i == 0) {
			size = img.getSize();
			channels = img.getChannels();
			pixels = new unsigned char[4*size.x*size.y*slices];
		}
		VBE_ASSERT(size == img.getSize(), "Image " << i << " has a different size.");
		VBE_ASSERT(img.getChannels() == channels, "Image " << i << " has a different channel count.");

		const int sliceSize = channels*size.x*size.y*sizeof(unsigned char);
		memcpy(pixels + sliceSize*i, img.getData(), sliceSize);
	}

	TextureFormat::Format sourceFormat = TextureFormat::channelsToFormat(channels);
	if(internalFormat == TextureFormat::AUTO)
		internalFormat = sourceFormat;

	loadFromRaw(pixels, vec3ui(size.x, size.y, slices), sourceFormat, TextureFormat::UNSIGNED_BYTE, internalFormat);
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

Texture2DArray::Texture2DArray(Texture2DArray&& rhs) : Texture2DArray() {
	using std::swap;
	swap(*this, rhs);
}

Texture2DArray& Texture2DArray::operator=(Texture2DArray&& rhs) {
	using std::swap;
	swap(*this, rhs);
	return *this;
}

void swap(Texture2DArray& a, Texture2DArray& b) {
	using std::swap;
	swap(static_cast<Texture&>(a), static_cast<Texture&>(b));
	swap(a.size, b.size);
}

#endif // VBE_GLES2
