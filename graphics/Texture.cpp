#include "Texture.hpp"

unsigned int Texture::lastSlot = 0;

Texture::Texture(): handle(0), slot(0) {
	lastSlot = lastSlot%(GL_MAX_TEXTURE_UNITS-GL_TEXTURE0-2);
	slot = lastSlot++;
	glGenTextures(1, &handle);
}

Texture::~Texture(){
	glDeleteTextures(1, (GLuint*) &handle);
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrap);
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
