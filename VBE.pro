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
INCLUDEPATH += $$PWD/VBE/include
QMAKE_CXXFLAGS += -std=c++0x

OTHER_FILES += \
    VBE/doxygenconfig

HEADERS += \
    VBE/include/VBE/config.hpp \
    VBE/include/VBE/geometry.hpp \
    VBE/include/VBE/graphics.hpp \
    VBE/include/VBE/math.hpp \
    VBE/include/VBE/scenegraph.hpp \
    VBE/include/VBE/system.hpp \
    VBE/include/VBE/VBE.hpp \
    VBE/include/VBE/utils/Manager.hpp \
    VBE/include/VBE/utils/NonCopyable.hpp \
    VBE/include/VBE/system/ContextSettings.hpp \
    VBE/include/VBE/system/InputStream.hpp \
    VBE/include/VBE/system/Keyboard.hpp \
    VBE/include/VBE/system/Log.hpp \
    VBE/include/VBE/system/Mouse.hpp \
    VBE/include/VBE/system/Screen.hpp \
    VBE/include/VBE/scenegraph/Camera.hpp \
    VBE/include/VBE/scenegraph/ContainerObject.hpp \
    VBE/include/VBE/scenegraph/Game.hpp \
    VBE/include/VBE/scenegraph/GameObject.hpp \
    VBE/include/VBE/graphics/Mesh.hpp \
    VBE/include/VBE/graphics/Model.hpp \
    VBE/include/VBE/graphics/OBJLoader.hpp \
    VBE/include/VBE/graphics/OpenGL.hpp \
    VBE/include/VBE/graphics/RenderBuffer.hpp \
    VBE/include/VBE/graphics/RenderTarget.hpp \
    VBE/include/VBE/graphics/Shader.hpp \
    VBE/include/VBE/graphics/ShaderProgram.hpp \
    VBE/include/VBE/graphics/Texture.hpp \
    VBE/include/VBE/graphics/Texture2D.hpp \
    VBE/include/VBE/graphics/Texture2DArray.hpp \
    VBE/include/VBE/graphics/Texture3D.hpp \
    VBE/include/VBE/graphics/TextureCubemap.hpp \
    VBE/include/VBE/graphics/TextureFormat.hpp \
    VBE/include/VBE/graphics/Uniform.hpp \
    VBE/include/VBE/graphics/Vertex.hpp \
    VBE/include/VBE/geometry/AABB.hpp \
    VBE/include/VBE/geometry/Collision.hpp \
    VBE/include/VBE/geometry/Frustum.hpp \
    VBE/include/VBE/geometry/Plane.hpp \
    VBE/include/VBE/geometry/Ray.hpp \
    VBE/include/VBE/geometry/Sphere.hpp \
    VBE/include/VBE/dependencies/glm/glm.hpp \
    VBE/src/VBE/system/android/ResourceStream.hpp \
    VBE/src/VBE/graphics/ShaderBinding.hpp \
    VBE/src/VBE/dependencies/stb_image/stb_image.hpp

SOURCES += \
    VBE/src/VBE/system/Log.cpp \
    VBE/src/VBE/system/sdl2/Environment.cpp \
    VBE/src/VBE/system/sdl2/Keyboard.cpp \
    VBE/src/VBE/system/sdl2/Mouse.cpp \
    VBE/src/VBE/system/sdl2/Screen.cpp \
    VBE/src/VBE/system/android/ResourceStream.cpp \
    VBE/src/VBE/scenegraph/Camera.cpp \
    VBE/src/VBE/scenegraph/ContainerObject.cpp \
    VBE/src/VBE/scenegraph/Game.cpp \
    VBE/src/VBE/scenegraph/GameObject.cpp \
    VBE/src/VBE/graphics/Mesh.cpp \
    VBE/src/VBE/graphics/Model.cpp \
    VBE/src/VBE/graphics/OBJLoader.cpp \
    VBE/src/VBE/graphics/RenderBuffer.cpp \
    VBE/src/VBE/graphics/RenderTarget.cpp \
    VBE/src/VBE/graphics/Shader.cpp \
    VBE/src/VBE/graphics/ShaderBinding.cpp \
    VBE/src/VBE/graphics/ShaderProgram.cpp \
    VBE/src/VBE/graphics/Texture.cpp \
    VBE/src/VBE/graphics/Texture2D.cpp \
    VBE/src/VBE/graphics/Texture2DArray.cpp \
    VBE/src/VBE/graphics/Texture3D.cpp \
    VBE/src/VBE/graphics/TextureCubemap.cpp \
    VBE/src/VBE/graphics/Uniform.cpp \
    VBE/src/VBE/graphics/Vertex.cpp \
    VBE/src/VBE/geometry/AABB.cpp \
    VBE/src/VBE/geometry/Collision.cpp \
    VBE/src/VBE/geometry/Frustum.cpp \
    VBE/src/VBE/geometry/Plane.cpp \
    VBE/src/VBE/geometry/Sphere.cpp \
    VBE/src/VBE/dependencies/stb_image/stb_image.cpp
