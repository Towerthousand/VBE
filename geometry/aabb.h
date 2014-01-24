#ifndef AABB_H
#define AABB_H

#include "tools.hpp"

class AABB
{
public:

    AABB();
    AABB(const AABB& aabb);
    AABB(const vec3f& min, const vec3f& max);
    ~AABB();

    void extend(const vec3f& p);
    void extend(const AABB& aabb);

    bool inside(const vec3f& p)     const;
    bool inside(const vec3f& aabb)  const;
    bool overlap(const vec3f& aabb) const;

    vec3f getMin()          const;
    vec3f getMax()          const;
    vec3f getCenter()       const;
    vec3f getDimensions()   const;
    float getRadius()       const;

private:

    vec3f min;
    vec3f max;

};

#endif // AABB_H
