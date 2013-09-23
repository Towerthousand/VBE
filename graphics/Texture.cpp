#include "Texture.hpp"

Texture::Texture(unsigned int slot): handle(0), slot(slot), size(0,0){
	VBE_ASSERT(slot < GL_MAX_TEXTURE_UNITS, "Trying to use impossible texture slot " << slot << ". Maximum is " << GL_MAX_TEXTURE_UNITS);
}

Texture::~Texture(){
	glDeleteTextures(1,(GLuint*) &handle);
}

bool Texture::load(const std::string &filePath) {
	//load image
	sf::Image image;
	if (!image.loadFromFile(filePath)) {
		VBE_LOG("#ERROR " << filePath << " didn't load" );
		return false;
	}
	size = vec2i(image.getSize().x,image.getSize().y);
	
	//get handle
	GLuint tex_handle;
	glGenTextures(1, &tex_handle);
	handle = tex_handle;
	
	//bind handle and set to image
	bind();
	glTexImage2D(
				GL_TEXTURE_2D, 0, GL_RGBA,
				image.getSize().x, image.getSize().y,
				0,
				GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr()
				);
	setFilter(GL_NEAREST);
	setWrap(GL_REPEAT);
	return true;
}

void Texture::bind() const {
	VBE_ASSERT(handle !=0, "Trying to bind null texture into slot " << slot);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, handle);
}

void Texture::setFilter(GLenum filter) const {
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
}

void Texture::setWrap(GLenum wrap) const {
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
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
