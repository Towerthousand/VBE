#ifndef Texture_HPP
#define Texture_HPP
#include "tools.hpp"

class Texture
{
	public:
		Texture();
		~Texture();

		void setFilter(GLenum filter) const;
		void setWrap(GLenum wrap) const;
		int getWidth() const;
		int getHeight() const;
	private:
		GLuint getHandle() const;
		bool load(const std::string& filePath);
		void bind() const;
		GLuint sampler;
		GLuint handle;
		vec2i size;

		friend class TextureManager;
};

#endif // Texture_HPP
