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
	$$PWD/Game.cpp \
	$$PWD/tools.cpp \
	$$PWD/graphics/Texture.cpp \
	$$PWD/graphics/Shader.cpp \
	$$PWD/graphics/ShaderProgram.cpp \
	$$PWD/audio/AudioManager.cpp \
	$$PWD/input/Input.cpp \
	$$PWD/GameObject.cpp \
	$$PWD/graphics/Mesh.cpp \
	$$PWD/graphics/Vertex.cpp \
	$$PWD/graphics/Model.cpp \
	$$PWD/graphics/Uniform.cpp \
	$$PWD/graphics/ShaderBinding.cpp \
	$$PWD/Manager.cpp \
	$$PWD/graphics/RenderTarget.cpp \
	$$PWD/ContainerObject.cpp \
    VBE/graphics/Texture3D.cpp \
    VBE/graphics/Texture2D.cpp

HEADERS += \
	$$PWD/Game.hpp \
	$$PWD/tools.hpp \
	$$PWD/graphics/Texture.hpp \
	$$PWD/graphics/Shader.hpp \
	$$PWD/graphics/ShaderProgram.hpp \
	$$PWD/audio/AudioManager.hpp \
	$$PWD/input/Input.hpp \
	$$PWD/GameObject.hpp \
	$$PWD/glm/*.hpp \
	$$PWD/graphics/Mesh.hpp \
	$$PWD/graphics/Vertex.hpp \
	$$PWD/graphics/Model.hpp \
	$$PWD/graphics/Uniform.hpp \
	$$PWD/graphics/ShaderBinding.hpp \
	$$PWD/includes.hpp \
	$$PWD/Manager.hpp \
	$$PWD/graphics/RenderTarget.hpp \
	$$PWD/ContainerObject.hpp \
    VBE/graphics/Texture3D.hpp \
    VBE/graphics/Texture2D.hpp

OTHER_FILES +=

