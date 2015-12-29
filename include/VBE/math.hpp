#ifndef _VBE_MATH_H
#define _VBE_MATH_H

//GLM (openGL Math)
// vec3, vec4, ivec4, mat4 (core)
#include <VBE/dependencies/glm/glm.hpp>
// translate, rotate, scale, perspective
#include <VBE/dependencies/glm/gtc/matrix_transform.hpp>

//STL stuff
#ifdef WINDOWS
#define _USE_MATH_DEFINES
/* Constants rounded for 21 decimals. */
#define M_E 2.71828182845904523536
#define M_LOG2E 1.44269504088896340736
#define M_LOG10E 0.434294481903251827651
#define M_LN2 0.693147180559945309417
#define M_LN10 2.30258509299404568402
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define M_PI_2 1.57079632679489661923
#define M_PI_4 0.785398163397448309616
#define M_1_PI 0.318309886183790671538
#define M_2_PI 0.636619772367581343076
#define M_1_SQRTPI 0.564189583547756286948
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2 1.41421356237309504880
#define M_SQRT_2 0.707106781186547524401
#endif

#include <cmath>

//math typedefs

typedef glm::tvec2<float, glm::highp> vec2f;
typedef glm::tvec3<float, glm::highp> vec3f;
typedef glm::tvec4<float, glm::highp> vec4f;
typedef glm::tvec2<double, glm::highp> vec2d;
typedef glm::tvec3<double, glm::highp> vec3d;
typedef glm::tvec4<double, glm::highp> vec4d;
typedef glm::tvec2<int, glm::highp> vec2i;
typedef glm::tvec3<int, glm::highp> vec3i;
typedef glm::tvec4<int, glm::highp> vec4i;
typedef glm::tvec2<unsigned int, glm::highp> vec2ui;
typedef glm::tvec3<unsigned int, glm::highp> vec3ui;
typedef glm::tvec4<unsigned int, glm::highp> vec4ui;
typedef glm::tvec2<short, glm::highp> vec2s;
typedef glm::tvec3<short, glm::highp> vec3s;
typedef glm::tvec4<short, glm::highp> vec4s;
typedef glm::tvec2<unsigned short, glm::highp> vec2us;
typedef glm::tvec3<unsigned short, glm::highp> vec3us;
typedef glm::tvec4<unsigned short, glm::highp> vec4us;
typedef glm::tvec2<char, glm::highp> vec2c;
typedef glm::tvec3<char, glm::highp> vec3c;
typedef glm::tvec4<char, glm::highp> vec4c;
typedef glm::tvec2<unsigned char, glm::highp> vec2uc;
typedef glm::tvec3<unsigned char, glm::highp> vec3uc;
typedef glm::tvec4<unsigned char, glm::highp> vec4uc;
typedef glm::tvec2<bool, glm::highp> vec2b;
typedef glm::tvec3<bool, glm::highp> vec3b;
typedef glm::tvec4<bool, glm::highp> vec4b;
typedef glm::tmat2x2<float, glm::highp> mat2f;
typedef glm::tmat3x3<float, glm::highp> mat3f;
typedef glm::tmat4x4<float, glm::highp> mat4f;
typedef glm::tmat2x2<double, glm::highp> mat2d;
typedef glm::tmat3x3<double, glm::highp> mat3d;
typedef glm::tmat4x4<double, glm::highp> mat4d;

#define DEG_TO_RAD (float(M_PI)/180.0f)

#endif
