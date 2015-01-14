#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <iostream>
#include <memory>

#include <VBE/graphics/Texture.hpp>

class Texture2D : public Texture {
	public:
		static Texture2D load(
				std::unique_ptr<std::istream> in,
				TextureFormat::Format format = TextureFormat::AUTO);

		Texture2D();
		Texture2D(vec2ui size,
				  TextureFormat::Format format = TextureFormat::RGBA);

		void setData(const void* pixels,
					 TextureFormat::Format sourceFormat = TextureFormat::RGBA,
					 TextureFormat::SourceType sourceType = TextureFormat::UNSIGNED_BYTE);

		void generateMipmap();
		vec2ui getSize() const;

		static void bind(const Texture2D* tex, unsigned int slot) {
			Texture::bind(Texture::Type2D, tex, slot);
		}

		Texture2D(Texture2D&& rhs);
		Texture2D& operator=(Texture2D&& rhs);
		friend void swap(Texture2D& a, Texture2D& b);

	private:
		vec2ui size = vec2ui(0);
};

#endif // TEXTURE2D_HPP
