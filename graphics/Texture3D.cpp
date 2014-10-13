#include "Texture3D.hpp"

// 3D textures are not supported in GLES2
#ifndef VBE_GLES2

Texture3D::Texture3D() : size(0) {
}

Texture3D::~Texture3D() {
}

// static
Texture3D* Texture3D::createFromRaw(
		const void* pixels,
		unsigned int sizeX,
		unsigned int sizeY,
		unsigned int sizeZ,
		TextureFormat::Format format,
		TextureFormat::SourceType sourceType) {

	Texture3D* t = new Texture3D();
	t->loadFromRaw(pixels, sizeX, sizeY, sizeZ, format, sourceType);
	return t;
}

// static
Texture3D* Texture3D::createEmpty(
		unsigned int sizeX,
		unsigned int sizeY,
		unsigned int sizeZ,
		TextureFormat::Format format) {

	Texture3D* t = new Texture3D();
	t->loadEmpty(sizeX, sizeY, sizeZ, format);
	return t;
}

void Texture3D::loadFromRaw(
		const void* pixels,
		unsigned int sizeX,
		unsigned int sizeY,
		unsigned int sizeZ,
		TextureFormat::Format format,
		TextureFormat::SourceType sourceType) {

	this->format = format;
	size = vec3i(sizeX, sizeY, sizeZ);
	bind();
    GL_ASSERT(glTexImage3D(GL_TEXTURE_3D, 0, format, sizeX, sizeY, sizeZ, 0, TextureFormat::getBaseFormat(format), sourceType, (GLvoid*) pixels));
	setFilter(GL_LINEAR, GL_LINEAR);
	setWrap(GL_REPEAT);
}

void Texture3D::loadEmpty(
		unsigned int sizeX,
		unsigned int sizeY,
		unsigned int sizeZ,
		TextureFormat::Format format) {
	loadFromRaw(nullptr, sizeX, sizeY, sizeZ, format);
}

void Texture3D::resize(unsigned int sizeX, unsigned int sizeY, unsigned sizeZ) {
	loadEmpty(sizeX, sizeY, sizeZ, format);
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
	VBE_ASSERT(handle !=0, "Cannot bind null texture");
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

#endif // VBE_GLES2
