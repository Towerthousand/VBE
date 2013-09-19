#ifndef RENDERSTATE_HPP
#define RENDERSTATE_HPP
#include "tools.hpp"

class RenderState {
	public:
		struct RenderInstance {
				RenderInstance(const mat4f& model, const mat4f& view, const mat4f& projection)
					: model(model), view(view), projection(projection) {}
				~RenderInstance() {}
				mat4f model, view, projection;
		};

		static mat4f model, view, projection;
		static void push();
		static void pop();
		static RenderInstance getCurrent();
		static void setState(RenderInstance newState);
		static void reset();
	private:
		static std::stack<mat4f> modelStack;
		RenderState();
		~RenderState();
};


#endif // RENDERSTATE_HPP
