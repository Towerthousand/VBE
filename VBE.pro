CONFIG(debug, debug|release) {
  DEFINES += "__DEBUG" "__LOG"
}
#DEFINES += "__DLOG"

#__DEBUG will make asserts on all risky operations, and will output a detailed error message if it fails
#__LOG will output all VBE_LOG(..). This is general (important) info such as resource loading, etc
#__DLOG will output all VBE_DLOG(..). This is detailed log info, use it for debugging.
# Disable all three for faster internets

TEMPLATE = app
CONFIG -= qt
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGL
INCLUDEPATH += $$PWD/
QMAKE_CXXFLAGS += -std=c++0x
SOURCES += \
	$$PWD/tools.cpp \
	$$PWD/scene/Game.cpp \
	$$PWD/graphics/Texture.cpp \
	$$PWD/graphics/Shader.cpp \
	$$PWD/graphics/ShaderProgram.cpp \
	$$PWD/audio/AudioManager.cpp \
	$$PWD/input/Input.cpp \
	$$PWD/scene/GameObject.cpp \
	$$PWD/graphics/Mesh.cpp \
	$$PWD/graphics/Vertex.cpp \
	$$PWD/graphics/Model.cpp \
	$$PWD/graphics/Uniform.cpp \
	$$PWD/graphics/ShaderBinding.cpp \
	$$PWD/utils/Manager.cpp \
	$$PWD/graphics/RenderTarget.cpp \
	$$PWD/scene/ContainerObject.cpp \
	$$PWD/graphics/Texture3D.cpp \
	$$PWD/graphics/Texture2D.cpp \
        $$PWD/graphics/Texture2DArray.cpp \
	$$PWD/graphics/OBJLoader.cpp \
	$$PWD/geometry/AABB.cpp \
	$$PWD/geometry/Plane.cpp \
	$$PWD/geometry/Frustum.cpp \
	$$PWD/scene/Camera.cpp \
	$$PWD/Log.cpp

HEADERS += \
	$$PWD/tools.hpp \
	$$PWD/includes.hpp \
	$$PWD/scene/Game.hpp \
	$$PWD/graphics/Texture.hpp \
	$$PWD/graphics/Shader.hpp \
	$$PWD/graphics/ShaderProgram.hpp \
	$$PWD/audio/AudioManager.hpp \
	$$PWD/input/Input.hpp \
	$$PWD/scene/GameObject.hpp \
	$$PWD/glm/*.hpp \
	$$PWD/graphics/Mesh.hpp \
	$$PWD/graphics/Vertex.hpp \
	$$PWD/graphics/Model.hpp \
	$$PWD/graphics/Uniform.hpp \
	$$PWD/graphics/ShaderBinding.hpp \
	$$PWD/utils/Manager.hpp \
	$$PWD/graphics/RenderTarget.hpp \
	$$PWD/scene/ContainerObject.hpp \
	$$PWD/graphics/Texture3D.hpp \
	$$PWD/graphics/Texture2D.hpp \
        $$PWD/graphics/Texture2DArray.hpp \
	$$PWD/graphics/OBJLoader.hpp \
	$$PWD/geometry/AABB.hpp \
	$$PWD/geometry/Plane.hpp \
	$$PWD/geometry/Frustum.hpp \
	$$PWD/scene/Camera.hpp \
	$$PWD/Log.hpp
