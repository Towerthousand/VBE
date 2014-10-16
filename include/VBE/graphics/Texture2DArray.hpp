#ifndef TEXTURE2DARRAY_HPP
#define TEXTURE2DARRAY_HPP
#include "Texture.hpp"

// Texture arrays are not supported in GLES2
#ifndef VBE_GLES2

class Texture2DArray : public Texture {
	public:
		Texture2DArray();
		~Texture2DArray();


		static Texture2DArray* createFromFiles(const std::vector<std::string>& filePaths);
		static Texture2DArray* createFromRaw(
				const void* pixels,
				unsigned int sizeX,
				unsigned int sizeY,
				unsigned int slices,
				TextureFormat::Format format = TextureFormat::RGBA,
				TextureFormat::SourceType sourceType = TextureFormat::UNSIGNED_BYTE);

		static Texture2DArray* createEmpty(
				unsigned int sizeX,
				unsigned int sizeY,
				unsigned int slices,
				TextureFormat::Format format = TextureFormat::RGBA);


		void loadFromFiles(const std::vector<std::string>& filePaths);
		void loadFromRaw(
				const void* pixels,
				unsigned int sizeX,
				unsigned int sizeY,
				unsigned int slices,
				TextureFormat::Format format = TextureFormat::RGBA,
				TextureFormat::SourceType sourceType = TextureFormat::UNSIGNED_BYTE);

		void loadEmpty(
				unsigned int sizeX,
				unsigned int sizeY,
				unsigned int slices,
				TextureFormat::Format format = TextureFormat::RGBA);

		void resize(unsigned int sizeX, unsigned int sizeY, unsigned int slices);
#ifndef VBE_GLES2
		void setComparison(GLenum func, GLenum mode = GL_COMPARE_REF_TO_TEXTURE);
#endif
		unsigned int getWidth() const;
		unsigned int getHeight() const;
		vec3ui getSize() const;
		unsigned int getSlices() const;

		void setFilter(GLenum min, GLenum mag);
		void setWrap(GLenum wrap);
		void bind() const;

	private:
		vec3ui size;
};

#endif // VBE_GLES2
#endif // TEXTURE2DARRAY_HPP
