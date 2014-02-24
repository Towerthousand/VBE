#include "Texture3D.hpp"

Texture3D::Texture3D() : size(0) {
}

Texture3D::~Texture3D() {
}

Texture3D* Texture3D::createEmpty(unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ, Texture::InternalFormat format, int slot) {
	Texture3D* t = new Texture3D();
	t->loadEmpty(sizeX, sizeY, sizeZ, format, slot);
	return t;
}

Texture3D* Texture3D::createFromRaw(const void* pixels, unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ, Texture::SourceFormat sourceFormat, Texture::SourceType sourceType, Texture::InternalFormat internalFormat, bool mipmap, int slot) {
	Texture3D* t = new Texture3D();
	t->loadFromRaw(pixels, sizeX, sizeY, sizeZ, sourceFormat, sourceType, internalFormat, mipmap, slot);
	return t;
}

void Texture3D::loadEmpty(unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ, Texture::InternalFormat format, int slot) {
	SourceFormat sFormat = RGBA;
	SourceType sType = UNSIGNED_BYTE;
	switch (format) {
		case R8_SNORM: case R8I: case R8UI: case R16: case R16F: case R16I: case R16UI: case R16_SNORM: case R32F: case R32I: case R32UI: case R8: sFormat = RED; break;
		case RG8_SNORM: case RG8I: case RG8UI: case RG16: case RG16F: case RG16I: case RG16UI: case RG16_SNORM: case RG32F: case RG32I: case RG32UI: case RG8: sFormat = RG; break;
		case RGB4: case RGB5: case RGB8_SNORM: case RGB8I: case RGB8UI: case RGB10: case RGB12: case RGB16_SNORM: case RGB16F: case RGB16I: case RGB16UI: case RGB32F: case RGB32I: case RGB32UI: case RGB8: sFormat = RGB; break;
		case RGBA2: case RGBA4: case RGBA8_SNORM: case RGBA12: case RGBA16: case RGBA16F: case RGBA32F: case RGBA8I: case RGBA8UI: case RGBA16I: case RGBA16UI: case RGBA32I: case RGBA32UI: case RGBA8: sFormat = RGBA; break;
		case DEPTH_COMPONENT16: case DEPTH_COMPONENT24: case DEPTH_COMPONENT32F: case DEPTH24_STENCIL8: case DEPTH32F_STENCIL8: case DEPTH_COMPONENT32: sFormat = DEPTH_COMPONENT; sType = UNSIGNED_INT; break;
	}
	loadFromRaw(nullptr, sizeX, sizeY, sizeZ, sFormat, sType, format, false, slot);
}

void Texture3D::loadFromRaw(const void* pixels, unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ, Texture::SourceFormat sourceFormat, Texture::SourceType sourceType, Texture::InternalFormat internalFormat, bool mipmap, int slot) {
	if(slot != -1)
		setSlot(slot);
	format = internalFormat;
	size = vec3i(sizeX, sizeY, sizeZ);
	bind();
	GL_ASSERT(glTexImage3D(GL_TEXTURE_3D, 0, internalFormat, sizeX, sizeY, sizeZ, 0, sourceFormat, sourceType, (GLvoid*) pixels));
	if(mipmap) {
		GL_ASSERT(glGenerateMipmap(GL_TEXTURE_3D));
		setFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	}
	else
		setFilter(GL_LINEAR, GL_LINEAR);
	setWrap(GL_REPEAT);
}

void Texture3D::resize(unsigned int sizeX, unsigned int sizeY, unsigned sizeZ) {
	loadEmpty(sizeX, sizeY, sizeZ, format, slot);
}

int Texture3D::getWidth() const {
	return size.x;
}

int Texture3D::getHeight() const {
	return size.y;
}

int Texture3D::getDepth() const {
	return size.z;
}

void Texture3D::bind() const {
	VBE_ASSERT(handle !=0);
	GL_ASSERT(glActiveTexture(GL_TEXTURE0 + slot));
	GL_ASSERT(glBindTexture(GL_TEXTURE_3D, handle));
}

void Texture3D::setFilter(GLenum min, GLenum mag) {
	bind();
	GL_ASSERT(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, min));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, mag));
}

void Texture3D::setWrap(GLenum wrap) {
	bind();
	GL_ASSERT(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, wrap));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, wrap));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, wrap));
}
