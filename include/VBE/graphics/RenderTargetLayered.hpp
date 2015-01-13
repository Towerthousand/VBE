#ifndef RENDERTARGETLAYERED_HPP
#define RENDERTARGETLAYERED_HPP

#include <VBE/graphics/RenderTargetBase.hpp>

// Layered targets are not supported in GLES2
#ifndef VBE_GLES2

class RenderTargetLayered : public RenderTargetBase {
	public:
		RenderTargetLayered(unsigned int width, unsigned int height, unsigned int layers);
		~RenderTargetLayered();

		void setTexture(RenderTargetBase::Attachment a, Texture2DArray* tex);
		Texture2DArray* getTexture(RenderTargetBase::Attachment a);
};

#endif //VBE_GLES2

#endif // RENDERTARGETLAYERED_HPP
