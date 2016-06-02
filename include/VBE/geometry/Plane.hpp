#ifndef PLANE_HPP
#define PLANE_HPP
#include "AABB.hpp"
#include "Sphere.hpp"

///
/// \brief Represents a 3D Plane
///
class Plane {
    public:
        ///
        /// \brief Default constructor
        ///
        /// Generated Plane will be invalid by default
        ///
        Plane();

        ///
        /// \brief Point constructor
        ///
        /// Given three points, will reconstruct the plane.
        /// Follows the right hand rule for the plane normal.
        /// p0, p1 and p2 should not be the same.
        ///
        Plane(vec3f p0, vec3f p1, vec3f p2);

        ///
        /// \brief Point/Normal constructor
        ///
        /// Given a point and a normal, will reconstruct the
        /// plane equation.
        ///
        ///
        /// \param n Normal vector, should not be zero
        /// \param p Point
        ///
        Plane(vec3f n, vec3f p);

        ///
        /// \brief Equation constructor
        ///
        /// Plane equation Ax + By + Cy + D = 0, where
        /// n = vec3f(A, B, C) and d = D.
        ///
        /// \param n Normal vector, should not be zero
        /// \param d Distance from origin
        ///
        Plane(vec3f n, float d);

        ///
        /// \brief Explicit equation constructor
        ///
        /// Plane equation Ax + By + Cy + D = 0
        ///
        /// \param ABCD Equation coefficients
        ///
        Plane(vec4f ABCD);

        ///
        /// \brief Destructor
        ///
        ~Plane();

        ///
        /// \brief Test a sphere against this plane
        ///
        /// \param s Sphere to be tested
        ///
        /// \return Wether the sphere lies inside or not
        ///
        bool inside(const Sphere& s) const;

        ///
        /// \brief Test a point against this plane
        ///
        /// \param p Point to be tested
        ///
        /// \return Wether the point lies inside or not
        ///
        bool inside(const vec3f& p) const;

        ///
        /// \brief Test an AABB against this plane
        ///
        /// \param p AABB to be tested
        ///
        /// \return Wether the AABB lies inside or not
        ///
        bool inside(const AABB& box) const;

        ///
        /// \brief Normal vector for this plane
        ///
        vec3f n;

        ///
        /// \brief Orthogonal distance to origin from this plane
        ///
        float d;
};
///
/// \class Plane Plane.hpp <VBE/geometry/Plane.hpp>
///	\ingroup Geometry
///
/// This class can be used to test against other geometry objects.
///
/// \see Collision
///

#endif // PLANE_HPP
