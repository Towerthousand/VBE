#ifndef AABB_H
#define AABB_H

#include "tools.hpp"

class AABB
{
public:

    AABB();
    AABB(const AABB& aabb);
    AABB(const vec3f& pmin, const vec3f& pmax);
    ~AABB();

    void extend(const vec3f& p);
    void extend(const AABB& aabb);

    bool inside(const vec3f& p)     const;
    bool inside(const AABB& aabb)   const;
    bool overlap(const AABB& aabb)  const;

    vec3f getMin()          const;
    vec3f getMax()          const;
    vec3f getCenter()       const;
    vec3f getDimensions()   const;
    float getRadius()       const;

private:

    vec3f pmin;
    vec3f pmax;

};


inline vec3f AABB::getMin() const {
    return pmin;
}

inline vec3f AABB::getMax() const {
    return pmax;
}

inline vec3f AABB::getCenter() const {
    return 0.5f*(pmin + pmax);
}

inline vec3f AABB::getDimensions() const {
    return pmax - pmin;
}

inline float AABB::getRadius() const {
    return 0.5f*glm::length(pmax - pmin);
}


#endif // AABB_H
