#include <VBE/config.hpp>
#include <VBE/dependencies/stb_image/stb_image.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/Texture3D.hpp>
#include <VBE/system/Log.hpp>

// 3D textures are not supported in GLES2
#ifndef VBE_GLES2

Texture3D::Texture3D() : Texture(Texture::Type3D), size(0) {
}

void Texture3D::loadEmpty(
		vec3ui size,
		TextureFormat::Format internalFormat) {
	loadFromRaw(nullptr, size, TextureFormat::getBaseFormat(internalFormat), TextureFormat::UNSIGNED_BYTE, internalFormat);
}

void Texture3D::loadFromRaw(
		const void *pixels,
		vec3ui size,
		TextureFormat::Format sourceFormat,
		TextureFormat::SourceType sourceType,
		TextureFormat::Format internalFormat) {

	if (internalFormat == TextureFormat::AUTO)
		internalFormat = sourceFormat;

	this->format = internalFormat;
	this->size = size;
	Texture3D::bind(this, 0);
	GL_ASSERT(glTexImage3D(GL_TEXTURE_3D, 0, internalFormat, size.x, size.y, size.z, 0, sourceFormat, sourceType, (GLvoid*) pixels));
	setFilter(GL_LINEAR, GL_LINEAR);
	setWrap(GL_REPEAT);
}

vec3ui Texture3D::getSize() const {
	return size;
}

Texture3D::Texture3D(Texture3D&& rhs) : Texture3D() {
	using std::swap;
	swap(*this, rhs);
}

Texture3D& Texture3D::operator=(Texture3D&& rhs) {
	using std::swap;
	swap(*this, rhs);
	return *this;
}

void swap(Texture3D& a, Texture3D& b) {
	using std::swap;
	swap(static_cast<Texture&>(a), static_cast<Texture&>(b));
	swap(a.size, b.size);
}

#endif // VBE_GLES2