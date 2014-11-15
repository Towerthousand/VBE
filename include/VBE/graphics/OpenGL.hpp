#include <VBE/config.hpp>

//OpenGL (Open Graphics Library)
#define GL_GLEXT_PROTOTYPES 1

#if defined(VBE_GLES2)
	#include "GLES2/gl2.h"
#elif defined(WINDOWS)
	#define GLEW_STATIC
	#include "GL/glew.h"
#else
	#include <GL/gl.h> //core
#endif
