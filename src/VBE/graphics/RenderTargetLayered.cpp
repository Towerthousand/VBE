#include <VBE/graphics/RenderTargetLayered.hpp>

// Layered targets are not supported in GLES2
#ifndef VBE_GLES2

RenderTargetLayered::RenderTargetLayered(float mult, unsigned int layers) : RenderTargetBase(mult, layers) {
}

RenderTargetLayered::RenderTargetLayered(unsigned int width, unsigned int height, unsigned int layers) : RenderTargetBase(width, height, layers) {
}

RenderTargetLayered::~RenderTargetLayered() {
}

void RenderTargetLayered::setTexture(RenderTargetBase::Attachment a, Texture2DArray* tex) {
	enableAttachment(a);
	if(entries.find(a) != entries.end()) entries.erase(a);
	entries.insert(std::pair<RenderTargetBase::Attachment, RenderTargetEntry>(a, RenderTargetEntry(tex)));
	dirty = true;
}

Texture2DArray* RenderTargetLayered::getTexture(RenderTargetBase::Attachment a) {
	VBE_ASSERT(entries.find(a) != entries.end(), "No texture found for the provided attachment");
	return entries.at(a).texture2DArray;
}

#endif
