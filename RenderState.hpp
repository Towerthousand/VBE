#ifndef RENDERSTATE_H
#define RENDERSTATE_H
#include "graphics/ShaderProgram.hpp"

class RenderState
{
	public:
		RenderState();
		~RenderState();

		void initShaderUniforms(const ShaderProgram& shader);
		void updateShaderUniforms(const ShaderProgram& shader) const;

		mat4f texture[MAX_TEXTURES];//GL_MAX_TEXTURE_UNITS = 8 by default
		mat4f model;
		mat4f view;
		mat4f projection;
};

#endif // RENDERSTATE_H
