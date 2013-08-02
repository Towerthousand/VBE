#ifndef Texture_HPP
#define Texture_HPP
#include "tools.hpp"

class Texture
{
	public:
		Texture();
		~Texture();

		bool load(const std::string& filePath);
		void bind() const;
		void setFilter(GLenum filter) const;
		void setWrap(GLenum wrap) const;

		GLuint getHandle() const;

		int getWidth() const;
		int getHeight() const;
	private:
		GLuint handle;
		vec2i size;
};

#endif // Texture_HPP
