#ifndef COLLISION_HPP
#define COLLISION_HPP
#include "Frustum.hpp"

class Collision {
	public:
		static bool Frustum_AABB(const Frustum& frustum, const AABB& box);
		static bool Frustum_Point(const Frustum& frustum, const vec3f& p);
		static bool Frustum_Sphere(const Frustum& frustum, const vec3f& center, float radius);
		static bool AABB_AABB(const AABB& frustum, const AABB& box);
	private:
		Collision();
		~Collision();
};

#endif // COLLISION_HPP
