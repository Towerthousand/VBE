#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <VBE/math.hpp>

///
/// \brief Represents a 3D Sphere
///
class Sphere {
    public:
        ///
        /// \brief Default constructor
        ///
        /// Generated Sphere will be invalid by default
        ///
        Sphere() : center(0.0f), radius(0.0f) {}
        ///
        /// \brief Data constructor
        ///
        /// Will initialize sphere with the provided data
        ///
        Sphere(vec3f center, float radius) : center(center), radius(radius) {
        }

        ///
        /// \brief Destructor
        ///
        ~Sphere() {}

        ///
        /// \brief Center of the Sphere
        ///
        vec3f center;

        ///
        /// \brief Radius of the Sphere
        ///
        float radius;
};
///
/// \class Sphere Sphere.hpp <VBE/geometry/Sphere.hpp>
///	\ingroup Geometry
///
/// This class can be used to test against other geometry objects.
///
/// \see Collision
///

#endif // SPHERE_HPP
