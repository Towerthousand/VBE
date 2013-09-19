#ifndef RENDERSTATE_HPP
#define RENDERSTATE_HPP
#include "tools.hpp"

class RenderState {
	public:
		struct RenderInstance {
				RenderInstance(const mat4f& model, const mat4f& view, const mat4f& projection)
					: m_model(model), m_view(view), m_projection(projection) {}
				~RenderInstance() {}
				mat4f m_model, m_view, m_projection;
		};

		static mat4f s_model, s_view, s_projection;
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
