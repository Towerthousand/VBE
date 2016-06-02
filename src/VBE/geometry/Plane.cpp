#include <VBE/geometry/Plane.hpp>

Plane::Plane(vec3f p0, vec3f p1, vec3f p2) : n(0), d(0) {
    vec3f v = p1-p0;
    vec3f u = p2-p0;
    n = glm::cross(u,v);
    if(glm::length(n) > 0.001f) n = glm::normalize(n);
    d = -glm::dot(n,p0);
}

Plane::Plane(vec3f n, vec3f p) : n(glm::normalize(n)), d(-glm::dot(glm::normalize(n),p)) {
}

Plane::Plane(vec3f n, float d) : n(glm::normalize(n)), d(d/glm::length(n)) {
}

Plane::Plane(vec4f ABCD) : n(vec3f(ABCD)), d(ABCD.z) {
    float l = glm::length(n);
    n /= l;
    d /= l;
}

Plane::Plane() : n(0), d(0) {
}

Plane::~Plane() {
}

bool Plane::inside(const Sphere& s) const {
    float distance = glm::dot(n,s.center) + d;
    return (distance < s.radius);
}

bool Plane::inside(const vec3f& p) const {
    float distance = glm::dot(n,p) + d;
    return (distance < 0);
}

bool Plane::inside(const AABB& box) const {
    vec3f c = box.getCenter();
    vec3f h = (box.getMax()-box.getMin())/2.0f; //half diagonal
    float e = glm::dot(h, glm::abs(n));
    float s = glm::dot(c, n) + d;
    if((s-e) > 0) return false;
    else return true;
}
