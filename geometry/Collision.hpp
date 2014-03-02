#ifndef COLLISION_HPP
#define COLLISION_HPP
#include "Frustum.hpp"
#include "Ray.hpp"

class Collision {
	public:
		// Frustum/AABB
		static bool intersects(const Frustum& f, const AABB& b);
		static bool intersects(const AABB& b, const Frustum& f) {return intersects(f, b);}

		// Frustum/point
		static bool intersects(const Frustum& f, const vec3f& p);
		static bool intersects(const vec3f& p, const Frustum& f) {return intersects(f, p);}

		// Frustum/sphere
		static bool intersects(const Frustum& f, const Sphere& s);
		static bool intersects(const Sphere& s, const Frustum& f) {return intersects(f, s);}

		// AABB/AABB
		static bool intersects(const AABB& f, const AABB& b);

		// Ray/AABB
		static std::pair<bool, float> intersectionPoint(const AABB& b, const Ray& r);
		static std::pair<bool, float> intersectionPoint(const Ray& r, const AABB& b) {return intersectionPoint(b, r);}

	private:
		Collision();
		~Collision();
};

#endif // COLLISION_HPP
