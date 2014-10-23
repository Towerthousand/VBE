#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP
#include "Texture.hpp"

class Texture2D : public Texture {
	public:
		Texture2D();

		void loadFromFile(
				const std::string& filePath,
				TextureFormat::Format internalFormat = TextureFormat::AUTO);

		void loadEmpty(
				vec2ui size,
				TextureFormat::Format internalFormat = TextureFormat::RGBA);

		void loadFromRaw(
				const void* pixels,
				vec2ui size,
				TextureFormat::Format sourceFormat = TextureFormat::RGBA,
				TextureFormat::SourceType sourceType = TextureFormat::UNSIGNED_BYTE,
				TextureFormat::Format internalFormat = TextureFormat::AUTO);

		void generateMipmap();
		vec2ui getSize() const;

		static void bind(const Texture2D* tex, unsigned int slot) {
			Texture::bind(Texture::Type2D, tex, slot);
		}

		Texture2D(Texture2D&& rhs);
		Texture2D& operator=(Texture2D&& rhs);
		friend void swap(Texture2D& a, Texture2D& b);

	private:
		vec2ui size;
};

#endif // TEXTURE2D_HPP
