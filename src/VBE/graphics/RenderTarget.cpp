#include <VBE/config.hpp>
#include <VBE/graphics/RenderBuffer.hpp>
#include <VBE/graphics/RenderTarget.hpp>

RenderTarget::RenderTarget() : RenderTargetBase(0, 0, 1) {
}

RenderTarget::RenderTarget(unsigned int width, unsigned int height) : RenderTargetBase(width, height, 1) {
}

RenderTarget::~RenderTarget() {
}

void RenderTarget::setTexture(RenderTargetBase::Attachment a, Texture2D* tex) {
    VBE_ASSERT(tex->getSize() == getSize(), "Incorrect size for Texture2D");
    enableAttachment(a);
    if(entries.find(a) != entries.end()) entries.erase(a);
    entries.insert(std::pair<RenderTargetBase::Attachment, RenderTargetEntry>(a, RenderTargetEntry(tex)));
    dirty = true;
}

void RenderTarget::setBuffer(RenderTargetBase::Attachment a, RenderBuffer* buff) {
    VBE_ASSERT(buff->getSize() == getSize(), "Incorrect size for RenderBuffer");
    enableAttachment(a);
    if(entries.find(a) != entries.end()) entries.erase(a);
    entries.insert(std::pair<RenderTargetBase::Attachment, RenderTargetEntry>(a, RenderTargetEntry(buff)));
    dirty = true;
}

Texture2D* RenderTarget::getTexture(RenderTargetBase::Attachment a) const {
    VBE_ASSERT(entries.find(a) != entries.end(), "No texture found for the provided attachment");
    VBE_ASSERT(entries.at(a).type == RenderTargetEntry::Texture2DEntry, "This attachment has a renderbuffer, not a texture");
    return entries.at(a).texture2D;
}

RenderTarget::RenderTarget(RenderTarget&& rhs) : RenderTarget() {
    using std::swap;
    swap(*this, rhs);
}

RenderTarget& RenderTarget::operator=(RenderTarget&& rhs) {
    using std::swap;
    swap(*this, rhs);
    return *this;
}

void swap(RenderTarget& a, RenderTarget& b) {
    using std::swap;
    swap(static_cast<RenderTargetBase&>(a), static_cast<RenderTargetBase&>(b));
}
