#ifndef Texture_HPP
#define Texture_HPP
#include "../tools.hpp"
#include "TextureFormat.hpp"

class Texture : public NonCopyable {
	public:
		virtual ~Texture();

		void setSlot(unsigned int newSlot);
		unsigned int getSlot() const;
		GLuint getHandle() const;
		TextureFormat::Format getFormat() const;
	protected:
		Texture();
		GLuint handle;
		unsigned int slot;
		TextureFormat::Format format;
	private:
		static unsigned int lastSlot;
		static int maxSlots;
};

#endif // Texture_HPP
