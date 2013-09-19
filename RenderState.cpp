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

RenderState::RenderInstance RenderState::getCurrent() {
	return RenderInstance(model,view,projection);
}

void RenderState::setState(RenderState::RenderInstance newState) {
	modelStack = std::stack<mat4f>({mat4f(newState.model)});
	model = modelStack.top();
	view = newState.view;
	projection = newState.projection;
}

void RenderState::reset() {
	model = view = projection = mat4f(1.0);
	modelStack = std::stack<mat4f>({mat4f(1.0)});
}
