#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP

#include <VBE/graphics/RenderTargetBase.hpp>

class RenderTarget : public RenderTargetBase {
    public:
        RenderTarget();
        RenderTarget(unsigned int width, unsigned int height);
        ~RenderTarget();

        void setTexture(RenderTargetBase::Attachment a, Texture2D* tex);
        void setBuffer(RenderTargetBase::Attachment a, RenderBuffer* buff);

        Texture2D* getTexture(RenderTargetBase::Attachment a) const;

        RenderTarget(RenderTarget&& rhs);
        RenderTarget& operator=(RenderTarget&& rhs);
        friend void swap(RenderTarget& a, RenderTarget& b);
};

#endif // RENDERTARGET_HPP
