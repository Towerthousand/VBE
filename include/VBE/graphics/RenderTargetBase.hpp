#ifndef RENDERTARGETBASE_HPP
#define RENDERTARGETBASE_HPP

#include <vector>
#include <map>

#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/Texture2D.hpp>
#include <VBE/math.hpp>
#include <VBE/utils/NonCopyable.hpp>

class RenderBuffer;
class RenderTargetBase : public NonCopyable {
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

		RenderTargetBase(unsigned int width, unsigned int height);
		RenderTargetBase(float mult);
		virtual ~RenderTargetBase();
		
		static void bind(const RenderTargetBase* renderTarget);
		static const RenderTargetBase* getCurrent();

		unsigned int getWidth() const;
		unsigned int getHeight() const;
		vec2ui getSize() const;

		void addDrawAttachment(RenderTargetBase::Attachment a);
	protected:
		void ensureValid() const;
		void valid() const = 0; //validate this framebuffer pls
		struct RenderTargetEntry {
				enum Type {
					RenderBufferEntry,
					TextureEntry
				};

				RenderTargetEntry(Texture* texture, RenderTargetBase::Attachment attachment) :
					type(TextureEntry), attachment(attachment), texture(texture), renderBuffer(nullptr) {}
				RenderTargetEntry(RenderTargetBase::Attachment attachment, RenderBuffer* renderBuffer) :
					type(RenderBufferEntry), attachment(attachment), texture(nullptr), renderBuffer(renderBuffer) {}
				~RenderTargetEntry() {}

				Type type;
				RenderTargetBase::Attachment attachment;
				Texture2D* texture;
				RenderBuffer* renderBuffer;
		};

		void registerAttachment(RenderTargetBase::Attachment a);

		static const RenderTargetBase* current;

		GLuint handle;
		mutable vec2ui size;
		bool screenRelativeSize;
		float screenSizeMultiplier;
		mutable bool dirty;
		mutable bool attachDirty;
		std::vector<Attachment> drawAttachments;
		std::vector<Attachment> allAttachments;
		mutable std::vector<RenderTargetEntry> entries;
};


#endif // RENDERTARGETBASE_HPP
