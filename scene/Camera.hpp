#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "GameObject.hpp"
#include "../geometry/Frustum.hpp"

class Camera : public GameObject {
	public:
		Camera(const std::string &cameraName = "", const vec3f& pos = vec3f(0.0f));
		virtual ~Camera();

		void lookInDir(const vec3f& direction);
		void rotateLocal(float angle, const vec3f& axis);
		void rotateGlobal(float angle, const vec3f& axis);
		void rotateAround(float angle, const vec3f& axis, const vec3f& center);

		vec3f getWorldPos() const;
		vec3f getForward() const;
		mat4f getView() const;
		mat4f getProjection() const;
		const Frustum& getFrustum() const;

		vec3f pos;
		mat4f projection;
	protected:
		virtual void update(float deltaTime);

		mat4f rotation;
		Frustum frustum;
};

#endif // CAMERA_HPP
