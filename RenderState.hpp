#ifndef RENDERSTATE_H
#define RENDERSTATE_H
#include "tools.hpp"

class RenderState {
	public:
		RenderState();
		~RenderState();

		mat4f model;
		mat4f view;
		mat4f projection;
};

#endif // RENDERSTATE_H
