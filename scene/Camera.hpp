#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "GameObject.hpp"
#include "../geometry/Frustum.hpp"

class Camera : public GameObject {
	public:
		Camera(const std::string &cameraName = "", const vec3f& pos = vec3f(0.0f), const vec3f& rot = vec3f(0.0f));
		virtual ~Camera();

		void update(float deltaTime);

		void lookInDir(); //TODO
		void rotateLocal(float angle, vec3f axis);
		void rotateGlobal(float angle, vec3f axis);

		vec3f getWorldPos() const;
		vec3f getForward() const;
		mat4f getView() const;
		mat4f getProjection() const;
		const Frustum& getFrustum() const;

		vec3f pos;
		mat4f projection;
	protected:
		mat4f rotation;
		Frustum frustum;
};

#endif // CAMERA_HPP
