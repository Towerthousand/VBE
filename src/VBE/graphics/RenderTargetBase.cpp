#include <VBE/config.hpp>
#include <VBE/graphics/RenderBuffer.cpp>
#include <VBE/graphics/RenderTargetBase.hpp>
#include <VBE/system/Window.hpp>

const RenderTargetBase* RenderTargetBase::current = nullptr;

RenderTargetBase::RenderTargetBase(unsigned int width, unsigned int height) : handle(0), size(width, height), screenRelativeSize(false), screenSizeMultiplier(0.0f), dirty(false), attachDirty(true) {
	VBE_ASSERT(width != 0 && height != 0, "Width or height can't be zero");
	GL_ASSERT(glGenFramebuffers(1, &handle));
}

RenderTargetBase::RenderTargetBase(float mult) : handle(0), screenRelativeSize(true), screenSizeMultiplier(mult), dirty(false), attachDirty(true) {
	GL_ASSERT(glGenFramebuffers(1, &handle));
}

RenderTargetBase::~RenderTargetBase() {
	GL_ASSERT(glDeleteFramebuffers(1, &handle));
	for(RenderTargetEntry& e : entries) {
		if(e.type == RenderTargetEntry::RenderBufferEntry) {
			delete e.renderBuffer;
			e.renderBuffer = nullptr;
		}
	}
	GL_ASSERT(glDeleteFramebuffers(1, &handle));
	handle = 0;
}

vec2ui RenderTargetBase::getSize() const {
	if(screenRelativeSize) {
		vec2ui screenSize = Window::getInstance()->getSize();
		return vec2ui(
			static_cast<unsigned int>(screenSize.x*screenSizeMultiplier),
			static_cast<unsigned int>(screenSize.y*screenSizeMultiplier));
	}
	else
		return size;
}

unsigned int RenderTargetBase::getWidth() const {
	return getSize().x;
}

unsigned int RenderTargetBase::getHeight() const {
	return getSize().y;
}

// static
void RenderTargetBase::bind(const RenderTargetBase *target) {
	if(current == target && (target == nullptr || !target->dirty)) return;
	if(target == nullptr) { //BIND SCREEN FRAMEBUFFER
		vec2ui screenSize = Window::getInstance()->getSize();
		GL_ASSERT(glViewport(0, 0, screenSize.x, screenSize.y));
		GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}
	else {
		GL_ASSERT(glViewport(0, 0, target->size.x, target->size.y));
		GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, target->handle));
		target->valid();
	}
	current = target;
}

const RenderTargetBase* RenderTargetBase::getCurrent() {
	return current;
}

void RenderTargetBase::registerAttachment(RenderTargetBase::Attachment a) {
	dirty = true;
	allAttachments.push_back(a);
	if(isColorAttachment(a)) {
		drawAttachments.push_back(a);
		attachDirty = true;
	}
}

void RenderTargetBase::ensureValid() const {
	const RenderTargetBase* last = current;
	if(last == this) return;
	bind(this);
	bind(last);
}

//void RenderTargetBase::valid() const {
//	VBE_ASSERT(entries.size() != 0, "This RenderTarget is invalid because it has no textures nor render buffers.");
//	vec2ui desiredSize = getSize();
//	bool resize = (desiredSize != size);
//	if(!resize && !dirty) return;

//	for(std::map<Attachment, RenderTargetEntry>::iterator it = entries.begin(); it != entries.end(); ++it) {
//		RenderTargetEntry& e = it->second;
//		if(e.type == RenderTargetEntry::RenderBufferEntry) {
//			if(e.renderBuffer == nullptr) { //make and bind the renderbuffer
//				e.renderBuffer = new RenderBuffer(desiredSize.x, desiredSize.y, e.format);
//				e.renderBuffer->bind();
//				GL_ASSERT(glFramebufferRenderbuffer(GL_FRAMEBUFFER, e.attachment, GL_RENDERBUFFER, e.renderBuffer->getHandle()));
//			}
//			else if(resize)	e.renderBuffer->resize(desiredSize.x, desiredSize.y);
//		}
//		else {
//			if(e.texture == nullptr || !e.userUp) { //make and bind/just bind texture/usertexture
//				if(!e.user) {
//					e.texture = new Texture2D();
//					e.texture->loadEmpty(desiredSize, e.format);
//				}

//				Texture2D::bind(e.texture, 0);
//				GL_ASSERT(glFramebufferTexture2D(GL_FRAMEBUFFER, e.attachment, GL_TEXTURE_2D, e.texture->getHandle(), 0));
//				VBE_WARN(e.texture->getSize() == desiredSize, "While validating RenderTarget:" << Log::Line <<
//						 "Custom texture has a different size from the rendertarget's." << Log::Line <<
//						 "This can yield unexpected results");
//				e.userUp = true;
//			}
//			else if(resize && !e.user)
//				e.texture->loadEmpty(desiredSize, e.texture->getFormat());
//		}
//	}
//	if(attachDirty) {
//#ifndef VBE_GLES2
//		if(drawAttachments.size() == 0) {
//			GLenum none = GL_NONE;
//			GL_ASSERT(glDrawBuffers(1, &none));
//		}
//		else
//			GL_ASSERT(glDrawBuffers(drawAttachments.size(), (GLenum*)&drawAttachments[0]));
//#endif
//		attachDirty = false;
//	}
//	VBE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Can't create framebuffer, incorrect input");
//	size = desiredSize;
//	dirty = false;
//}

//const Texture2D* RenderTargetBase::getTextureForAttachment(RenderTargetBase::Attachment target) const {
//	VBE_ASSERT(entries.find(target) != entries.end(), "Trying to retrieve unexisting texture from RenderTarget");
//	const RenderTargetEntry& e = entries.at(target);
//    VBE_ASSERT(e.type == RenderTargetEntry::TextureEntry, "You can't get a texture for a RenderBuffer attachment");
//	if(dirty) ensureValid();
//	return e.texture;
//}

//Texture2D* RenderTargetBase::getTextureForAttachment(RenderTargetBase::Attachment target) {
//	VBE_ASSERT(entries.find(target) != entries.end(), "Trying to retrieve unexisting texture from RenderTarget");
//	RenderTargetEntry& e = entries.at(target);
//    VBE_ASSERT(e.type == RenderTargetEntry::TextureEntry, "You can't get a texture for a RenderBuffer attachment");
//	if(dirty) ensureValid();
//	return e.texture;
//}
