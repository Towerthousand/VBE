#ifndef RAY_HPP
#define RAY_HPP
#include "../tools.hpp"

class Ray {
	public:
		Ray(vec3f o, vec3f dir) : o(o), dir(dir) {}
		~Ray() {}

		vec3f getOrigin() const {return o;}
		vec3f getDirection() const {return dir;}

	private:
		friend class Collision;

		vec3f o;
		vec3f dir;
};

#endif // RAY_HPP
