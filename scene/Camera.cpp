#include "Camera.hpp"

Camera::Camera(const std::string& cameraName, const vec3f& pos)
	: pos(pos), projection(1.0f), rotation(1.0f) {
	if(cameraName != "") this->setName(cameraName);
}

Camera::~Camera() {
}

void Camera::update(float deltaTime) {
	(void) deltaTime;
	frustum.calculate(projection*getView());
}

void Camera::lookInDir(const vec3f& direction) {
	vec3f dummyUp = (glm::abs(glm::normalize(direction)) == vec3f(0, 1, 0))? vec3f(0,0,1) : vec3f(0, 1, 0);
	vec3f front = glm::normalize(-direction);
	vec3f right = glm::normalize(glm::cross(dummyUp, front));
	vec3f up = glm::normalize(glm::cross(front, right));
	rotation = glm::transpose(mat4f(right.x, right.y, right.z, 0,
									up.x   , up.y   , up.z   , 0,
									front.x, front.y, front.z, 0,
									0      , 0      , 0      , 1));
}

void Camera::rotateLocal(float angle, const vec3f& axis) {
	rotation = glm::rotate(mat4f(1.0), angle, axis)*rotation;
}

void Camera::rotateGlobal(float angle, const vec3f& axis) {
	vec3f gaxis = vec3f(rotation*vec4f(axis.x, axis.y, axis.z, 0));
	rotation = glm::rotate(mat4f(1.0), angle, gaxis)*rotation;
}

void Camera::rotateAround(float angle, const vec3f& axis, const vec3f& center) {
	vec3f gaxis = vec3f(vec4f(axis.x, axis.y, axis.z, 0)*rotation);
	rotation = glm::translate(rotation,  center);
	rotation = glm::rotate(rotation, angle, gaxis);
	rotation = glm::translate(rotation, -center);
}

vec3f Camera::getWorldPos() const {
	return vec3f(fullTransform*vec4f(pos,1));
}

vec3f Camera::getForward() const {
	mat4f m = getView();
	return -glm::normalize(vec3f(m[0][2],m[1][2],m[2][2]));
}

mat4f Camera::getView() const {
	return glm::translate(rotation, -getWorldPos());
}

const Frustum&Camera::getFrustum() const {
	return frustum;
}
