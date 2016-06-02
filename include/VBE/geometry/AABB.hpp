#ifndef AABB_HPP
#define AABB_HPP

#include <VBE/math.hpp>
#include <VBE/system/Log.hpp>

///
/// \brief Represents an Axis-Aliged Bounding Box
///
class AABB {
    public:
        ///
        /// \brief Default constructor
        ///
        /// This AABB will be init with the maximum value
        /// in all three edges for the minimum point
        /// and vice-versa. This leaves the AABB in an
        /// invalid state untill extended at least once.
        ///
        AABB();
        ///
        /// \brief Copy constructor
        ///
        /// The minimum and maximum will be copied
        ///
        AABB(const AABB& aabb);
        ///
        /// \brief Explicit constructor
        ///
        AABB(const vec3f& pmin, const vec3f& pmax);
        ///
        /// \brief Destructor
        ///
        ~AABB();

        ///
        /// \brief Extend this AABB to contain a point
        ///
        void extend(const vec3f& p);

        ///
        /// \brief Extend this AABB to contain another AABB
        ///
        void extend(const AABB& aabb);

        ///
        /// \brief Test a point against this AABB
        ///
        /// Points on the edge are considered inside
        ///
        /// \return Wether the point lies inside or not
        ///
        bool inside(const vec3f& p) const; //p inside this box

        ///
        /// \brief Test another AABB against this AABB
        ///
        /// Merely overlapping will not pass this test
        ///
        /// \return Wether the AABB lies inside or not
        ///
        bool inside(const AABB& aabb) const; //aabb inside this boxs

        ///
        /// \brief Get the current minimum
        ///
        /// \return Minimum point
        ///
        vec3f getMin() const;

        ///
        /// \brief Get the current maximum
        ///
        /// \return Maximum point
        ///
        vec3f getMax() const;

        ///
        /// \brief Get the current center
        ///
        /// \return Center
        ///
        vec3f getCenter() const;

        ///
        /// \brief Get the current dimensions
        ///
        /// \return Dimensions
        ///
        vec3f getDimensions() const;

        ///
        /// \brief Get the current radius
        ///
        /// \return Radius
        ///
        float getRadius() const;

    private:
        friend class Collision;
        vec3f pmin = vec3f(std::numeric_limits<float>::max());
        vec3f pmax = vec3f(std::numeric_limits<float>::lowest());
};
///
/// \class AABB AABB.hpp <VBE/geometry/AABB.hpp>
///	\ingroup Geometry
///
/// This class can be used to test against other geometry objects.
///
/// \see Collision
///

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

const Log&operator << (const Log& log, const AABB& aabb);

#endif // AABB_HPP
