#include "RenderState.hpp"

RenderState::RenderState() {
	model = mat4f(1.0);
	view = mat4f(1.0);
	projection = mat4f(1.0);
}

RenderState::~RenderState() {
}

void RenderState::initShaderUniforms(const ShaderProgram& shader) {
	//Set up texture handles and texture matrices
	shader.use();
	for (int i = 0; i < MAX_TEXTURES; ++i) {
		std::string uniformID1 = "tex" + toString(i);
		if(shader.getUniLoc(uniformID1) != -1)
			shader.sendUniform1i(uniformID1,i);
		std::string uniformID2 = "texMat" + toString(i);
		if(shader.getUniLoc(uniformID2) != -1)
			shader.sendUniformMat4f(uniformID2,texture[i]);
	}
}

void RenderState::updateShaderUniforms(const ShaderProgram& shader) const { //change model or time depending vars
	shader.use();
	if(shader.getUniLoc("modelViewProjectionMatrix") != -1)
		shader.sendUniformMat4f("modelViewProjectionMatrix",projection*view*model);
}
