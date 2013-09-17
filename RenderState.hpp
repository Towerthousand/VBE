#ifndef RENDERSTATE_HPP
#define RENDERSTATE_HPP
#include "tools.hpp"

class RenderState {
	public:
		static mat4f model;
		static mat4f view;
		static mat4f projection;
		static void push();
		static void pop();
	private:
		static std::stack<mat4f> modelStack;
		RenderState();
		~RenderState();
};


#endif // RENDERSTATE_HPP
