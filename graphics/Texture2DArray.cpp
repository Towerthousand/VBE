#include "Texture2DArray.hpp"
#include "SFML/Graphics.hpp"


Texture2DArray::Texture2DArray() : size(0) {
}

Texture2DArray::~Texture2DArray() {
}

Texture2DArray* Texture2DArray::createEmpty(unsigned int sizeX, unsigned int sizeY, unsigned int slices, Texture::InternalFormat format, int slot) {
	Texture2DArray* t = new Texture2DArray();
	t->loadEmpty(sizeX, sizeY, slices, format, slot);
	return t;
}

Texture2DArray* Texture2DArray::createFromFiles(const std::vector<std::string>& filePaths, Texture::SourceFormat sourceFormat, Texture::SourceType sourceType, Texture::InternalFormat internalFormat, bool mipmap, int slot) {
	Texture2DArray* t = new Texture2DArray();
	t->loadFromFiles(filePaths, sourceFormat, sourceType, internalFormat, mipmap, slot);
	return t;
}

Texture2DArray* Texture2DArray::createFromRaw(const void* pixels, unsigned int sizeX, unsigned int sizeY, unsigned int slices, Texture::SourceFormat sourceFormat, Texture::SourceType sourceType, Texture::InternalFormat internalFormat, bool mipmap, int slot) {
	Texture2DArray* t = new Texture2DArray();
	t->loadFromRaw(pixels, sizeX, sizeY, slices, sourceFormat, sourceType, internalFormat, mipmap, slot);
	return t;
}

void Texture2DArray::loadEmpty(unsigned int sizeX, unsigned int sizeY, unsigned int slices, Texture::InternalFormat format, int slot) {
	SourceFormat sFormat = RGBA;
	SourceType sType = UNSIGNED_BYTE;
	switch (format) {
		case R8_SNORM: case R8I: case R8UI: case R16: case R16F: case R16I: case R16UI: case R16_SNORM: case R32F: case R32I: case R32UI: case R8: sFormat = RED; break;
		case RG8_SNORM: case RG8I: case RG8UI: case RG16: case RG16F: case RG16I: case RG16UI: case RG16_SNORM: case RG32F: case RG32I: case RG32UI: case RG8: sFormat = RG; break;
		case RGB4: case RGB5: case RGB8_SNORM: case RGB8I: case RGB8UI: case RGB10: case RGB12: case RGB16_SNORM: case RGB16F: case RGB16I: case RGB16UI: case RGB32F: case RGB32I: case RGB32UI: case RGB8: sFormat = RGB; break;
		case RGBA2: case RGBA4: case RGBA8_SNORM: case RGBA12: case RGBA16: case RGBA16F: case RGBA32F: case RGBA8I: case RGBA8UI: case RGBA16I: case RGBA16UI: case RGBA32I: case RGBA32UI: case RGBA8: sFormat = RGBA; break;
		case DEPTH_COMPONENT16: case DEPTH_COMPONENT24: case DEPTH_COMPONENT32F: case DEPTH24_STENCIL8: case DEPTH32F_STENCIL8: case DEPTH_COMPONENT32: sFormat = DEPTH_COMPONENT; sType = UNSIGNED_INT; break;
	}
	loadFromRaw(nullptr, sizeX, sizeY, slices, sFormat, sType, format, false, slot);
}

void Texture2DArray::loadFromFiles(const std::vector<std::string>& filePaths, Texture::SourceFormat sourceFormat, Texture::SourceType sourceType, Texture::InternalFormat internalFormat, bool mipmap, int slot) {
	//load images
	unsigned int sizeX  = 0;
	unsigned int sizeY  = 0;
	unsigned int slices = filePaths.size();
	unsigned char* pixels = nullptr;
	for (unsigned int i = 0; i < slices; i++) {
		VBE_DLOG("* Loading new Texture2DArray slice from path " << filePaths[i]);
		sf::Image image;
		if (!image.loadFromFile(filePaths[i])) {
			VBE_LOG("#ERROR " << filePaths[i] << " didn't load" );
		}
		if (i == 0) {
			sizeX = image.getSize().x;
			sizeY = image.getSize().y;
			pixels = new unsigned char[4*sizeX*sizeY*slices];
		}
		VBE_ASSERT(image.getSize().x == sizeX && image.getSize().y == sizeY, "Image " << i << ": " << filePaths[i] << " has a different size.");
		memcpy((void*)&pixels[4*i*sizeX*sizeY*sizeof(unsigned char)], (void*)image.getPixelsPtr(), 4*sizeX*sizeY*sizeof(unsigned char));
	}

	loadFromRaw(pixels, sizeX, sizeY, slices, sourceFormat, sourceType, internalFormat, mipmap, slot);
	delete[] pixels;
}

void Texture2DArray::loadFromRaw(const void* pixels, unsigned int sizeX, unsigned int sizeY, unsigned int slices, Texture::SourceFormat sourceFormat, Texture::SourceType sourceType, Texture::InternalFormat internalFormat, bool mipmap, int slot) {
	if(slot != -1)
		setSlot(slot);
	format = internalFormat;
	size = vec3i(sizeX, sizeY, slices);
	bind();
	GL_ASSERT(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, internalFormat, sizeX, sizeY, slices, 0, sourceFormat, sourceType, (GLvoid*) pixels));
	if(mipmap) {
		GL_ASSERT(glGenerateMipmap(GL_TEXTURE_2D_ARRAY));
		setFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	}
	else
		setFilter(GL_LINEAR, GL_LINEAR);
	setWrap(GL_REPEAT);
}

void Texture2DArray::resize(unsigned int sizeX, unsigned int sizeY, unsigned int slices) {
	loadEmpty(sizeX, sizeY, slices, format, slot);
}

void Texture2DArray::setComparison(GLenum func, GLenum mode) {
	VBE_ASSERT(format == DEPTH_COMPONENT16 || format == DEPTH_COMPONENT24 || format == DEPTH_COMPONENT32 || format == DEPTH_COMPONENT32F || format == DEPTH24_STENCIL8 || format == DEPTH32F_STENCIL8, "Can't set comparison for a non-depth, non_stencil texture");
	bind();
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_FUNC, func));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_MODE, mode));
}

int Texture2DArray::getWidth() const {
	return size.x;
}

int Texture2DArray::getHeight() const {
	return size.y;
}

int Texture2DArray::getSlices() const {
	return size.z;
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
