#ifndef PLANE_HPP
#define PLANE_HPP
#include "AABB.hpp"

class Plane {
	public:
		Plane(vec3f p0, vec3f p1, vec3f p2); //Three points
		Plane(vec3f n, vec3f p); //point and normal
		Plane(vec3f n, float d); //Equation Ax +By +Cz + D = 0, where n = (A,B,C)
		Plane(vec4f ABCD); //Equation Ax + By + Cz + D = 0, where ABCD = (A,B,C,D)
		Plane(); //generated plane will be invalid by default
		~Plane();

		bool inside(const vec3f& p, float r) const;
		bool inside(const vec3f& p) const;
		bool inside(const AABB& box) const;

	private:
		friend class Collision;
		vec3f n;
		float d;
};

#endif // PLANE_HPP
