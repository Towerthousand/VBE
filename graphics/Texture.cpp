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
