#ifndef RENDERSTATE_HPP
#define RENDERSTATE_HPP
#include "tools.hpp"

class RenderState {
	public:
		static mat4f model;
		static mat4f view;
		static mat4f projection;
	private:
		RenderState();
		~RenderState();
};


#endif // RENDERSTATE_HPP
