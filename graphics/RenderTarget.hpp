#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP
#include "../tools.hpp"
#include "environment/Environment.hpp"
#include "Texture2D.hpp"

class RenderTarget {
	public:
		enum Attachment {
			DEPTH = GL_DEPTH_ATTACHMENT,
			STENCIL = GL_STENCIL_ATTACHMENT,
			DEPTH_STENCIL = GL_DEPTH_STENCIL_ATTACHMENT,
			COLOR0 = GL_COLOR_ATTACHMENT0,
			COLOR1 = GL_COLOR_ATTACHMENT1,
			COLOR2 = GL_COLOR_ATTACHMENT2,
			COLOR3 = GL_COLOR_ATTACHMENT3,
			COLOR4 = GL_COLOR_ATTACHMENT4,
			COLOR5 = GL_COLOR_ATTACHMENT5,
			COLOR6 = GL_COLOR_ATTACHMENT6,
			COLOR7 = GL_COLOR_ATTACHMENT7,
			COLOR8 = GL_COLOR_ATTACHMENT8,
			COLOR9 = GL_COLOR_ATTACHMENT9,
			COLOR10 = GL_COLOR_ATTACHMENT10,
			COLOR11 = GL_COLOR_ATTACHMENT11,
			COLOR12 = GL_COLOR_ATTACHMENT12,
			COLOR13 = GL_COLOR_ATTACHMENT13,
			COLOR14 = GL_COLOR_ATTACHMENT14,
			COLOR15 = GL_COLOR_ATTACHMENT15
		};

		RenderTarget();
		RenderTarget(int width, int height);
		RenderTarget(float mult);
		~RenderTarget();

		static void bind(RenderTarget* renderTarget);
		static RenderTarget* getCurrent();

		int getWidth() const { return size.x; }
		int getHeight() const { return size.y; }
		vec2i getSize() const { return size; }
		vec2i getDesiredSize() const {
			if(screenRelativeSize)
				return vec2i(int(Environment::getScreen()->getWidth()*screenSizeMultiplier), int(Environment::getScreen()->getHeight()*screenSizeMultiplier));
			else
				return size;
		}

		void addRenderBuffer(Attachment target, Texture::InternalFormat format);
		void addTexture(Attachment target, Texture::InternalFormat format);

		Texture2D* getTextureForAttachment(Attachment attachment);
		const Texture2D* getTextureForAttachment(Attachment attachment) const;

		void build();
		void destroy();

	private:

		void checkSize();

		class RenderBuffer {
			public:
				RenderBuffer(int width, int height, Texture::InternalFormat format);
				~RenderBuffer();

				void resize(int width, int height);
				void bind() const;
				GLuint getHandle() const;
			private:
				Texture::InternalFormat format;
				GLuint handle;
		};


		class RenderTargetEntry {
			public:
				enum Type {
					RenderBufferEntry,
					TextureEntry
				};

				RenderTargetEntry(Type type, RenderTarget::Attachment attachment, Texture::InternalFormat format) :
					type(type), attachment(attachment), format(format), texture(nullptr), renderBuffer(nullptr) {}

				Type type;
				RenderTarget::Attachment attachment;
				Texture::InternalFormat format;

				Texture2D* texture;
				RenderBuffer* renderBuffer;
		};

		static RenderTarget* current;

		GLuint handle; // 0 if not built
		vec2i size;
		bool screenRelativeSize;
		float screenSizeMultiplier;

		std::map<Attachment, RenderTargetEntry> entries;
};

#endif // RENDERTARGET_HPP
