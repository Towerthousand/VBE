#include <VBE/config.hpp>

//OpenGL (Open Graphics Library)
#if defined(VBE_GLES2)
#include "GLES2/gl2.h"
#elif defined(WINDOWS)
#include "GL/glew.h"
#else
#include <GL/glew.h>
#endif
