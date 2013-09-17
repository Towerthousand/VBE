#include "RenderState.hpp"

mat4f RenderState::model(1.0);
mat4f RenderState::view(1.0);
mat4f RenderState::projection(1.0);
std::stack<mat4f> RenderState::modelStack({mat4f(1.0)});

RenderState::RenderState(){
}
RenderState::~RenderState() {
}

void RenderState::push() {
	modelStack.push(model);
}

void RenderState::pop() {
	modelStack.pop();
	model = modelStack.top();
}
