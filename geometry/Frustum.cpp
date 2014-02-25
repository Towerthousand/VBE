#include "Frustum.hpp"

Frustum::Frustum() {
}

Frustum::~Frustum() {
}

bool Frustum::insideFrustum( const vec3f &p) const {
	for(unsigned int i=0; i < 4; i++)
		if(!planes[i].inside(p)) return false;
	return true;
}

bool Frustum::insideFrustum( const vec3f &center, float radius) const {
	for(unsigned int i=0; i < 4; i++)
		if(!planes[i].inside(center,radius)) return false;
	return true;
}

bool Frustum::insideFrustum( const AABB &box) const {
	for(unsigned int i=0; i < 4; i++)
		if(!planes[i].inside(box)) return false;
	return true;
}

void Frustum::calculate(mat4f VP) {
	mat4f invVP = glm::inverse(VP);
	vec4f ntl,ntr,nbl,nbr,ftl,ftr,fbl,fbr;
	// compute the 4 corners of the frustum on the near plane
	ntl = invVP * vec4f(-1, 1,-1, 1);
	ntr = invVP * vec4f( 1, 1,-1, 1);
	nbl = invVP * vec4f(-1,-1,-1, 1);
	nbr = invVP * vec4f( 1,-1,-1, 1);

	// compute the 4 corners of the frustum on the far plane
	ftl = invVP * vec4f(-1, 1, 1, 1);
	ftr = invVP * vec4f( 1, 1, 1, 1);
	fbl = invVP * vec4f(-1,-1, 1, 1);
	fbr = invVP * vec4f( 1,-1, 1, 1);

	// compute the six planes
	planes[TOP]		= Plane(vec3f(ntl/ntl.w),vec3f(ftl/ftl.w),vec3f(ftr/ftr.w));
	planes[BOTTOM]	= Plane(vec3f(nbl/nbl.w),vec3f(nbr/nbr.w),vec3f(fbr/fbr.w));
	planes[LEFT]	= Plane(vec3f(nbl/nbl.w),vec3f(fbl/fbl.w),vec3f(ftl/ftl.w));
	planes[RIGHT]	= Plane(vec3f(ntr/ntr.w),vec3f(ftr/ftr.w),vec3f(fbr/fbr.w));
}
