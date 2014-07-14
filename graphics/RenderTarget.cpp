#include "RenderTarget.hpp"
#include "RenderBuffer.hpp"

RenderTarget* RenderTarget::current = nullptr;

RenderTarget::RenderTarget(int width, int height) : handle(0), size(width, height), screenRelativeSize(false), screenSizeMultiplier(0.0f), dirty(false), attachDirty(true) {
	VBE_ASSERT(width != 0 && height != 0, "Width or height can't be zero");
	GL_ASSERT(glGenFramebuffers(1, &handle));
}

RenderTarget::RenderTarget(float mult) : handle(0), size(int(Environment::getScreen()->getWidth()*mult), int(Environment::getScreen()->getHeight()*mult)), screenRelativeSize(true), screenSizeMultiplier(mult), dirty(false), attachDirty(true) {
	GL_ASSERT(glGenFramebuffers(1, &handle));
}

RenderTarget::RenderTarget() : handle(0), size(int(Environment::getScreen()->getWidth()), int(Environment::getScreen()->getHeight())), screenRelativeSize(true), screenSizeMultiplier(1), dirty(false), attachDirty(true) {
	GL_ASSERT(glGenFramebuffers(1, &handle));
}

RenderTarget::~RenderTarget() {
	GL_ASSERT(glDeleteFramebuffers(1, &handle));
	for(std::map<Attachment, RenderTargetEntry>::iterator it = entries.begin(); it != entries.end(); ++it) {
		RenderTargetEntry& e = it->second;
		if(e.user) continue;
		else if(e.type == RenderTargetEntry::RenderBufferEntry) {
			delete e.renderBuffer;
			e.renderBuffer = nullptr;
		}
		else {
			delete e.texture;
			e.texture = nullptr;
		}
	}
	GL_ASSERT(glDeleteFramebuffers(1, &handle));
	handle = 0;
}

void RenderTarget::bind(RenderTarget* target) {
	if(current == target && (target == nullptr || !target->dirty)) return;
	if(target == nullptr) { //BIND SCREEN FRAMEBUFFER
		GL_ASSERT(glViewport(0, 0, Environment::getScreen()->getWidth(), Environment::getScreen()->getHeight()));
		GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}
	else {
		GL_ASSERT(glViewport(0, 0, target->size.x, target->size.y));
		GL_ASSERT(glBindFramebuffer(GL_FRAMEBUFFER, target->handle));
		target->valid();
	}
	current = target;
}

RenderTarget* RenderTarget::getCurrent() {
	return current;
}

void RenderTarget::registerAttachment(RenderTarget::Attachment a) {
	dirty = true;
	if(a >= COLOR0 && a <= COLOR15) {
		drawAttachments.push_back(a);
		attachDirty = true;
	}
}

void RenderTarget::addRenderBuffer(RenderTarget::Attachment attachment, Texture::InternalFormat format) {
	VBE_ASSERT(entries.find(attachment) == entries.end(), "There's already an entry with the requested Attachment");
	entries.insert(std::pair<Attachment, RenderTargetEntry> (attachment, RenderTargetEntry(RenderTargetEntry::RenderBufferEntry, attachment, format)));
	registerAttachment(attachment);
    if(this == current) valid();
}

void RenderTarget::addTexture(RenderTarget::Attachment attachment, Texture::InternalFormat format) {
	VBE_ASSERT(entries.find(attachment) == entries.end(), "There's already an entry with the requested Attachment");
	entries.insert(std::pair<Attachment, RenderTargetEntry> (attachment, RenderTargetEntry(RenderTargetEntry::TextureEntry, attachment, format)));
	registerAttachment(attachment);
    if(this == current) valid();
}

void RenderTarget::addCustomTexture(RenderTarget::Attachment attachment, Texture2D* tex) {
	VBE_ASSERT(entries.find(attachment) == entries.end(), "There's already an entry with the requested Attachment");
	entries.insert(std::pair<Attachment, RenderTargetEntry> (attachment, RenderTargetEntry(attachment, tex)));
	registerAttachment(attachment);
    if(this == current) valid();
}

