CONFIG(debug, debug|release) {
  DEFINES += "__DEBUG" "__LOG"
}

#__DEBUG will make asserts on all risky operations, and will output a detailed error message if it fails
#__LOG will output all VBE_LOG(..). This is general (important) info such as resource loading, etc
#__DLOG will output all VBE_DLOG(..). This is detailed log info, use it for debugging.
# Disable all three for faster internets

TEMPLATE = app
CONFIG -= qt
LIBS += -lGL -lSDL2
INCLUDEPATH += $$PWD/
QMAKE_CXXFLAGS += -std=c++0x
SOURCES += \
	$$PWD/scene/Game.cpp \
	$$PWD/graphics/Texture.cpp \
	$$PWD/graphics/Shader.cpp \
	$$PWD/graphics/ShaderProgram.cpp \
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
	$$PWD/utils/Log.cpp \
	$$PWD/environment/Environment.cpp \
	$$PWD/environment/Screen.cpp \
	$$PWD/environment/Keyboard.cpp \
	$$PWD/environment/Mouse.cpp \
	$$PWD/environment/StartingConfig.cpp \
	$$PWD/geometry/Collision.cpp \
	$$PWD/geometry/Ray.cpp \
	$$PWD/dependencies/stb_image/stb_image.cpp \
    VBE/geometry/Sphere.cpp \
    VBE/graphics/RenderState.cpp \
    VBE/graphics/TextureCubemap.cpp \
    VBE/graphics/RenderBuffer.cpp 

HEADERS += \
	$$PWD/tools.hpp \
	$$PWD/includes.hpp \
	$$PWD/scene/Game.hpp \
	$$PWD/graphics/Texture.hpp \
	$$PWD/graphics/Shader.hpp \
	$$PWD/graphics/ShaderProgram.hpp \
	$$PWD/scene/GameObject.hpp \
	$$PWD/dependencies/glm/glm.hpp \
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
	$$PWD/utils/Log.hpp \
	$$PWD/environment/Environment.hpp \
	$$PWD/environment/Screen.hpp \
	$$PWD/environment/Keyboard.hpp \
	$$PWD/environment/Mouse.hpp \
	$$PWD/environment/StartingConfig.hpp \
	$$PWD/geometry/Collision.hpp \
	$$PWD/geometry/Ray.hpp \
    VBE/dependencies/stb_image/stb_image.hpp \
    VBE/geometry/Sphere.hpp \
    VBE/graphics/RenderState.hpp \
    VBE/graphics/TextureCubemap.hpp \
    VBE/graphics/RenderBuffer.hpp \
    VBE/utils/InputStream.hpp \
    VBE/utils/NonCopyable.hpp

