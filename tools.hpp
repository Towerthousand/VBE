#ifndef TOOLS_HPP
#define TOOLS_HPP

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

//GLM (openGL Math)
#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4 (core)
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp> // value_ptr
#include <glm/gtc/noise.hpp> //noise

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
typedef glm::detail::tmat2x2<float> mat2f;
typedef glm::detail::tmat3x3<float> mat3f;
typedef glm::detail::tmat4x4<float> mat4f;
typedef glm::detail::tmat2x2<double> mat2d;
typedef glm::detail::tmat3x3<double> mat3d;
typedef glm::detail::tmat4x4<double> mat4d;

//prototype misc functions here (define in tools.cpp) and inlines.
std::string toString(float num);

//defines (global settings and constants)
#define WINDOW_TITLE "Engine"
#define CONTEXT_SETTINGS_OPENGL sf::ContextSettings(32,32,0,4,2)
#define DEG_TO_RAD ((2*M_PI)/360.0f)

//frustum settings
#define FOV 60.0f //degrees
#define ZNEAR 0.01f
#define ZFAR 1000.0f

//texture settings
#define MAX_TEXTURES 1 //max number of currently used textures
#define TEXSIZE 8 //size of block textures

//global variables
extern int SCRWIDTH;
extern int SCRHEIGHT;
extern bool WINDOWFOCUS;
extern sf::Clock GLOBALCLOCK;

#endif // TOOLS_HPP
