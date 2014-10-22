#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/Texture.hpp>
#include <VBE/system/Log.hpp>

// static
int Texture::maxSlots = -1;

//static
unsigned int Texture::getMaxSlots() {
	if(maxSlots == -1) {
		GL_ASSERT(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxSlots));
		VBE_DLOG("* Platform info: Max concurrent texture images: " << maxSlots);
	}
}

// static
void Texture::bind(Texture::Type type, const Texture* tex, int slot) {
	GL_ASSERT(glActiveTexture(GL_TEXTURE0 + slot));

	if(tex != nullptr)
		GL_ASSERT(glBindTexture(type, tex->handle));
	else
		GL_ASSERT(glBindTexture(type, 0));
}

Texture::Texture(Type type): handle(0), type(type) {
	GL_ASSERT(glGenTextures(1, &handle));
	VBE_ASSERT(handle != 0, "Failed to create texture");
}

Texture::~Texture(){
	GL_ASSERT(glDeleteTextures(1, (GLuint*) &handle));
}

GLuint Texture::getHandle() const {
	return handle;
}

TextureFormat::Format Texture::getFormat() const {
	return format;
}

Texture::Type Texture::getType() const {
	return type;
}

#ifndef VBE_GLES2
void Texture::setComparison(GLenum func, GLenum mode) {
	VBE_ASSERT(TextureFormat::isDepth(format), "Can't set comparison for a non-depth, non_stencil texture");
	Texture::bind(type, this, 0);
	GL_ASSERT(glTexParameteri(type, GL_TEXTURE_COMPARE_FUNC, func));
	GL_ASSERT(glTexParameteri(type, GL_TEXTURE_COMPARE_MODE, mode));
}
#endif

void Texture::setFilter(GLenum min, GLenum mag) {
	Texture::bind(type, this, 0);
	GL_ASSERT(glTexParameteri(type, GL_TEXTURE_MIN_FILTER, min));
	GL_ASSERT(glTexParameteri(type, GL_TEXTURE_MAG_FILTER, mag));
}

void Texture::setWrap(GLenum wrap) {
	Texture::bind(type, this, 0);
	GL_ASSERT(glTexParameteri(type, GL_TEXTURE_WRAP_S, wrap));
	GL_ASSERT(glTexParameteri(type, GL_TEXTURE_WRAP_T, wrap));
}
