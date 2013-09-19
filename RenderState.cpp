#include "RenderState.hpp"

mat4f RenderState::s_model(1.0);
mat4f RenderState::s_view(1.0);
mat4f RenderState::s_projection(1.0);
std::stack<mat4f> RenderState::modelStack({mat4f(1.0)});

RenderState::RenderState(){
}
RenderState::~RenderState() {
}

void RenderState::push() {
	modelStack.push(s_model);
}

void RenderState::pop() {
	modelStack.pop();
	s_model = modelStack.top();
}

RenderState::RenderInstance RenderState::getCurrent() {
	return RenderInstance(s_model,s_view,s_projection);
}

void RenderState::setState(RenderState::RenderInstance newState) {
	modelStack = std::stack<mat4f>({mat4f(newState.m_model)});
	s_model = modelStack.top();
	s_view = newState.m_view;
	s_projection = newState.m_projection;
}

void RenderState::reset() {
	s_model = s_view = s_projection = mat4f(1.0);
	modelStack = std::stack<mat4f>({mat4f(1.0)});
}
