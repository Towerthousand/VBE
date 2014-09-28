#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "tools.hpp"

class Sphere {
	public:
		Sphere(vec3f center, float radius);
		~Sphere();

		vec3f center;
		float radius;

	private:
		friend class Collision;
};

#endif // SPHERE_HPP
