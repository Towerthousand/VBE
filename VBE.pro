QT       -= core gui

TARGET = VBE
TEMPLATE = lib
CONFIG += staticlib

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += include src

#__DEBUG will make asserts on all risky operations, and will output a detailed error message if it fails
#__LOG will output all VBE_LOG(..). This is general (important) info such as resource loading, etc
#__DLOG will output all VBE_DLOG(..). This is detailed log info, use it for debugging.
# Disable all three for faster internets

include(../common.pri)

OTHER_FILES += \
    doxygenconfig \
    VBE.pri

HEADERS += \
    include/VBE/config.hpp \
    include/VBE/geometry.hpp \
    include/VBE/graphics.hpp \
    include/VBE/math.hpp \
    include/VBE/scenegraph.hpp \
    include/VBE/system.hpp \
    include/VBE/VBE.hpp \
    include/VBE/utils/NonCopyable.hpp \
    include/VBE/system/ContextSettings.hpp \
    include/VBE/system/Keyboard.hpp \
    include/VBE/system/Log.hpp \
    include/VBE/system/Mouse.hpp \
    include/VBE/scenegraph/Camera.hpp \
    include/VBE/scenegraph/ContainerObject.hpp \
    include/VBE/scenegraph/Game.hpp \
    include/VBE/scenegraph/GameObject.hpp \
    include/VBE/graphics/OBJLoader.hpp \
    include/VBE/graphics/OpenGL.hpp \
    include/VBE/graphics/RenderBuffer.hpp \
    include/VBE/graphics/RenderTarget.hpp \
    include/VBE/graphics/Shader.hpp \
    include/VBE/graphics/ShaderProgram.hpp \
    include/VBE/graphics/Texture.hpp \
    include/VBE/graphics/Texture2D.hpp \
    include/VBE/graphics/Texture2DArray.hpp \
    include/VBE/graphics/Texture3D.hpp \
    include/VBE/graphics/TextureCubemap.hpp \
    include/VBE/graphics/TextureFormat.hpp \
    include/VBE/graphics/Uniform.hpp \
    include/VBE/graphics/Vertex.hpp \
    include/VBE/geometry/AABB.hpp \
    include/VBE/geometry/Collision.hpp \
    include/VBE/geometry/Frustum.hpp \
    include/VBE/geometry/Plane.hpp \
    include/VBE/geometry/Ray.hpp \
    include/VBE/geometry/Sphere.hpp \
    include/VBE/dependencies/glm/glm.hpp \
    src/VBE/graphics/ShaderBinding.hpp \
    src/VBE/dependencies/stb_image/stb_image.hpp \
    include/VBE/system/Clock.hpp \
    src/VBE/system/sdl2/ClockImpl.hpp \
    src/VBE/system/ClockImpl.hpp \
    src/VBE/system/InputImpl.hpp \
    src/VBE/system/sdl2/InputImpl.hpp \
    src/VBE/system/sdl2/sdl2.hpp \
    include/VBE/system/Window.hpp \
    src/VBE/system/WindowImpl.hpp \
    src/VBE/system/sdl2/WindowImpl.hpp \
    include/VBE/system/Storage.hpp \
    src/VBE/system/StorageImpl.hpp \
    src/VBE/system/sdl2/StorageImpl.hpp \
    include/VBE/graphics/Mesh.hpp \
    include/VBE/graphics/MeshBase.hpp \
    include/VBE/graphics/MeshIndexed.hpp

SOURCES += \
    src/VBE/dependencies/stb_image/stb_image.cpp \
    src/VBE/geometry/AABB.cpp \
    src/VBE/geometry/Collision.cpp \
    src/VBE/geometry/Frustum.cpp \
    src/VBE/geometry/Plane.cpp \
    src/VBE/graphics/Mesh.cpp \
    src/VBE/graphics/OBJLoader.cpp \
    src/VBE/graphics/RenderBuffer.cpp \
    src/VBE/graphics/RenderTarget.cpp \
    src/VBE/graphics/Shader.cpp \
    src/VBE/graphics/ShaderBinding.cpp \
    src/VBE/graphics/ShaderProgram.cpp \
    src/VBE/graphics/Texture.cpp \
    src/VBE/graphics/Texture2D.cpp \
    src/VBE/graphics/Texture2DArray.cpp \
    src/VBE/graphics/Texture3D.cpp \
    src/VBE/graphics/TextureCubemap.cpp \
    src/VBE/graphics/Uniform.cpp \
    src/VBE/graphics/Vertex.cpp \
    src/VBE/scenegraph/Camera.cpp \
    src/VBE/scenegraph/ContainerObject.cpp \
    src/VBE/scenegraph/Game.cpp \
    src/VBE/scenegraph/GameObject.cpp \
    src/VBE/system/Log.cpp \
    src/VBE/system/Mouse.cpp \
    src/VBE/system/Keyboard.cpp \
    src/VBE/system/Clock.cpp \
    src/VBE/system/sdl2/ClockImpl.cpp \
    src/VBE/system/sdl2/InputImpl.cpp \
    src/VBE/system/Window.cpp \
    src/VBE/system/sdl2/WindowImpl.cpp \
    src/VBE/system/sdl2/StorageImpl.cpp \
    src/VBE/system/Storage.cpp \
    src/VBE/graphics/MeshBase.cpp \
    src/VBE/graphics/MeshIndexed.cpp
