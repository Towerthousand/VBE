#include <VBE/geometry/AABB.hpp>

AABB::AABB() {
}

AABB::AABB(const AABB &aabb) {
    pmin = aabb.pmin;
    pmax = aabb.pmax;
}

AABB::AABB(const vec3f &min, const vec3f &max) {
    this->pmin = min;
    this->pmax = max;
}

AABB::~AABB() {
}

void AABB::extend(const vec3f &p) {
    if (p.x < pmin.x) pmin.x = p.x;
    if (p.y < pmin.y) pmin.y = p.y;
    if (p.z < pmin.z) pmin.z = p.z;
    if (p.x > pmax.x) pmax.x = p.x;
    if (p.y > pmax.y) pmax.y = p.y;
    if (p.z > pmax.z) pmax.z = p.z;
}

void AABB::extend(const AABB &aabb) {
    this->extend(aabb.pmin);
    this->extend(aabb.pmax);
}

bool AABB::inside(const vec3f &p) const {
    if (p.x < pmin.x) return false;
    if (p.y < pmin.y) return false;
    if (p.z < pmin.z) return false;
    if (p.x > pmax.x) return false;
    if (p.y > pmax.y) return false;
    if (p.z > pmax.z) return false;
    return true;
}

bool AABB::inside(const AABB &aabb) const {
    return inside(aabb.pmin) && inside(aabb.pmax);
}


const Log&operator <<(const Log& log, const AABB& aabb) {
    log << "[Center: " << aabb.getCenter() << ", Dimensions: " << aabb.getDimensions() << "]";
    return log;
}
