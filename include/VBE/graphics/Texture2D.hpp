#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP
#include "Texture.hpp"

class Texture2D : public Texture {
	public:
		~Texture2D();

		static Texture2D* createFromFile(const std::string& filePath);
		static Texture2D* createFromFile(const std::string& filePath, TextureFormat::Format customFormat);
		static Texture2D* createFromRaw(
				const void* pixels,
				unsigned int sizeX,
				unsigned int sizeY,
				TextureFormat::Format format = TextureFormat::RGBA,
				TextureFormat::SourceType sourceType = TextureFormat::UNSIGNED_BYTE);

		static Texture2D* createEmpty(
				unsigned int sizeX,
				unsigned int sizeY,
				TextureFormat::Format format = TextureFormat::RGBA);

		void loadFromFile(const std::string& filePath);
		void loadFromFile(const std::string& filePath, TextureFormat::Format customFormat);
		void loadFromRaw(
				const void* pixels,
				unsigned int sizeX,
				unsigned int sizeY,
				TextureFormat::Format format = TextureFormat::RGBA,
				TextureFormat::SourceType sourceType = TextureFormat::UNSIGNED_BYTE);

		void loadEmpty(
				unsigned int sizeX,
				unsigned int sizeY,
				TextureFormat::Format format = TextureFormat::RGBA);

		void generateMipmap();
		void resize(unsigned int sizeX, unsigned int sizeY);
#ifndef VBE_GLES2
		void setComparison(GLenum func, GLenum mode = GL_COMPARE_REF_TO_TEXTURE);
#endif
		int getWidth() const;
		int getHeight() const;
		vec2i getSize() const;

		void setFilter(GLenum min, GLenum mag);
		void setWrap(GLenum wrap);
		void bind() const;

	private:

		void load(const void* pixels,
				  unsigned int sizeX,
				  unsigned int sizeY,
				  TextureFormat::Format format,
				  TextureFormat::Format sourceFormat,
				  TextureFormat::SourceType sourceType);
		Texture2D();
		vec2i size;
};

#endif // TEXTURE2D_HPP
