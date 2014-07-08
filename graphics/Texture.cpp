#include "Texture.hpp"

unsigned int Texture::lastSlot = 0;
int Texture::maxSlots = -1;

Texture::Texture(): handle(0), slot(0) {
	if(maxSlots == -1) {
		int max;
		GL_ASSERT(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS_ARB, &max));
		VBE_DLOG("* Platform info: Max concurrent texture images: " << max);
		maxSlots = max;
	}
	lastSlot = lastSlot%(maxSlots-1);
	slot = lastSlot++;
	GL_ASSERT(glGenTextures(1, &handle));
	VBE_ASSERT(handle != 0, "Failed to create texture");
}

Texture::~Texture(){
	GL_ASSERT(glDeleteTextures(1, (GLuint*) &handle));
}

void Texture::setSlot(unsigned int newSlot) {
	VBE_ASSERT(int(newSlot) < maxSlots, "Trying to use impossible texture slot " << newSlot << ". Maximum is " << maxSlots);
	slot = newSlot;
}

unsigned int Texture::getSlot() const {
	return slot;
}

GLuint Texture::getHandle() const {
	return handle;
}

Texture::InternalFormat Texture::getFormat() const {
	return format;
}
