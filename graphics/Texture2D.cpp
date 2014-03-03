#include "Texture2D.hpp"

Texture2D::Texture2D() : size(0) {
}

Texture2D::~Texture2D() {
}

Texture2D* Texture2D::createEmpty(unsigned int sizeX, unsigned int sizeY, Texture::InternalFormat format, int slot) {
	Texture2D* t = new Texture2D();
	t->loadEmpty(sizeX, sizeY, format, slot);
	return t;
}

Texture2D* Texture2D::createFromFile(const std::string& filePath, Texture::SourceFormat sourceFormat, Texture::SourceType sourceType, Texture::InternalFormat internalFormat, bool mipmap, int slot) {
	Texture2D* t = new Texture2D();
	t->loadFromFile(filePath, sourceFormat, sourceType, internalFormat, mipmap, slot);
	return t;
}

Texture2D* Texture2D::createFromRaw(const void* pixels, unsigned int sizeX, unsigned int sizeY, Texture::SourceFormat sourceFormat, Texture::SourceType sourceType, Texture::InternalFormat internalFormat, bool mipmap, int slot) {
	Texture2D* t = new Texture2D();
	t->loadFromRaw(pixels, sizeX, sizeY, sourceFormat, sourceType, internalFormat, mipmap, slot);
	return t;
}

void Texture2D::loadEmpty(unsigned int sizeX, unsigned int sizeY, Texture::InternalFormat format, int slot) {
	SourceFormat sFormat = RGBA;
	SourceType sType = UNSIGNED_BYTE;
	switch (format) {
		case R8_SNORM: case R8I: case R8UI: case R16: case R16F: case R16I: case R16UI: case R16_SNORM: case R32F: case R32I: case R32UI: case R8: sFormat = RED; break;
		case RG8_SNORM: case RG8I: case RG8UI: case RG16: case RG16F: case RG16I: case RG16UI: case RG16_SNORM: case RG32F: case RG32I: case RG32UI: case RG8: sFormat = RG; break;
		case RGB4: case RGB5: case RGB8_SNORM: case RGB8I: case RGB8UI: case RGB10: case RGB12: case RGB16_SNORM: case RGB16F: case RGB16I: case RGB16UI: case RGB32F: case RGB32I: case RGB32UI: case RGB8: sFormat = RGB; break;
		case RGBA2: case RGBA4: case RGBA8_SNORM: case RGBA12: case RGBA16: case RGBA16F: case RGBA32F: case RGBA8I: case RGBA8UI: case RGBA16I: case RGBA16UI: case RGBA32I: case RGBA32UI: case RGBA8: sFormat = RGBA; break;
		case DEPTH_COMPONENT16: case DEPTH_COMPONENT24: case DEPTH_COMPONENT32F: case DEPTH24_STENCIL8: case DEPTH32F_STENCIL8: case DEPTH_COMPONENT32: sFormat = DEPTH_COMPONENT; sType = UNSIGNED_INT; break;
	}
	loadFromRaw(nullptr, sizeX, sizeY, sFormat, sType, format, false, slot);
}

void Texture2D::loadFromFile(const std::string& filePath, Texture::SourceFormat sourceFormat, Texture::SourceType sourceType, Texture::InternalFormat internalFormat, bool mipmap, int slot) {
	//load image
	VBE_DLOG("* Loading new Texture2D from path " << filePath);
	int width, height, channels;
	int comp_req = 0;
	switch(sourceFormat) {
		case RGB: comp_req = STBI::STBI_rgb; break;
		case RGBA: comp_req = STBI::STBI_rgb_alpha; break;
		default: break;
	}
	VBE_ASSERT(comp_req != 0 && sourceType == UNSIGNED_BYTE, "While loading texture: uncompatible source format? Try a RGBA8888 kind of image or a RGB888 one");
	unsigned char* ptr = STBI::stbi_load(filePath.c_str(), &width, &height, &channels, comp_req);
	VBE_ASSERT(ptr && width && height, "Failed to load image \"" << filePath << "\". Reason : " << STBI::stbi_failure_reason());
	loadFromRaw(ptr, width, height, sourceFormat, sourceType, internalFormat, mipmap, slot);
	STBI::stbi_image_free(ptr);
}

void Texture2D::loadFromRaw(const void* pixels, unsigned int sizeX, unsigned int sizeY, Texture::SourceFormat sourceFormat, Texture::SourceType sourceType, Texture::InternalFormat internalFormat, bool mipmap, int slot) {
	if(slot != -1)
		setSlot(slot);
	format = internalFormat;
	size = vec2i(sizeX, sizeY);
	bind();
	GL_ASSERT(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, sizeX, sizeY, 0, sourceFormat, sourceType, (GLvoid*) pixels));
	if(mipmap) {
		GL_ASSERT(glGenerateMipmap(GL_TEXTURE_2D));
		setFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	}
	else
		setFilter(GL_LINEAR, GL_LINEAR);
	setWrap(GL_REPEAT);
}

void Texture2D::resize(unsigned int sizeX, unsigned int sizeY) {
	loadEmpty(sizeX, sizeY, format, slot);
}

void Texture2D::setComparison(GLenum func, GLenum mode) {
	VBE_ASSERT(format == DEPTH_COMPONENT16 || format == DEPTH_COMPONENT24 || format == DEPTH_COMPONENT32 || format == DEPTH_COMPONENT32F || format == DEPTH24_STENCIL8 || format == DEPTH32F_STENCIL8, "Can't set comparison for a non-depth, non_stencil texture");
	bind();
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, func));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, mode));
}

int Texture2D::getWidth() const {
	return size.x;
}

int Texture2D::getHeight() const {
	return size.y;
}

void Texture2D::bind() const {
	VBE_ASSERT(handle !=0, "Trying to bind nullptr texture into slot " << slot);
	GL_ASSERT(glActiveTexture(GL_TEXTURE0 + slot));
	GL_ASSERT(glBindTexture(GL_TEXTURE_2D, handle));
}

void Texture2D::setFilter(GLenum min, GLenum mag) {
	bind();
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag));
}

void Texture2D::setWrap(GLenum wrap) {
	bind();
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrap));
}
