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



RenderTarget::RenderTarget(int width, int height) : handle(0), width(width), height(height) {
}

RenderTarget::~RenderTarget() {
	if(handle != 0)
		destroy();
}

void RenderTarget::bind(RenderTarget* target) {
	GLuint handle = 0;
	if(target != nullptr) {
		VBE_ASSERT(target->handle != 0, "This RenderTarget not yet built");
		handle = target->handle;
	}

	if(current == handle) return;
	glBindFramebuffer(GL_FRAMEBUFFER, handle);
	current = handle;
}

void RenderTarget::setSize(int width, int height) {
	VBE_ASSERT(handle == 0, "This RenderTarget is already built");
	this->width = width;
	this->height = height;
}

void RenderTarget::addRenderBuffer(RenderTarget::Attachment attachment, Texture::Format format) {
	VBE_ASSERT(handle == 0, "This RenderTarget is already built");
	VBE_ASSERT(entries.find(attachment) == entries.end(), "There's already an entry with the requested Attachment");
	entries.insert(std::pair<Attachment, RenderTargetEntry> (attachment, RenderTargetEntry(RenderTargetEntry::RenderBufferEntry, attachment, format)));
}

void RenderTarget::addTexture(RenderTarget::Attachment attachment, Texture::Format format) {
	VBE_ASSERT(handle == 0, "This RenderTarget is already built");
	VBE_ASSERT(entries.find(attachment) == entries.end(), "There's already an entry with the requested Attachment");
	entries.insert(std::pair<Attachment, RenderTargetEntry> (attachment, RenderTargetEntry(RenderTargetEntry::TextureEntry, attachment, format)));
}

void RenderTarget::build() {
	VBE_ASSERT(handle == 0, "This RenderTarget is already built");
	VBE_ASSERT(entries.size() != 0, "This RenderTarget has no textures or render buffers.");

	glGenFramebuffers(1,&handle);
	bind(this);//please

	std::vector<Attachment> drawAttachments;

	for(std::map<Attachment, RenderTargetEntry>::iterator it = entries.begin(); it != entries.end(); ++it) {
		RenderTargetEntry& e = it->second;

		if(e.type == RenderTargetEntry::RenderBufferEntry) {
			RenderBuffer* buff = new RenderBuffer(width, height, e.format);
			buff->bind();
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, e.attachment, GL_RENDERBUFFER, buff->getHandle());
			e.renderBuffer = buff;
		}
		else {
			Texture* tex = Texture::loadFromRaw(nullptr, width, height, e.format);
			tex->bind();
			glFramebufferTexture(GL_FRAMEBUFFER, e.attachment, tex->getHandle(), 0);
			e.texture = tex;
		}

		if(e.attachment >= COLOR0 && e.attachment <= COLOR15)
			drawAttachments.push_back(e.attachment);
	}

	if(drawAttachments.size() == 0) {
		GLenum none = GL_NONE;
		glDrawBuffers(1,&none);
	}
	else
		glDrawBuffers(drawAttachments.size(),(GLenum*)&drawAttachments[0]);

	VBE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Can't create framebuffer");
}

void RenderTarget::destroy() {
	VBE_ASSERT(handle != 0, "Can't destroy a not built RenderTarget");

	for(std::map<Attachment, RenderTargetEntry>::iterator it = entries.begin(); it != entries.end(); ++it) {
		RenderTargetEntry& e = it->second;

		if(e.type == RenderTargetEntry::RenderBufferEntry) {
			VBE_ASSERT(e.renderBuffer != nullptr, "this should never happen. wat do?");
			delete e.renderBuffer;
			e.renderBuffer = nullptr;
		}
		else {
			VBE_ASSERT(e.texture != nullptr, "this should never happen. wat do?");
			delete e.texture;
			e.texture = nullptr;
		}
	}

	glDeleteFramebuffers(1, &handle);
}

Texture* RenderTarget::getTextureForAttachment(RenderTarget::Attachment target) {
	VBE_ASSERT(handle != 0, "This RenderTarget not yet built");
	VBE_ASSERT(entries.find(target) != entries.end(), "Trying to retrieve unexisting texture from RenderTarget");
	RenderTargetEntry& e = entries.at(target);
	VBE_ASSERT(e.type == RenderTargetEntry::TextureEntry, "You can't get a texture for a RenderBuffer attachment");
	return e.texture;
}
