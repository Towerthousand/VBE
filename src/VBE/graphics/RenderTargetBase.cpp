#include <VBE/config.hpp>
#include <VBE/graphics/RenderBuffer.hpp>
#include <VBE/graphics/RenderTargetBase.hpp>
#include <VBE/system/Window.hpp>
#include <algorithm>

const RenderTargetBase* RenderTargetBase::current = nullptr;

RenderTargetBase::RenderTargetBase(unsigned int width, unsigned int height, unsigned int numLayers) : size(width, height), numLayers(numLayers) {
    GL_ASSERT(glGenFramebuffers(1, &handle));
}

RenderTargetBase::~RenderTargetBase() {
    GL_ASSERT(glDeleteFramebuffers(1, &handle));
    handle = 0;
}

void swap(RenderTargetBase& a, RenderTargetBase& b) {
    using std::swap;

    //TODO: Fix this with handles!
    RenderTargetBase::bind(nullptr); //'current' pointer might become invalidated otherwise

    swap(a.handle, b.handle);
    swap(a.size, b.size);
    swap(a.dirty, b.dirty);
    swap(a.numLayers, b.numLayers);
    swap(a.drawAttachments, b.drawAttachments);
    swap(a.allAttachments, b.allAttachments);
    swap(a.entries, b.entries);
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

vec2ui RenderTargetBase::getSize() const {
    return size;
}

unsigned int RenderTargetBase::getNumLayers() const {
    return numLayers;
}

void RenderTargetBase::ensureValid() const {
    const RenderTargetBase* last = current;
    if(last == this) return;
    bind(this);
    bind(last);
}

void RenderTargetBase::valid() const {
    VBE_ASSERT(size.x != 0 && size.y != 0, "Width or height can't be zero");
    VBE_ASSERT(entries.size() != 0, "This RenderTarget is invalid because it has no textures nor render buffers.");
    VBE_ASSERT(entries.size() == allAttachments.size(), "This RenderTarget is invalid because it has no texture/renderbuffer for at least one of it's enabled attachments");

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
                Texture2D::bind(e.texture2D, rand()%10); //wow, such determinism
                GL_ASSERT(glFramebufferTexture2D(GL_FRAMEBUFFER, a, GL_TEXTURE_2D, e.texture2D->getHandle(), 0));
                break;
#ifndef VBE_GLES2
            case RenderTargetEntry::Texture2DArrayEntry:
                Texture2DArray::bind(e.texture2DArray, 0);
                GL_ASSERT(glFramebufferTexture(GL_FRAMEBUFFER, a, e.texture2DArray->getHandle(), 0));
                break;
#endif
        }
    }
    dirty = false;

#ifndef VBE_GLES2
    //Submit draw buffers
    if(drawAttachments.size() == 0) {
        GLenum none = GL_NONE;
        GL_ASSERT(glDrawBuffers(1, &none));
    }
    else {
        GL_ASSERT(glDrawBuffers(drawAttachments.size(), (GLenum*)&drawAttachments[0]));
    }
#endif
    GLenum ret = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    (void)ret;
    VBE_ASSERT(ret == GL_FRAMEBUFFER_COMPLETE, "Can't create framebuffer, incorrect input");
}

void RenderTargetBase::enableAttachment(RenderTargetBase::Attachment a) {
    if(std::find(allAttachments.begin(), allAttachments.end(), a) != allAttachments.end())
        return;
    dirty = true;
    allAttachments.insert(a);
    if(isColorAttachment(a)) drawAttachments.push_back(a);
}

void RenderTargetBase::disableAttachment(RenderTargetBase::Attachment a) {
    if(std::find(allAttachments.begin(), allAttachments.end(), a) == allAttachments.end())
        return;
    dirty = true;
    allAttachments.erase(a);
    if(isColorAttachment(a)) drawAttachments.erase(std::find(drawAttachments.begin(), drawAttachments.end(), a));
}
