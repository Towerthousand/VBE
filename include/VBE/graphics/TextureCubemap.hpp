#ifndef TEXTURECUBEMAP_HPP
#define TEXTURECUBEMAP_HPP
#include "Texture.hpp"

class TextureCubemap : public Texture {
	public:

		enum cubeFaces {
			CUBEMAP_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			CUBEMAP_NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			CUBEMAP_POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			CUBEMAP_NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			CUBEMAP_POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			CUBEMAP_NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
		};

		TextureCubemap();
		~TextureCubemap();


		static TextureCubemap* createFromFiles(const std::vector<std::string>& filePaths);
		static TextureCubemap* createFromRaw(
				const void* pixels,
				unsigned int size,
				TextureFormat::Format format = TextureFormat::RGBA,
				TextureFormat::SourceType sourceType = TextureFormat::UNSIGNED_BYTE);

		static TextureCubemap* createEmpty(
				unsigned int size,
				TextureFormat::Format format = TextureFormat::RGBA);


		void loadFromFiles(const std::vector<std::string>& filePaths);
		void loadFromRaw(
				const void* pixels,
				unsigned int size,
				TextureFormat::Format format = TextureFormat::RGBA,
				TextureFormat::SourceType sourceType = TextureFormat::UNSIGNED_BYTE);

		void loadEmpty(
				unsigned int size,
				TextureFormat::Format format = TextureFormat::RGBA);

		void resize(unsigned int newSize);

#ifndef VBE_GLES2
		void setComparison(GLenum func, GLenum mode = GL_COMPARE_REF_TO_TEXTURE);
#endif
		
		int getWidth() const;
		int getHeight() const;

		void setFilter(GLenum min, GLenum mag);
		void setWrap(GLenum wrap);
		void bind() const;

	private:
		int size;
};

#endif // TEXTURECUBEMAP_HPP