void RenderTarget::setCustomTexture(RenderTarget::Attachment attachment, Texture2D* tex) {
	VBE_ASSERT(entries.find(attachment) != entries.end(), "There's no entry with the requested Attachment");
	RenderTargetEntry& e = entries.at(attachment);
	VBE_ASSERT(e.type == RenderTargetEntry::TextureEntry, "Cannot set the texture of a RenderBuffer entry.");
	VBE_ASSERT(e.user, "Cannot set the texture of a non user-managed Texture entry.");
	e.texture = tex;
	e.userUp = false;
	dirty = true;
    if(this == current) valid();
}

void RenderTarget::valid() {
	VBE_ASSERT(entries.size() != 0, "This RenderTarget is invalid because it has no textures nor render buffers.");
	vec2i desiredSize = getDesiredSize();
	bool resize = (desiredSize == size);
	if(!resize && !dirty) return;

	for(std::map<Attachment, RenderTargetEntry>::iterator it = entries.begin(); it != entries.end(); ++it) {
		RenderTargetEntry& e = it->second;
		if(e.type == RenderTargetEntry::RenderBufferEntry) {
			if(e.renderBuffer == nullptr) { //make and bind the renderbuffer
				e.renderBuffer = new RenderBuffer(desiredSize.x, desiredSize.y, e.format);
				e.renderBuffer->bind();
				GL_ASSERT(glFramebufferRenderbuffer(GL_FRAMEBUFFER, e.attachment, GL_RENDERBUFFER, e.renderBuffer->getHandle()));
			}
			else if(resize)	e.renderBuffer->resize(desiredSize.x, desiredSize.y);
		}
		else {
			if(e.texture == nullptr || !e.userUp) { //make and bind/just bind texture/usertexture
				e.texture = (e.user ? e.texture : Texture2D::createEmpty(desiredSize.x, desiredSize.y, e.format));
				e.texture->bind();
				GL_ASSERT(glFramebufferTexture(GL_FRAMEBUFFER, e.attachment, e.texture->getHandle(), 0));
				VBE_WARN(e.texture->getSize() == desiredSize, "While validating RenderTarget:" << Log::Line <<
						 "Custom texture has a different size from the rendertarget's." << Log::Line <<
						 "This can yield unexpected results");
				e.userUp = true;
			}
			else if(resize && !e.user) e.texture->resize(desiredSize.x, desiredSize.y);
		}
	}
	if(attachDirty) {
		if(drawAttachments.size() == 0) {
			GLenum none = GL_NONE;
			GL_ASSERT(glDrawBuffers(1, &none));
		}
		else
			GL_ASSERT(glDrawBuffers(drawAttachments.size(), (GLenum*)&drawAttachments[0]));
		attachDirty = false;
	}
	VBE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Can't create framebuffer, incorrect input");
	size = desiredSize;
	dirty = false;
}

const Texture2D* RenderTarget::getTextureForAttachment(RenderTarget::Attachment target) const {
	VBE_ASSERT(handle != 0, "Can't get texture for attachment without building it first");
	VBE_ASSERT(entries.find(target) != entries.end(), "Trying to retrieve unexisting texture from RenderTarget");
	const RenderTargetEntry& e = entries.at(target);
	VBE_ASSERT(e.type == RenderTargetEntry::TextureEntry, "You can't get a texture for a RenderBuffer attachment");
	return e.texture;
}

void RenderTarget::ensureValid() {
	RenderTarget* last = current;
	if(last == this) return;
	bind(this);
	bind(last);
}

Texture2D* RenderTarget::getTextureForAttachment(RenderTarget::Attachment target) {
	VBE_ASSERT(handle != 0, "Can't get texture for attachment without building it first");
	VBE_ASSERT(entries.find(target) != entries.end(), "Trying to retrieve unexisting texture from RenderTarget");
	RenderTargetEntry& e = entries.at(target);
	VBE_ASSERT(e.type == RenderTargetEntry::TextureEntry, "You can't get a texture for a RenderBuffer attachment");
	return e.texture;
}
