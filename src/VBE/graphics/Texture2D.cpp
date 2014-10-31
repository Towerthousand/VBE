#include <VBE/config.hpp>
#include <VBE/dependencies/stb_image/stb_image.hpp>
#include <VBE/graphics/Image.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/Texture2D.hpp>
#include <VBE/system/Log.hpp>

Texture2D::Texture2D() : Texture(Texture::Type2D), size(0) {
}

void Texture2D::load(
		std::unique_ptr<std::istream> in,
		TextureFormat::Format internalFormat) {

	VBE_DLOG("* Loading new Texture2D from path " << filePath);

	Image img = Image::load(std::move(in));

	TextureFormat::Format sourceFormat = img.getGlFormat();
	if(internalFormat == TextureFormat::AUTO)
		internalFormat = sourceFormat;

	loadFromRaw(img.getData(), img.getSize(), sourceFormat, TextureFormat::UNSIGNED_BYTE, internalFormat);
}

void Texture2D::loadEmpty(
		vec2ui size,
		TextureFormat::Format internalFormat) {

	loadFromRaw(nullptr, size, TextureFormat::getBaseFormat(internalFormat), TextureFormat::UNSIGNED_BYTE, internalFormat);
}

void Texture2D::loadFromRaw(
		const void *pixels,
		vec2ui size,
		TextureFormat::Format sourceFormat,
		TextureFormat::SourceType sourceType,
		TextureFormat::Format internalFormat) {

	if (internalFormat == TextureFormat::AUTO)
		internalFormat = sourceFormat;

	this->format = internalFormat;
	this->size = size;
	Texture2D::bind(this, 0);
	GL_ASSERT(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
	GL_ASSERT(glPixelStorei(GL_PACK_ALIGNMENT, 1));
	GL_ASSERT(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, size.x, size.y, 0, sourceFormat, sourceType, (GLvoid*) pixels));
	setFilter(GL_LINEAR, GL_LINEAR);
	setWrap(GL_REPEAT);
}

void Texture2D::generateMipmap() {
	Texture2D::bind(this, 0);
	GL_ASSERT(glGenerateMipmap(GL_TEXTURE_2D));
	setFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
}

vec2ui Texture2D::getSize() const {
	return size;
}

Texture2D::Texture2D(Texture2D&& rhs) : Texture2D() {
	using std::swap;
	swap(*this, rhs);
}

Texture2D& Texture2D::operator=(Texture2D&& rhs) {
	using std::swap;
	swap(*this, rhs);
	return *this;
}

void swap(Texture2D& a, Texture2D& b) {
	using std::swap;
	swap(static_cast<Texture&>(a), static_cast<Texture&>(b));
	swap(a.size, b.size);
}
