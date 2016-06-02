#ifndef RAY_HPP
#define RAY_HPP
#include <VBE/math.hpp>

///
/// \brief Represents a 3D Ray
///
class Ray {
    public:
        ///
        /// \brief Default constructor
        ///
        /// Generated Ray will be invalid by default
        ///
        Ray() : o(0.0f), dir(0.0f) {}

        ///
        /// \brief Data constructor
        ///
        /// Will initialize ray with the provided data
        ///
        /// \param o Origin of the ray
        /// \param o Direction of the ray. Doesn't need to be normalized,
        /// but it should not be zero.
        ///
        Ray(vec3f o, vec3f dir) : o(o), dir(glm::normalize(dir)) {}

        ///
        /// \brief Destructor
        ///
        ~Ray() {}

        ///
        /// \brief Origin point of the ray
        ///
        vec3f o;

        ///
        /// \brief Normalized direction of the ray
        ///
        vec3f dir;
};
///
/// \class Ray Ray.hpp <VBE/geometry/Ray.hpp>
///	\ingroup Geometry
///
/// This class can be used to test against other geometry objects.
///
/// \see Collision
///

#endif // RAY_HPP
