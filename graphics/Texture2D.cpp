#include "Texture2D.hpp"

Texture2D::Texture2D() : size(0) {
}

Texture2D::~Texture2D() {
}


// static
Texture2D* Texture2D::createFromFile(const std::string& filePath) {
	Texture2D* t = new Texture2D();
	t->loadFromFile(filePath);
	return t;
}

// static
Texture2D* Texture2D::createFromRaw(
		const void* pixels,
		unsigned int sizeX,
		unsigned int sizeY,
		TextureFormat::Format format,
		TextureFormat::SourceType sourceType) {

	Texture2D* t = new Texture2D();
	t->loadFromRaw(pixels, sizeX, sizeY, format, sourceType);
	return t;
}

// static
Texture2D* Texture2D::createEmpty(
		unsigned int sizeX,
		unsigned int sizeY,
		TextureFormat::Format format) {

	Texture2D* t = new Texture2D();
	t->loadEmpty(sizeX, sizeY, format);
	return t;
}


void Texture2D::loadFromFile(const std::string& filePath) {
	//load image
	VBE_DLOG("* Loading new Texture2D from path " << filePath);
	int width, height, channels;
	unsigned char* ptr = STBI::stbi_load(filePath.c_str(), &width, &height, &channels, 0);
	VBE_ASSERT(ptr && width && height, "Failed to load image \"" << filePath << "\". Reason : " << STBI::stbi_failure_reason());
	loadFromRaw(ptr, width, height, TextureFormat::channelsToFormat(channels), TextureFormat::UNSIGNED_BYTE);
	STBI::stbi_image_free(ptr);
}

void Texture2D::loadFromRaw(
		const void* pixels,
		unsigned int sizeX,
		unsigned int sizeY,
		TextureFormat::Format format,
		TextureFormat::SourceType sourceType) {

	this->format = format;
	size = vec2i(sizeX, sizeY);
	bind();
    GL_ASSERT(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
    GL_ASSERT(glPixelStorei(GL_PACK_ALIGNMENT, 1));
	GL_ASSERT(glTexImage2D(GL_TEXTURE_2D, 0, format, sizeX, sizeY, 0, TextureFormat::getBaseFormat(format), sourceType, (GLvoid*) pixels));
	setFilter(GL_LINEAR, GL_LINEAR);
	setWrap(GL_REPEAT);
}

void Texture2D::loadEmpty(
		unsigned int sizeX,
		unsigned int sizeY,
		TextureFormat::Format format) {
	loadFromRaw(nullptr, sizeX, sizeY, format);
}

void Texture2D::generateMipmap() {
	GL_ASSERT(glGenerateMipmap(GL_TEXTURE_2D));
	setFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
}

void Texture2D::resize(unsigned int sizeX, unsigned int sizeY) {
	loadEmpty(sizeX, sizeY, format);
}

#ifndef VBE_GLES2
void Texture2D::setComparison(GLenum func, GLenum mode) {
	VBE_ASSERT(format == DEPTH_COMPONENT16 || format == DEPTH_COMPONENT24 || format == DEPTH_COMPONENT32 || format == DEPTH_COMPONENT32F || format == DEPTH24_STENCIL8 || format == DEPTH32F_STENCIL8, "Can't set comparison for a non-depth, non_stencil texture");
	bind();
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, func));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, mode));
}
#endif

int Texture2D::getWidth() const {
	return size.x;
}

int Texture2D::getHeight() const {
	return size.y;
}

vec2i Texture2D::getSize() const {
	return size;
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
}
