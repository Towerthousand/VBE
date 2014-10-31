#include <VBE/config.hpp>
#include <VBE/graphics/RenderBuffer.hpp>
#include <VBE/graphics/RenderTargetBase.hpp>
#include <VBE/system/Window.hpp>
#include <algorithm>

const RenderTargetBase* RenderTargetBase::current = nullptr;

RenderTargetBase::RenderTargetBase(unsigned int width, unsigned int height, int numLayers) : handle(0), size(width, height), screenRelativeSize(false), screenSizeMultiplier(0.0f), dirty(false), numLayers(numLayers) {
	VBE_ASSERT(width != 0 && height != 0, "Width or height can't be zero");
	GL_ASSERT(glGenFramebuffers(1, &handle));
}

RenderTargetBase::RenderTargetBase(float mult, int numLayers) : handle(0), size(0), screenRelativeSize(true), screenSizeMultiplier(mult), dirty(false), numLayers(numLayers) {
	GL_ASSERT(glGenFramebuffers(1, &handle));
}

RenderTargetBase::~RenderTargetBase() {
	GL_ASSERT(glDeleteFramebuffers(1, &handle));
	for(std::pair<const Attachment,RenderTargetEntry>& it  : entries) {
		if(it.second.type == RenderTargetEntry::RenderBufferEntry) {
			delete it.second.renderBuffer;
			it.second.renderBuffer = nullptr;
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

void RenderTargetBase::enableAttachment(RenderTargetBase::Attachment a) {
	VBE_ASSERT(std::find(allAttachments.begin(), allAttachments.end(), a) == allAttachments.end(), "Trying to enable an already enabled rendering attachment");
	dirty = true;
	allAttachments.insert(a);
	if(isColorAttachment(a)) drawAttachments.push_back(a);
}

void RenderTargetBase::disableAttachment(RenderTargetBase::Attachment a) {
	VBE_ASSERT(std::find(allAttachments.begin(), allAttachments.end(), a) != allAttachments.end(), "Trying to disable a non-enabled rendering attachment");
	dirty = true;
	allAttachments.erase(a);
	if(isColorAttachment(a)) drawAttachments.erase(std::find(drawAttachments.begin(), drawAttachments.end(), a));
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

void RenderTargetBase::ensureValid() const {
	const RenderTargetBase* last = current;
	if(last == this) return;
	bind(this);
	bind(last);
}

void RenderTargetBase::valid() const {
	VBE_ASSERT(entries.size() != 0, "This RenderTarget is invalid because it has no textures nor render buffers.");
	VBE_ASSERT(entries.size() == allAttachments.size(), "This RenderTarget is invalid because it has no texture/renderbuffer for at least one of it's enabled attachments");
	vec2ui desiredSize = getSize();

	//Check size of all textures, resize if needed and check for entry consistency.
	for(std::pair<const Attachment, RenderTargetEntry>& it : entries) {
		RenderTargetEntry& e = it.second;
		switch(e.type) {
			case RenderTargetEntry::RenderBufferEntry:
				VBE_ASSERT(numLayers == 1, "RenderBuffer attached to a RenderTarget with several layers");
				if(e.renderBuffer->getSize() != desiredSize)	e.renderBuffer->resize(desiredSize);
				break;
			case RenderTargetEntry::Texture2DEntry:
				VBE_ASSERT(numLayers == 1, "Texture2D attached with a RenderTarget with several layers");
				if(e.texture2D->getSize() != desiredSize) e.texture2D->loadEmpty(desiredSize, e.texture2D->getFormat());
				break;
			case RenderTargetEntry::Texture2DArrayEntry:
				VBE_ASSERT(e.texture2DArray->getSize().z == numLayers, "A Texture2DArray attached to this RenderTarget does not have the same layers as the RenderTarget");
				if(vec2ui(e.texture2DArray->getSize()) != desiredSize) e.texture2DArray->loadEmpty(vec3ui(desiredSize, numLayers), e.texture2DArray->getFormat());
				break;
		}
	}
	size = desiredSize;

	if(!dirty) return;

	//Rebind all textures
	for(std::pair<const Attachment, RenderTargetEntry>& it : entries) {
		RenderTargetEntry& e = it.second;
		Attachment a = it.first;
		switch(e.type) {
			case RenderTargetEntry::RenderBufferEntry:
				e.renderBuffer->bind();
				GL_ASSERT(glFramebufferRenderbuffer(GL_FRAMEBUFFER, a, GL_RENDERBUFFER, e.renderBuffer->getHandle()));
				break;
			case RenderTargetEntry::Texture2DEntry:
				Texture2D::bind(e.texture2D, 0);
				GL_ASSERT(glFramebufferTexture(GL_FRAMEBUFFER, a, e.texture2D->getHandle(), 0));
				break;
			case RenderTargetEntry::Texture2DArrayEntry:
				Texture2DArray::bind(e.texture2DArray, 0);
				GL_ASSERT(glFramebufferTexture(GL_FRAMEBUFFER, a, e.texture2DArray->getHandle(), 0));
				break;
		}
	}
	dirty = false;

#ifndef VBE_GLES2
	//Submit draw buffers
	if(drawAttachments.size() == 0) {
		GLenum none = GL_NONE;
		GL_ASSERT(glDrawBuffers(1, &none));
	}
	else GL_ASSERT(glDrawBuffers(drawAttachments.size(), (GLenum*)&drawAttachments[0]));
#endif

	VBE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Can't create framebuffer, incorrect input");
}
