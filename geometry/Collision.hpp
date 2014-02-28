#ifndef COLLISION_HPP
#define COLLISION_HPP
#include "Frustum.hpp"
#include "Ray.hpp"

class Collision {
	public:
		static bool intersects(const Frustum& frustum, const AABB& box);
		static bool intersects(const Frustum& frustum, const vec3f& p);
		static bool intersects(const Frustum& frustum, const vec3f& center, float radius);
		static bool intersects(const AABB& frustum, const AABB& box);
		static std::pair<bool, float> intersectionPoint(const AABB& box, const Ray& ray);

	private:
		Collision();
		~Collision();
};

#endif // COLLISION_HPP
