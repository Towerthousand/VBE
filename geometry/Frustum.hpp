#ifndef FRUSTUM_HPP
#define FRUSTUM_HPP
#include "Plane.hpp"
#include "AABB.hpp"

class Frustum {
		enum { //frustrum planes
			TOP = 0,
			BOTTOM,
			LEFT,
			RIGHT,
			NEAR,
			FAR
		};

	public:

		Frustum();
		~Frustum();

		void calculate(mat4f VP);
		bool insideFrustum(const vec3f& p) const;
		bool insideFrustum(const vec3f& center, float radius) const;
		bool insideFrustum(const AABB& box) const;

	private:
		Plane planes[4];
};

#endif // FRUSTUM_HPP
