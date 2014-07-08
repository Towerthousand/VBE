#include "TextureCubemap.hpp"

TextureCubemap::TextureCubemap() : size(0) {
}

TextureCubemap::~TextureCubemap() {
}

TextureCubemap* TextureCubemap::createEmpty(unsigned int size, Texture::InternalFormat format, int slot) {
	TextureCubemap* t = new TextureCubemap();
	t->loadEmpty(size, format, slot);
	return t;
}

TextureCubemap* TextureCubemap::createFromFiles(const std::vector<std::string>& filePaths, Texture::SourceFormat sourceFormat, Texture::SourceType sourceType, Texture::InternalFormat internalFormat, bool mipmap, int slot) {
	TextureCubemap* t = new TextureCubemap();
	t->loadFromFiles(filePaths, sourceFormat, sourceType, internalFormat, mipmap, slot);
	return t;
}

TextureCubemap* TextureCubemap::createFromRaw(const void* pixels, unsigned int size, Texture::SourceFormat sourceFormat, Texture::SourceType sourceType, Texture::InternalFormat internalFormat, bool mipmap, int slot) {
	TextureCubemap* t = new TextureCubemap();
	t->loadFromRaw(pixels, size, sourceFormat, sourceType, internalFormat, mipmap, slot);
	return t;
}

void TextureCubemap::loadEmpty(unsigned int size, Texture::InternalFormat format, int slot) {
	SourceFormat sFormat = RGBA;
	SourceType sType = UNSIGNED_BYTE;
	switch (format) {
		case R8_SNORM: case R8I: case R8UI: case R16: case R16F: case R16I: case R16UI: case R16_SNORM: case R32F: case R32I: case R32UI: case R8: sFormat = RED; break;
		case RG8_SNORM: case RG8I: case RG8UI: case RG16: case RG16F: case RG16I: case RG16UI: case RG16_SNORM: case RG32F: case RG32I: case RG32UI: case RG8: sFormat = RG; break;
		case RGB4: case RGB5: case RGB8_SNORM: case RGB8I: case RGB8UI: case RGB10: case RGB12: case RGB16_SNORM: case RGB16F: case RGB16I: case RGB16UI: case RGB32F: case RGB32I: case RGB32UI: case RGB8: sFormat = RGB; break;
		case RGBA2: case RGBA4: case RGBA8_SNORM: case RGBA12: case RGBA16: case RGBA16F: case RGBA32F: case RGBA8I: case RGBA8UI: case RGBA16I: case RGBA16UI: case RGBA32I: case RGBA32UI: case RGBA8: sFormat = RGBA; break;
		case DEPTH_COMPONENT16: case DEPTH_COMPONENT24: case DEPTH_COMPONENT32F: case DEPTH24_STENCIL8: case DEPTH32F_STENCIL8: case DEPTH_COMPONENT32: sFormat = DEPTH_COMPONENT; sType = UNSIGNED_INT; break;
	}
	loadFromRaw(nullptr, size, sFormat, sType, format, false, slot);
}

