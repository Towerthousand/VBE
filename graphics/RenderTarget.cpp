#include "RenderTarget.hpp"

GLuint RenderTarget::current = 0;

RenderTarget::RenderBuffer::RenderBuffer(int width, int height, Texture::InternalFormat format) {
	glGenRenderbuffers(1, &handle);
	bind();
	glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
}

RenderTarget::RenderBuffer::~RenderBuffer() {
	glDeleteRenderbuffers(1, &handle);
}

void RenderTarget::RenderBuffer::bind() const {
	glBindRenderbuffer(GL_RENDERBUFFER, handle);
}

GLuint RenderTarget::RenderBuffer::getHandle() const {
	return handle;
}

RenderTarget::RenderTarget(int width, int height) : handle(0), width(width), height(height) {
	VBE_ASSERT(width != 0 && height != 0, "Invalid dimensions for RenderTarget (height:" << height << " width:" << width);
}

RenderTarget::~RenderTarget() {
	if(handle != 0)
		destroy();
}

void RenderTarget::bind(RenderTarget* target) {
	GLuint handle = (target == nullptr)? 0 : target->handle;
	VBE_ASSERT(target == nullptr || handle != 0, "Cannot bind unbuilt RenderTarget");
	if(current == handle) return;
	glBindFramebuffer(GL_FRAMEBUFFER, handle);
	if(handle != 0)
		glViewport(0, 0, target->width, target->height);
	else glViewport(0, 0, SCRWIDTH, SCRHEIGHT);
	current = handle;
}

void RenderTarget::setSize(int width, int height) {
	VBE_ASSERT(handle == 0, "Cannot set size of already built RenderTarget. Call RenderTarget::destroy() first or add before building");
	VBE_ASSERT(width != 0 && height != 0, "Invalid dimensions for RenderTarget (height:" << height << " width:" << width);
	this->width = width;
	this->height = height;
}

void RenderTarget::addRenderBuffer(RenderTarget::Attachment attachment, Texture::InternalFormat format) {
	VBE_ASSERT(handle == 0, "Cannot add RenderBuffer to already built RenderTarget. Call RenderTarget::destroy() first or add before building");
	VBE_ASSERT(entries.find(attachment) == entries.end(), "There's already an entry with the requested Attachment");
	entries.insert(std::pair<Attachment, RenderTargetEntry> (attachment, RenderTargetEntry(RenderTargetEntry::RenderBufferEntry, attachment, format)));
}

void RenderTarget::addTexture(RenderTarget::Attachment attachment, Texture::InternalFormat format) {
	VBE_ASSERT(handle == 0, "Cannot add texture to already built RenderTarget. Call RenderTarget::destroy() first or add before building");
	VBE_ASSERT(entries.find(attachment) == entries.end(), "There's already an entry with the requested Attachment");
	entries.insert(std::pair<Attachment, RenderTargetEntry> (attachment, RenderTargetEntry(RenderTargetEntry::TextureEntry, attachment, format)));
}

void RenderTarget::build() {
	VBE_ASSERT(handle == 0, "Cannot rebuild already built RenderTarget. Call RenderTarget::destroy() first");
	VBE_ASSERT(entries.size() != 0, "This RenderTarget has no textures or render buffers.");

	glGenFramebuffers(1, &handle);
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
			Texture* tex = Texture::loadEmpty(width, height, e.format);
			tex->bind();
			glFramebufferTexture(GL_FRAMEBUFFER, e.attachment, tex->getHandle(), 0);
			e.texture = tex;
		}

		if(e.attachment >= COLOR0 && e.attachment <= COLOR15)
			drawAttachments.push_back(e.attachment);
	}

	if(drawAttachments.size() == 0) {
		GLenum none = GL_NONE;
		glDrawBuffers(1, &none);
	}
	else
		glDrawBuffers(drawAttachments.size(), (GLenum*)&drawAttachments[0]);

	VBE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Can't create framebuffer");
}

void RenderTarget::destroy() {
	VBE_ASSERT(handle != 0, "Can't destroy an unbuilt RenderTarget");

	for(std::map<Attachment, RenderTargetEntry>::iterator it = entries.begin(); it != entries.end(); ++it) {
		RenderTargetEntry& e = it->second;

		if(e.type == RenderTargetEntry::RenderBufferEntry) {
			delete e.renderBuffer;
			e.renderBuffer = nullptr;
		}
		else {
			delete e.texture;
			e.texture = nullptr;
		}
	}

	glDeleteFramebuffers(1, &handle);
}

Texture* RenderTarget::getTextureForAttachment(RenderTarget::Attachment target) {
	VBE_ASSERT(handle != 0, "Can't get texture for attachment without building it first");
	VBE_ASSERT(entries.find(target) != entries.end(), "Trying to retrieve unexisting texture from RenderTarget");
	RenderTargetEntry& e = entries.at(target);
	VBE_ASSERT(e.type == RenderTargetEntry::TextureEntry, "You can't get a texture for a RenderBuffer attachment");
	return e.texture;
}
