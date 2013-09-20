#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(GameObject* parent, vec3f pos) : GameObject(parent), pos(pos) { //TODO: Todo esto deberia ser configurable.
	transform = glm::perspective(FOV,float(SCRWIDTH)/float(SCRHEIGHT),ZNEAR,ZFAR);
	transform = glm::translate(transform,pos);
}
