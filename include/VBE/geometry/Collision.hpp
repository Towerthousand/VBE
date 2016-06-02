#ifndef COLLISION_HPP
#define COLLISION_HPP
#include "Frustum.hpp"
#include "Ray.hpp"

#include <bitset>

///
/// \brief Collision functions for geometry testing
///
class Collision {
    public:
        ///
        /// \brief Test an AABB against a Frustum
        ///
        static bool intersects(const Frustum& f, const AABB& b);

        ///
        /// \brief Test an AABB against a Frustum
        ///
        static bool intersects(const AABB& b, const Frustum& f) {return intersects(f, b);}

        ///
        /// \brief Test an AABB against a Frustum, with ommited planes
        /// \param ommitedPlanes A bitset of 6 bits where each bit represents wether that
        ///        particular Frustum::PlaneID was ommited from the test
        ///
        static bool intersects(const Frustum& f, const AABB& b, std::bitset<6> ommitedPlanes);

        ///
        /// \brief Test a point against a Frustum
        ///
        static bool intersects(const Frustum& f, const vec3f& p);

        ///
        /// \brief Test a point against a Frustum
        ///
        static bool intersects(const vec3f& p, const Frustum& f) {return intersects(f, p);}

        ///
        /// \brief Test a point against a Frustum, with ommited planes
        /// \param ommitedPlanes A bitset of 6 bits where each bit represents wether that
        ///        particular Frustum::PlaneID was ommited from the test
        ///
        static bool intersects(const Frustum& f, const vec3f& b, std::bitset<6> ommitedPlanes);

        ///
        /// \brief Test a Sphere against a Frustum
        ///
        static bool intersects(const Frustum& f, const Sphere& s);

        ///
        /// \brief Test a Sphere against a Frustum
        ///
        static bool intersects(const Sphere& s, const Frustum& f) {return intersects(f, s);}

        ///
        /// \brief Test a Sphere against a Frustum, with ommited planes
        /// \param ommitedPlanes A bitset of 6 bits where each bit represents wether that
        ///        particular Frustum::PlaneID was ommited from the test
        ///
        static bool intersects(const Frustum& f, const Sphere& s, std::bitset<6> ommitedPlanes);

        ///
        /// \brief Test an AABB against another AABB
        ///
        static bool intersects(const AABB& f, const AABB& b);

        ///
        /// \brief Get the intersection point between an AABB and a Ray
        ///
        /// \return Pair (bool, float) where the bool tells wether if the test passed
        ///			(the Ray touched the AABB) and in case it did, the distance to the
        ///			ray's origin from the intersection point
        ///
        static std::pair<bool, float> intersectionPoint(const AABB& b, const Ray& r);

        ///
        /// \brief Get the intersection point between an AABB and a Ray
        ///
        static std::pair<bool, float> intersectionPoint(const Ray& r, const AABB& b) {return intersectionPoint(b, r);}

    private:
        Collision();
        ~Collision();
};
///
/// \class Collision Collision.hpp <VBE/geometry/Collision.hpp>
///	\ingroup Geometry
///
/// This class can be used to test geometry objects against each other.
/// Tested objects should be valid (i.e. no radius of 0 for spheres or negative
/// dimensions for bounding boxes)
///
/// \see AABB, Sphere, Ray, Plane, Frustum
///

#endif // COLLISION_HPP
