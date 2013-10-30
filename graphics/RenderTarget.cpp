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

RenderTarget::RenderTarget() {
	glGenFramebuffers(1,&handle);
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

void RenderTarget::attachRenderBuffer(int width, int height, Attachment target,
									  Texture::Format bufferFormat) {
	bind();
	RenderBuffer* buff = new RenderBuffer(width,height,bufferFormat);
	buffers.insert(std::pair<Attachment,RenderBuffer*>(target,buff));
	buff->bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, target, GL_RENDERBUFFER, buff->getHandle());
}

void RenderTarget::attachTexture(int width, int height, Attachment target,
									  Texture::Format textureFormat, unsigned int slot) {
	bind();
	Texture* tex = new Texture(slot);
	tex->loadRawRGBA8888(NULL,width,height,textureFormat,false);
	tex->setFilter(GL_NEAREST,GL_NEAREST);
	textures.insert(std::pair<Attachment,Texture*>(target,tex));
	tex->bind();
	glFramebufferTexture(GL_FRAMEBUFFER, target, tex->getHandle(), 0);
}

void RenderTarget::addDrawingTarget(Attachment target) {
	bool error = false;
	for(unsigned int i = 0; i < drawAttachments.size(); ++i)
		if(drawAttachments[i] == target) {
			error = true;
			break;
		}
	VBE_ASSERT(!error, "Trying to add an already added attachment to a RenderTarget");
	bind();
	drawAttachments.push_back(target);
	glDrawBuffers(drawAttachments.size(),(GLenum*)&drawAttachments[0]);
	VBE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "FrameBuffer Error");
}

Texture* RenderTarget::getAttachedTexture(RenderTarget::Attachment target) {
	VBE_ASSERT(textures.find(target) != textures.end(), "Trying to retrieve unexisting texture from FBO");
	return textures.at(target);
}
