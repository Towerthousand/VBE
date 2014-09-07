#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP
#include "environment/Environment.hpp"
#include "Texture2D.hpp"

class RenderBuffer;
class RenderTarget : public NonCopyable {
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

        static void bind(const RenderTarget* renderTarget);
        static const RenderTarget *getCurrent();

		int getWidth() const { return (this? size.x : Environment::getScreen()->getWidth());}
		int getHeight() const { return (this? size.y : Environment::getScreen()->getHeight());}
		vec2i getSize() const { return (this? size : vec2i(Environment::getScreen()->getSize()));}
		vec2i getDesiredSize() const {
			if(screenRelativeSize)
				return vec2i(int(Environment::getScreen()->getWidth()*screenSizeMultiplier), int(Environment::getScreen()->getHeight()*screenSizeMultiplier));
			else
				return size;
		}
		void addRenderBuffer(Attachment target, Texture::InternalFormat format);
		void addTexture(Attachment target, Texture::InternalFormat format);
		void addCustomTexture(RenderTarget::Attachment attachment, Texture2D* tex);
		void setCustomTexture(RenderTarget::Attachment attachment, Texture2D* tex);
		Texture2D* getTextureForAttachment(Attachment attachment);
		const Texture2D* getTextureForAttachment(Attachment attachment) const;
        void ensureValid() const;
	private:
        void valid() const;
		struct RenderTargetEntry {
				enum Type {
					RenderBufferEntry,
					TextureEntry
				};

				RenderTargetEntry(Type type, RenderTarget::Attachment attachment, Texture::InternalFormat format) :
					type(type), attachment(attachment), format(format), user(false), userUp(true), texture(nullptr), renderBuffer(nullptr) {}
				RenderTargetEntry(RenderTarget::Attachment attachment, Texture2D* tex) :
					type(TextureEntry), attachment(attachment), format(tex->getFormat()), user(true), userUp(false), texture(tex), renderBuffer(nullptr) {}
				~RenderTargetEntry() {}

				Type type;
				RenderTarget::Attachment attachment;
				Texture::InternalFormat format;
				bool user;
				bool userUp;

				Texture2D* texture;
				RenderBuffer* renderBuffer;
		};

		void registerAttachment(RenderTarget::Attachment a);

        static const RenderTarget* current;

		GLuint handle;
        mutable vec2i size;
		bool screenRelativeSize;
		float screenSizeMultiplier;
        mutable bool dirty;
        mutable bool attachDirty;
		std::vector<Attachment> drawAttachments;
        mutable std::map<Attachment, RenderTargetEntry> entries;
};

#endif // RENDERTARGET_HPP
