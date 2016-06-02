#include <VBE/geometry/Collision.hpp>

bool Collision::intersects(const Frustum& f, const AABB& b) {
    for(unsigned int i=0; i < 6; i++)
        if(!f.planes[i].inside(b)) return false;
    return true;
}

bool Collision::intersects(const Frustum& f, const AABB& b, std::bitset<6> ommitedPlanes) {
    for(unsigned int i=0; i < 6; i++)
        if(!ommitedPlanes.test(i) && !f.planes[i].inside(b)) return false;
    return true;
}

bool Collision::intersects(const Frustum& f, const vec3f& p) {
    for(unsigned int i=0; i < 6; i++)
        if(!f.planes[i].inside(p)) return false;
    return true;
}

bool Collision::intersects(const Frustum& f, const vec3f& p, std::bitset<6> ommitedPlanes) {
    for(unsigned int i=0; i < 6; i++)
        if(!ommitedPlanes.test(i) && !f.planes[i].inside(p)) return false;
    return true;
}

bool Collision::intersects(const Frustum& f, const Sphere& s) {
    for(unsigned int i=0; i < 6; i++)
        if(!f.planes[i].inside(s)) return false;
    return true;
}

bool Collision::intersects(const Frustum& f, const Sphere& s, std::bitset<6> ommitedPlanes) {
    for(unsigned int i=0; i < 6; i++)
        if(!ommitedPlanes.test(i) && !f.planes[i].inside(s)) return false;
    return true;
}

bool Collision::intersects(const AABB& a, const AABB& b) {
    if (a.pmin.x > b.pmax.x) return false;
    if (a.pmax.x < b.pmin.x) return false;
    if (a.pmin.y > b.pmax.y) return false;
    if (a.pmax.y < b.pmin.y) return false;
    if (a.pmin.z > b.pmax.z) return false;
    if (a.pmax.z < b.pmin.z) return false;
    return true;
}

std::pair<bool, float> Collision::intersectionPoint(const AABB& b, const Ray& r) {
    //Slopes method. Realtime rendering (3rd Ed.) pg. 743 for reference
    float tmin = std::numeric_limits<float>::min();
    float tmax = std::numeric_limits<float>::max();
    vec3f p = b.getCenter() - r.o;
    vec3f side_dirs[3] = {vec3f(1,0,0), vec3f(0,1,0), vec3f(0,0,1)};
    vec3f side_lengths = b.getDimensions()/2.0f;
    for(int i = 0; i < 3; ++i) {
        float e = glm::dot(side_dirs[i], p);
        float f = glm::dot(side_dirs[i], r.dir);
        if(glm::length(f) > 0.001) {
            float t1 = (e + side_lengths[i])/f;
            float t2 = (e - side_lengths[i])/f;
            if(t1 > t2) std::swap(t1,t2);
            if(t1 > tmin) tmin = t1;
            if(t2 < tmax) tmax = t2;
            if(tmin > tmax) return std::pair<bool, float>(false, 0);
            if(tmax < 0) return std::pair<bool, float>(false, 0);
        }
        else if((-e - side_lengths[i]) > 0 || (-e + side_lengths[i]) < 0) return std::pair<bool, float>(false, 0);
    }
    if(tmin > 0) return std::pair<bool, float>(true, tmin);
    return std::pair<bool, float>(true, tmax);
}
