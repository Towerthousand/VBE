#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(GameObject* parent) : GameObject(parent, vec3f(0.0f), vec3f(0.0f))
{
	//TODO: Todo esto deberia ser configurable.
	transform = glm::perspective(FOV,float(SCRWIDTH)/float(SCRHEIGHT),ZNEAR,ZFAR);
	transform = glm::translate(transform,vec3f(0,0,-10));
}
