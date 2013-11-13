#include "Texture.hpp"

unsigned int Texture::lastSlot = 0;

Texture::Texture(): handle(0), slot(0), size(0,0){
	lastSlot = lastSlot%(GL_MAX_TEXTURE_UNITS-GL_TEXTURE0-2);
	slot = lastSlot++;
	glGenTextures(1, &handle);
}

Texture::~Texture(){
	glDeleteTextures(1,(GLuint*) &handle);
}

bool Texture::loadFromFile(const std::string &filePath, Format format, bool mipmap) {
	//load image
	sf::Image image;
	if (!image.loadFromFile(filePath)) {
		VBE_LOG("#ERROR " << filePath << " didn't load" );
		return false;
	}
	return loadRaw(image.getPixelsPtr(),image.getSize().x,image.getSize().y, format, mipmap);
}

bool Texture::loadRaw(const void* pixels, unsigned int sizeX, unsigned int sizeY, Format format, bool mipmap) {
	this->format = format;
	size = vec2i(sizeX,sizeY);

	//bind handle and set to image
	bind();
	glTexImage2D(
				GL_TEXTURE_2D, 0, ((format==DEPTH_COMPONENT)?GL_DEPTH_COMPONENT32:format),
				sizeX, sizeY,
				0,
				format, GL_UNSIGNED_BYTE, (GLvoid*) pixels
				);

	if(mipmap) {
		glGenerateMipmap(GL_TEXTURE_2D);
		setFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	}
	else
		setFilter(GL_LINEAR, GL_LINEAR);

	setWrap(GL_REPEAT);
	return true;
}

void Texture::bind() const {
	VBE_ASSERT(handle !=0, "Trying to bind nullptr texture into slot " << slot);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, handle);
}

void Texture::setFilter(GLenum min, GLenum mag) {
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
}

void Texture::setWrap(GLenum wrap) const {
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
}

void Texture::setComparison(GLenum func, GLenum mode) {
	VBE_ASSERT(format == DEPTH_COMPONENT || format == DEPTH_STENCIL, "Can't set comparison for a non-depth, non_stencil texture");
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, func);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, mode);
}

void Texture::setSlot(unsigned int newSlot) {
	VBE_ASSERT(newSlot < GL_MAX_TEXTURE_UNITS, "Trying to use impossible texture slot " << newSlot << ". Maximum is " << GL_MAX_TEXTURE_UNITS);
	slot = newSlot;
}

unsigned int Texture::getSlot() const {
	return slot;
}

GLuint Texture::getHandle() const {
	return handle;
}

int Texture::getWidth() const {
	return size.x;
}
int Texture::getHeight() const {
	return size.y;
}
