#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "tools.hpp"

class Sphere {
	public:
		Sphere(vec3f center, float radius);
		~Sphere();

		vec3f getCenter() const {return center;}
		float getRadius() const {return radius;}

	private:
		friend class Collision;

		vec3f center;
		float radius;
};

#endif // SPHERE_HPP
