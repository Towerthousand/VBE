#include "Collision.hpp"

bool Collision::Frustum_AABB(const Frustum& frustum, const AABB& box) {
	for(unsigned int i=0; i < 4; i++)
		if(!frustum.planes[i].inside(box)) return false;
	return true;
}

bool Collision::Frustum_Point(const Frustum& frustum, const vec3f& p) {
	for(unsigned int i=0; i < 4; i++)
		if(!frustum.planes[i].inside(p)) return false;
	return true;
}

bool Collision::Frustum_Sphere(const Frustum& frustum, const vec3f& center, float radius) {
	for(unsigned int i=0; i < 4; i++)
		if(!frustum.planes[i].inside(center, radius)) return false;
	return true;
}

bool Collision::AABB_AABB(const AABB& a, const AABB& b) {
	if (a.pmin.x > b.pmax.x) return false;
	if (a.pmax.x < b.pmin.x) return false;
	if (a.pmin.y > b.pmax.y) return false;
	if (a.pmax.y < b.pmin.y) return false;
	if (a.pmin.z > b.pmax.z) return false;
	if (a.pmax.z < b.pmin.z) return false;
	return true;
}