void TextureCubemap::loadFromFiles(const std::vector<std::string>& filePaths, Texture::SourceFormat sourceFormat, Texture::SourceType sourceType, Texture::InternalFormat internalFormat, bool mipmap, int slot) {
	// check 6 faces provided
	VBE_ASSERT(filePaths.size() >= 6, "Less than 6 textures provided for the cubemap");
	if (filePaths.size() > 6) VBE_LOG("Provided more than 6 textures for a cubemap, last images ignored");

	// load images
	int sizeLoaded = 0;
	unsigned char* pixels = nullptr;
	for (unsigned int i = 0; i < 6; i++) {
		//load image
		VBE_DLOG("* Loading cubemap face from path " << filePaths[i]);
		int width, height, channels;
		int comp_req = 0;
		switch(sourceFormat) {
			case RGB: comp_req = STBI::STBI_rgb; break;
			case RGBA: comp_req = STBI::STBI_rgb_alpha; break;
			default: break;
		}
		VBE_ASSERT(comp_req != 0 && sourceType == UNSIGNED_BYTE, "While loading texture: uncompatible source format? Try a RGBA8888 kind of image or a RGB888 one");
		unsigned char* ptr = STBI::stbi_load(filePaths[i].c_str(), &width, &height, &channels, comp_req);
		VBE_ASSERT(ptr && width && height, "Failed to load image \"" << filePaths[i] << "\". Reason : " << STBI::stbi_failure_reason());
		if (i == 0) {
			sizeLoaded = width;
			pixels = new unsigned char[4*size*size*6];
		}
		VBE_ASSERT(width == sizeLoaded && height == sizeLoaded, "Image " << i << ": " << filePaths[i] << " has a wrong size.");
		memcpy((void*)&pixels[4*i*sizeLoaded*sizeLoaded*sizeof(unsigned char)], (void*)ptr, 4*sizeLoaded*sizeLoaded*sizeof(unsigned char));
		STBI::stbi_image_free(ptr);
	}

	loadFromRaw(pixels, sizeLoaded, sourceFormat, sourceType, internalFormat, mipmap, slot);
	delete[] pixels;
}

void TextureCubemap::loadFromRaw(const void* pixels, unsigned int size, Texture::SourceFormat sourceFormat, Texture::SourceType sourceType, Texture::InternalFormat internalFormat, bool mipmap, int slot) {
	if(slot != -1)
		setSlot(slot);
	format = internalFormat;
	this->size = size;
	bind();

	unsigned char* pface = (unsigned char*)pixels;
	for (int i = 0; i < 6; i++) {
		cubeFaces target;
		switch (i) {
			case 0:	target = CUBEMAP_POSITIVE_X; break;
			case 1:	target = CUBEMAP_NEGATIVE_X; break;
			case 2:	target = CUBEMAP_POSITIVE_Y; break;
			case 3:	target = CUBEMAP_NEGATIVE_Y; break;
			case 4: target = CUBEMAP_POSITIVE_Z; break;
			case 5:	target = CUBEMAP_NEGATIVE_Z; break;
		}
		if (pface)
			GL_ASSERT(glTexImage2D(target, 0, internalFormat, size, size, 0, sourceFormat, sourceType, (GLvoid*)(pface + i*size*size*4)));
		else
			GL_ASSERT(glTexImage2D(target, 0, internalFormat, size, size, 0, sourceFormat, sourceType, 0));
	}

	if(mipmap) {
		GL_ASSERT(glGenerateMipmap(GL_TEXTURE_CUBE_MAP));
		setFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	}
	else
		setFilter(GL_LINEAR, GL_LINEAR);
	setWrap(GL_CLAMP_TO_EDGE);
}

void TextureCubemap::resize(unsigned int newSize) {
	loadEmpty(newSize, format, slot);
}

void TextureCubemap::setComparison(GLenum func, GLenum mode) {
	VBE_ASSERT(format == DEPTH_COMPONENT16 || format == DEPTH_COMPONENT24 || format == DEPTH_COMPONENT32 || format == DEPTH_COMPONENT32F || format == DEPTH24_STENCIL8 || format == DEPTH32F_STENCIL8, "Can't set comparison for a non-depth, non_stencil texture");
	bind();
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_FUNC, func));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, mode));
}

int TextureCubemap::getWidth() const {
	return size;
}

int TextureCubemap::getHeight() const {
	return size;
}

void TextureCubemap::bind() const {
	VBE_ASSERT(handle !=0, "Trying to bind nullptr texture into slot " << slot);
	GL_ASSERT(glActiveTexture(GL_TEXTURE0 + slot));
	GL_ASSERT(glBindTexture(GL_TEXTURE_CUBE_MAP, handle));
}

void TextureCubemap::setFilter(GLenum min, GLenum mag) {
	bind();
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, min));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, mag));
}

void TextureCubemap::setWrap(GLenum wrap) {
	bind();
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, wrap));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, wrap));
	GL_ASSERT(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, wrap));
}
