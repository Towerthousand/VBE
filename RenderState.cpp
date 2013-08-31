#include "RenderState.hpp"
#include "graphics/ShaderProgram.hpp"

RenderState::RenderState() {
	model = mat4f(1.0);
	view = mat4f(1.0);
	projection = mat4f(1.0);
}

RenderState::~RenderState() {
}
