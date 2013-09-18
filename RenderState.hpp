#ifndef RENDERSTATE_HPP
#define RENDERSTATE_HPP
#include "tools.hpp"

class RenderState {
	public:
		struct RenderInstance {
				RenderInstance() : model(1.0), view(1.0), projection(1.0) {}
				~RenderInstance() {}
				mat4f model, view, projection;
		};

		static mat4f model, view, projection;
		static void push();
		static void pop();
	private:
		static std::stack<mat4f> modelStack;
		RenderState();
		~RenderState();
};


#endif // RENDERSTATE_HPP
