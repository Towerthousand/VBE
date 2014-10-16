#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP

#include <vector>
#include <map>

#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/Texture2D.hpp>
#include <VBE/math.hpp>
#include <VBE/utils/NonCopyable.hpp>

class RenderBuffer;
class RenderTarget : public NonCopyable {
	public:
		enum Attachment {
			DEPTH = GL_DEPTH_ATTACHMENT,
			STENCIL = GL_STENCIL_ATTACHMENT,
			COLOR0 = GL_COLOR_ATTACHMENT0,
#ifndef VBE_GLES2
			DEPTH_STENCIL = GL_DEPTH_STENCIL_ATTACHMENT,
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
#endif
		};

		inline bool isColorAttachment(Attachment a) {
#ifdef VBE_GLES2
			return a == COLOR0;
#else
			return a >= COLOR0 && a <= COLOR15;
#endif
		}

		RenderTarget(unsigned int width, unsigned int height);
		RenderTarget(float mult);
		~RenderTarget();
		
		static void bind(const RenderTarget* renderTarget);
		static const RenderTarget *getCurrent();

		unsigned int getWidth() const;
		unsigned int getHeight() const;
		vec2ui getSize() const;

		// TODO 
		void addRenderBuffer(Attachment target, TextureFormat::Format format);
		void addTexture(Attachment target, TextureFormat::Format format);
		void addCustomTexture(RenderTarget::Attachment attachment, Texture2D* tex);
		void setCustomTexture(RenderTarget::Attachment attachment, Texture2D* tex);
		Texture2D* getTextureForAttachment(Attachment attachment);
		const Texture2D* getTextureForAttachment(Attachment attachment) const;
	private:
		void ensureValid() const;
		void valid() const;
		struct RenderTargetEntry {
				enum Type {
					RenderBufferEntry,
					TextureEntry
				};

				RenderTargetEntry(Type type, RenderTarget::Attachment attachment, TextureFormat::Format format) :
					type(type), attachment(attachment), format(format), user(false), userUp(true), texture(nullptr), renderBuffer(nullptr) {}
				RenderTargetEntry(RenderTarget::Attachment attachment, Texture2D* tex) :
					type(TextureEntry), attachment(attachment), format(tex->getFormat()), user(true), userUp(false), texture(tex), renderBuffer(nullptr) {}
				~RenderTargetEntry() {}

				Type type;
				RenderTarget::Attachment attachment;
				TextureFormat::Format format;
				bool user;
				bool userUp;

				Texture2D* texture;
				RenderBuffer* renderBuffer;
		};

		void registerAttachment(RenderTarget::Attachment a);

		static const RenderTarget* current;

		GLuint handle;
		mutable vec2ui size;
		bool screenRelativeSize;
		float screenSizeMultiplier;
		mutable bool dirty;
		mutable bool attachDirty;
		std::vector<Attachment> drawAttachments;
		mutable std::map<Attachment, RenderTargetEntry> entries;
};


#endif // RENDERTARGET_HPP
