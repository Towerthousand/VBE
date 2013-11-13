#include "RenderTarget.hpp"

GLuint RenderTarget::current = 0;

RenderTarget::RenderBuffer::RenderBuffer(int width, int height, Texture::Format format) {
	glGenRenderbuffers(1, &handle);
	bind();
	glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
}

RenderTarget::RenderBuffer::~RenderBuffer() {
	glDeleteRenderbuffers(1, &handle);
}

void RenderTarget::RenderBuffer::bind() const {
	glBindRenderbuffer(GL_RENDERBUFFER,handle);
}

GLuint RenderTarget::RenderBuffer::getHandle() const {
	return handle;
}



RenderTarget::RenderTarget() : handle(0) {
}

RenderTarget::~RenderTarget() {
	for(std::map<Attachment,Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
		delete it->second;
	for(std::map<Attachment,RenderBuffer*>::iterator it = buffers.begin(); it != buffers.end(); ++it)
		delete it->second;
	glDeleteFramebuffers(1,&handle);
}

void RenderTarget::bindScreen() {
	if(current == 0) return;
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	current = 0;
}

void RenderTarget::bind() {
	if(current == handle) return;
	glBindFramebuffer(GL_FRAMEBUFFER,handle);
	current = handle;
}

void RenderTarget::use() {
	VBE_ASSERT(isUsable(),"Can't use incomplete RenderTaget");
	bind();
}

void RenderTarget::addRenderBuffer(RenderTarget::Attachment target, Texture::Format format) {
	VBE_ASSERT(entries.find(target) == entries.end(), "There's already an entry with the requested Attachment");
	entries[target] = RenderTargetEntry(RenderTargetEntry::Type::RenderBuffer, target, format);
}

void RenderTarget::addTexture(RenderTarget::Attachment target, Texture::Format format) {
	VBE_ASSERT(entries.find(target) == entries.end(), "There's already an entry with the requested Attachment");
	entries[target] = RenderTargetEntry(RenderTargetEntry::Type::Texture, target, format);
}

void RenderTarget::build() {
	VBE_ASSERT(handle == 0, "This RenderTarget is already built");
	VBE_ASSERT(entries.size() != 0, "This RenderTarget has no textures or render buffers.");

	glGenFramebuffers(1,&handle);
	for(std::map<Attachment, RenderTargetEntry> it = entries.begin(); it != entries.end(); ++it) {
		RenderTargetEntry& e = it->second;

	}
}

void RenderTarget::attachRenderBuffer(int width, int height, Attachment target, Texture::Format bufferFormat) {
	bind();
	RenderBuffer* buff = new RenderBuffer(width,height,bufferFormat);
	buffers.insert(std::pair<Attachment,RenderBuffer*>(target,buff));
	buff->bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, target, GL_RENDERBUFFER, buff->getHandle());
}

void RenderTarget::attachTexture(int width, int height, Attachment target, Texture::Format textureFormat, unsigned int slot) {
	bind();
	Texture* tex = Texture::loadFromRaw(nullptr,width,height,textureFormat,false,slot);
	tex->setFilter(GL_NEAREST,GL_NEAREST);
	textures.insert(std::pair<Attachment,Texture*>(target,tex));
	tex->bind();
	glFramebufferTexture(GL_FRAMEBUFFER, target, tex->getHandle(), 0);
}

void RenderTarget::addDrawingTarget(Attachment target) {
	VBE_ASSERT(target != DEPTH && target != STENCIL && target != DEPTH_STENCIL,
			   "Can only set color attachments as drawing targets");
	VBE_ASSERT(std::find(drawAttachments.begin(),drawAttachments.end(),target) == drawAttachments.end(),
			   "Trying to add an already added attachment to a RenderTarget");

	drawAttachments.push_back(target);
	bind();
	glDrawBuffers(drawAttachments.size(),(GLenum*)&drawAttachments[0]);
}

void RenderTarget::noDrawingTargets() {
	drawAttachments.clear();
	bind();
	GLenum none = GL_NONE;
	glDrawBuffers(1,&none);
}

Texture* RenderTarget::getAttachedTexture(RenderTarget::Attachment target) {
	VBE_ASSERT(textures.find(target) != textures.end(), "Trying to retrieve unexisting texture from FBO");
	return textures.at(target);
}

bool RenderTarget::isUsable() {
	return (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
}
