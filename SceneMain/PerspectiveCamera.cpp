#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(vec3f pos) : pos(pos) { //TODO: Todo esto deberia ser configurable.
	transform = glm::perspective(FOV,float(SCRWIDTH)/float(SCRHEIGHT),ZNEAR,ZFAR);
	transform = glm::translate(transform,pos);
}
