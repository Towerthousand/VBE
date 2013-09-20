#ifndef PERSPECTIVECAMERA_HPP
#define PERSPECTIVECAMERA_HPP

#include "GameObject.hpp"

class PerspectiveCamera : public GameObject {
	public:
		PerspectiveCamera(GameObject* parent, vec3f pos);
		vec3f pos;
};

#endif // PERSPECTIVECAMERA_HPP
