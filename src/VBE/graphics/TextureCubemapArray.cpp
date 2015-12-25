#include <cstring>

#include <VBE/dependencies/stb_image/stb_image.hpp>
#include <VBE/config.hpp>
#include <VBE/graphics/Image.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/TextureCubemapArray.hpp>
#include <VBE/system/Log.hpp>

// Texture arrays are not supported in GLES2
#ifndef VBE_GLES2

//static
TextureCubemapArray TextureCubemapArray::load(
		std::vector<std::unique_ptr<std::istream>>& files,
		TextureFormat::Format format) {

	unsigned int slices = files.size()/6;
	VBE_ASSERT(slices%6 == 0, "You must provide 6 filepaths for each cubemap");

	unsigned int size;
	unsigned int channels = 0;

	unsigned char* pixels = nullptr;
	for (unsigned int i = 0; i < files.size(); i++) {
		Image img = Image::load(std::move(files[i]));
		VBE_ASSERT(img.getSize().x == img.getSize().y, "Images in a cubemap must be square");
		if (i == 0) {
			size = img.getSize().x;
			channels = img.getChannels();
			pixels = new unsigned char[channels*size*size*files.size()];
		}
		VBE_ASSERT(size == img.getSize().x, "Image " << i << " has a different size.");
		VBE_ASSERT(img.getChannels() == channels, "Image " << i << " has a different channel count.");

		const int sliceSize = channels*size*size*sizeof(unsigned char);
		memcpy(pixels + sliceSize*i, img.getData(), sliceSize);
	}

	TextureFormat::Format sourceFormat = TextureFormat::channelsToFormat(channels);
	if(format == TextureFormat::AUTO)
		format = sourceFormat;

	TextureCubemapArray res(size, slices, format);
	res.setData(pixels, sourceFormat, TextureFormat::UNSIGNED_BYTE);
	delete[] pixels;
	return res;
}

TextureCubemapArray::TextureCubemapArray() : Texture(Texture::TypeCubemapArray) {
}

TextureCubemapArray::TextureCubemapArray(unsigned size, unsigned int slices, TextureFormat::Format format) :
	Texture(Texture::TypeCubemapArray, format), size(size), slices(slices) {
	setData(nullptr, TextureFormat::getBaseFormat(format), TextureFormat::UNSIGNED_BYTE);
}

void TextureCubemapArray::setData(
		const void *pixels,
		TextureFormat::Format sourceFormat,
		TextureFormat::SourceType sourceType) {
	VBE_ASSERT(TextureFormat::isBaseFormat(sourceFormat), "Only base formats are accepted as source format for pixel data on texture loads. Specify the sizing of your input through the sourceType only");

	TextureCubemapArray::bind(this, 0);
	GL_ASSERT(glTexImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, 0, getFormat(), size, size, 6*slices, 0, sourceFormat, sourceType, (GLvoid*) pixels));
}

unsigned int TextureCubemapArray::getSize() const {
	return size;
}

unsigned int TextureCubemapArray::getSlices() const {
	return slices;
}

TextureCubemapArray::TextureCubemapArray(TextureCubemapArray&& rhs) : TextureCubemapArray() {
	using std::swap;
	swap(*this, rhs);
}

TextureCubemapArray& TextureCubemapArray::operator=(TextureCubemapArray&& rhs) {
	using std::swap;
	swap(*this, rhs);
	return *this;
}

void swap(TextureCubemapArray& a, TextureCubemapArray& b) {
	using std::swap;
	swap(static_cast<Texture&>(a), static_cast<Texture&>(b));
	swap(a.size, b.size);
}

#endif // VBE_GLES2
