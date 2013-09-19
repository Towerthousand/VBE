#ifndef Texture_HPP
#define Texture_HPP
#include "../tools.hpp"

class Texture
{
	public:
		Texture(unsigned int slot);
		~Texture();

		void setFilter(GLenum filter) const;
		void setWrap(GLenum wrap) const;
		void setSlot(unsigned int newSlot);
		unsigned int getSlot() const;
		int getWidth() const;
		int getHeight() const;
		void bind() const;
	private:
		GLuint getHandle() const;
		bool load(const std::string& filePath);
		GLuint m_sampler;
		GLuint m_handle;
		unsigned int m_slot;
		vec2i m_size;

		friend class TextureManager;
};

#endif // Texture_HPP
