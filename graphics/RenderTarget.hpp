#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP
#include "../tools.hpp"
#include "Texture.hpp"

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
		~RenderTarget();

		static void bindScreen();
		void use();
		void attachRenderBuffer(int width, int height, Attachment target,
								Texture::Format bufferFormat);
		void attachTexture(int width, int height,Attachment target,
						   Texture::Format textureFormat, unsigned int slot);
		void addDrawingTarget(Attachment target);
		void noDrawingTargets();
		Texture* getAttachedTexture(Attachment target);
		bool isUsable();

	private:
		class RenderBuffer {
			public:
				RenderBuffer(int width, int height, Texture::Format format);
				~RenderBuffer();

				void bind() const;
				GLuint getHandle() const;
			private:
				GLuint handle;
		};

		void bind();

		static GLuint current;
		GLuint handle;

		std::vector<Attachment> drawAttachments;
		std::map<Attachment,Texture*> textures;
		std::map<Attachment,RenderBuffer*> buffers;
};

#endif // RENDERTARGET_HPP
