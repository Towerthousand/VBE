#include <VBE/geometry/Frustum.hpp>

Frustum::Frustum() {
}

Frustum::~Frustum() {
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
    planes[TOP_PLANE]		= Plane(vec3f(ntl/ntl.w),vec3f(ftl/ftl.w),vec3f(ftr/ftr.w));
    planes[BOTTOM_PLANE]	= Plane(vec3f(nbl/nbl.w),vec3f(nbr/nbr.w),vec3f(fbr/fbr.w));
    planes[LEFT_PLANE]	= Plane(vec3f(nbl/nbl.w),vec3f(fbl/fbl.w),vec3f(ftl/ftl.w));
    planes[RIGHT_PLANE]	= Plane(vec3f(ntr/ntr.w),vec3f(ftr/ftr.w),vec3f(fbr/fbr.w));
    planes[NEAR_PLANE]	= Plane(vec3f(nbl/nbl.w),vec3f(ntl/ntl.w),vec3f(ntr/ntr.w));
    planes[FAR_PLANE]		= Plane(vec3f(fbr/fbr.w),vec3f(ftr/ftr.w),vec3f(ftl/ftl.w));
}

Plane Frustum::getPlane(Frustum::PlaneID p) const {
    return planes[p];
}
