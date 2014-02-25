#ifndef FRUSTUM_HPP
#define FRUSTUM_HPP
#include "Plane.hpp"

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
	private:
		friend class Collision;
		Plane planes[4];
};

#endif // FRUSTUM_HPP
