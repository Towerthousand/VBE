#ifndef TOOLS_HPP
#define TOOLS_HPP

//OpenGL (Open Graphics Library)
#define GL_GLEXT_PROTOTYPES 1

#if defined(ANDROID)
	#include "GLES2/gl2.h"
	#define VBE_GLES2
#elif defined(WINDOWS)
	#include "GL/glew.h"
#else
	#include <GL/gl.h> //core
#endif

//Image loading
#include "dependencies/stb_image/stb_image.hpp"

//GLM (openGL Math)
#include "dependencies/glm/glm.hpp" // vec3, vec4, ivec4, mat4 (core)
#include "dependencies/glm/gtc/matrix_transform.hpp" // translate, rotate, scale, perspective

//SDL 2
#if defined(ANDROID)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

//STL stuff
#ifdef WINDOWS
#define _USE_MATH_DEFINES
/* Constants rounded for 21 decimals. */
#define M_E 2.71828182845904523536
#define M_LOG2E 1.44269504088896340736
#define M_LOG10E 0.434294481903251827651
#define M_LN2 0.693147180559945309417
#define M_LN10 2.30258509299404568402
#define M_PI 3.14159265358979323846
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
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <list>
#include <cstring>
#include <queue>
#include <limits>
#include <set>
#include <mutex>
#include <thread>

//math typedefs

typedef glm::detail::tvec2<float> vec2f;
typedef glm::detail::tvec3<float> vec3f;
typedef glm::detail::tvec4<float> vec4f;
typedef glm::detail::tvec2<double> vec2d;
typedef glm::detail::tvec3<double> vec3d;
typedef glm::detail::tvec4<double> vec4d;
typedef glm::detail::tvec2<int> vec2i;
typedef glm::detail::tvec3<int> vec3i;
typedef glm::detail::tvec4<int> vec4i;
typedef glm::detail::tvec2<unsigned int> vec2ui;
typedef glm::detail::tvec3<unsigned int> vec3ui;
typedef glm::detail::tvec4<unsigned int> vec4ui;
typedef glm::detail::tvec2<short> vec2s;
typedef glm::detail::tvec3<short> vec3s;
typedef glm::detail::tvec4<short> vec4s;
typedef glm::detail::tvec2<unsigned short> vec2us;
typedef glm::detail::tvec3<unsigned short> vec3us;
typedef glm::detail::tvec4<unsigned short> vec4us;
typedef glm::detail::tvec2<char> vec2c;
typedef glm::detail::tvec3<char> vec3c;
typedef glm::detail::tvec4<char> vec4c;
typedef glm::detail::tvec2<unsigned char> vec2uc;
typedef glm::detail::tvec3<unsigned char> vec3uc;
typedef glm::detail::tvec4<unsigned char> vec4uc;
typedef glm::detail::tvec2<bool> vec2b;
typedef glm::detail::tvec3<bool> vec3b;
typedef glm::detail::tvec4<bool> vec4b;
typedef glm::detail::tmat2x2<float> mat2f;
typedef glm::detail::tmat3x3<float> mat3f;
typedef glm::detail::tmat4x4<float> mat4f;
typedef glm::detail::tmat2x2<double> mat2d;
typedef glm::detail::tmat3x3<double> mat3d;
typedef glm::detail::tmat4x4<double> mat4d;

#define DEG_TO_RAD (float(M_PI)/180.0f)

//Logging system and log macros

#include "utils/Log.hpp"

//NonCopyable protoclass

#include "utils/NonCopyable.hpp"

namespace Utils {
    inline std::string toLower(std::string str) {
        for (std::string::iterator i = str.begin(); i != str.end(); ++i)
            *i = static_cast<char>(std::tolower(*i));
        return str;
    }
}

#endif // TOOLS_HPP
