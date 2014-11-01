#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP

#include <VBE/graphics/RenderTargetBase.hpp>

class RenderTarget : public RenderTargetBase {
	public:
		RenderTarget(unsigned int width, unsigned int height);
		RenderTarget(float mult);
		~RenderTarget();

		void setTexture(RenderTargetBase::Attachment a, Texture2D* tex);
		void setBuffer(RenderTargetBase::Attachment a, RenderBuffer* buff);

		Texture2D* getTexture(RenderTargetBase::Attachment a);
};

#endif // RENDERTARGET_HPP
