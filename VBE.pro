TEMPLATE = app
CONFIG -= qt
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGL
INCLUDEPATH += $$PWD/
QMAKE_CXXFLAGS += -std=c++11 -O3
SOURCES += \
    $$PWD/main.cpp \
    $$PWD/Game.cpp \
    $$PWD/tools.cpp \
    $$PWD/Scene.cpp \
    $$PWD/RenderState.cpp \
    $$PWD/graphics/FontManager.cpp \
    $$PWD/graphics/Texture.cpp \
    $$PWD/graphics/TextureManager.cpp \
    $$PWD/graphics/Shader.cpp \
    $$PWD/graphics/ShaderProgram.cpp \
    $$PWD/audio/AudioManager.cpp \
    $$PWD/audio/Effect.cpp \
    $$PWD/audio/Music.cpp \
    $$PWD/input/InputManager.cpp \
    $$PWD/SceneMain/SceneMain.cpp \
    $$PWD/SceneMain/GameObject.cpp \
    SceneMain/TriangleObject.cpp

HEADERS += \
    $$PWD/Scene.hpp \
    $$PWD/Game.hpp \
    $$PWD/tools.hpp \
    $$PWD/RenderState.hpp \
    $$PWD/graphics/FontManager.hpp \
    $$PWD/graphics/Texture.hpp \
    $$PWD/graphics/TextureManager.hpp \
    $$PWD/graphics/Shader.hpp \
    $$PWD/graphics/ShaderProgram.hpp \
    $$PWD/audio/AudioManager.hpp \
    $$PWD/audio/Effect.hpp \
    $$PWD/audio/Music.hpp \
    $$PWD/input/InputManager.hpp \
    $$PWD/SceneMain/SceneMain.hpp \
    $$PWD/SceneMain/GameObject.hpp \
    $$PWD/glm/*.hpp \
    SceneMain/TriangleObject.hpp

OTHER_FILES += \
    $$PWD/shaders/sample.vert \
    $$PWD/shaders/sample.frag
