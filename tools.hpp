#ifndef TOOLS_HPP
#define TOOLS_HPP

#ifdef __DEBUG
  #define VBE_ASSERT(expression, string) do \
	{ \
		if(!(expression)) { \
			std::cout << "ASSERT FAILED, STOPPING " << std::endl;\
			std::cout << "Reason: " << string << std::endl; \
			assert(expression); \
			std::exit(-1); \
		} \
	} while (0)
#else
  #define VBE_ASSERT(expression, string)
#endif
#ifdef __LOG
  #define VBE_LOG(log) std::cout << log << std::endl
#else
  #define VBE_LOG(log)
#endif
#ifdef __DLOG
  #define VBE_DLOG(log) VBE_LOG(log)
#else
  #define VBE_DLOG(log)
#endif


//OpenGL (Open Graphics Library)
#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h> //core

//SFML (Simple Fast Media Library)
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//STL (Standard Toolkit Library)
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <list>
#include <cmath>
#include <cstring>
#include <queue>

//GLM (openGL Math)
#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4 (core)
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective

//math typedefs
typedef glm::detail::tvec4<int> vec4i;
typedef glm::detail::tvec4<float> vec4f;
typedef glm::detail::tvec4<double> vec4d;
typedef glm::detail::tvec4<uint> vec4ui;
typedef glm::detail::tvec3<int> vec3i;
typedef glm::detail::tvec3<float> vec3f;
typedef glm::detail::tvec3<double> vec3d;
typedef glm::detail::tvec3<uint> vec3ui;
typedef glm::detail::tvec2<int> vec2i;
typedef glm::detail::tvec2<float> vec2f;
typedef glm::detail::tvec2<double> vec2d;
typedef glm::detail::tvec2<uint> vec2ui;
typedef glm::detail::tvec2<bool> vec2b;
typedef glm::detail::tmat2x2<float> mat2f;
typedef glm::detail::tmat3x3<float> mat3f;
typedef glm::detail::tmat4x4<float> mat4f;
typedef glm::detail::tmat2x2<double> mat2d;
typedef glm::detail::tmat3x3<double> mat3d;
typedef glm::detail::tmat4x4<double> mat4d;

//defines (global settings and constants)
extern std::string WINDOW_TITLE;
extern sf::ContextSettings CONTEXT_SETTINGS_OPENGL;
extern const float DEG_TO_RAD;

//frustum settings
extern float FOV;
extern float ZNEAR;
extern float ZFAR;

//global variables
extern int SCRWIDTH;
extern int SCRHEIGHT;
extern bool WINDOWFOCUS;
extern const sf::Clock GLOBALCLOCK;

#endif // TOOLS_HPP
