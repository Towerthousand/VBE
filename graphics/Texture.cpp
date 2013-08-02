#include "Texture.hpp"

Texture::Texture(): handle(0), size(0,0){
}

Texture::~Texture(){
	glDeleteTextures(1,(GLuint*) &handle);
}

bool Texture::load(const std::string &filePath) {
	//load image
	sf::Image image;
	if (!image.loadFromFile(filePath)) {
		outLog("#ERROR " + filePath + " didn't load");
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

GLuint Texture::getHandle() const {
	return handle;
}

int Texture::getWidth() const {
	return size.x;
}
int Texture::getHeight() const {
	return size.y;
}
