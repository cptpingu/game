TEMPLATE = app
CONFIG += console
CONFIG -= qt

DESTDIR = .

SOURCES += \
    src/Core/Vector3D.cc \
    src/TextureManager.cc \
    src/main.cc \
    src/GLUtils.cc \
    src/Map.cc \
    src/Drawer.cc \
    src/ImageFile.cc \
    src/Opengl.cc \
    src/Game.cc \
    src/Architecte.cc \
    src/Chunk.cc \
    src/Core/Random.cc \
    src/SDL/SavePng.cc \
    src/ShadersManager.cc \
    src/Block/Basic.cc \
    src/Block/Cube.cc \
    src/Block/Triangle.cc \
    src/IdManager.cc \
    src/Camera/BasicCamera.cc \
    src/Camera/FreeFly.cc \
    src/ConfigManager.cc \
    src/InputManager.cc

HEADERS += \
    src/Core/Vector3D.hh \
    src/TextureManager.hh \
    src/Core/Singleton.hxx \
    src/Core/Singleton.hh \
    src/GLUtils.hh \
    src/Map.hh \
    src/Drawer.hh \
    src/ImageFile.hh \
    src/Core/Container3D.hh \
    src/Core/ListContainer3D.hh \
    src/Core/ListContainer3D.hxx \
    src/Opengl.hh \
    src/Core/Traits.hh \
    src/Game.hh \
    src/Architecte.hh \
    src/Chunk.hh \
    src/Core/PairHash.hh \
    src/Core/Random.hh \
    src/SDL/SavePng.hh \
    src/Core/NonCopyable.hh \
    src/Core/Array2D.hh \
    src/Core/Array3D.hh \
    src/ShadersManager.hh \
    src/Core/NumericalContainerHash.hh \
    src/Block/Basic.hh \
    src/Block/Cube.hh \
    src/Block/Triangle.hh \
    src/IdManager.hh \
    src/Camera/BasicCamera.hh \
    src/Camera/FreeFly.hh \
    src/ConfigManager.hh \
    src/InputManager.hh \
    src/Block/NeighbourMatrix.hh

QMAKE_CXXFLAGS += -std=c++0x -Wno-unknown-pragmas -W -Wall
LIBS+= -L$$PWD/../../include/SDL-1.2.14/lib/ -lSDL -lSDL_image -lSDLmain -lopengl32 -lglu32 -lpng12-0

INCLUDEPATH += $$PWD/../../include/SDL-1.2.14/include
DEPENDPATH += $$PWD/../../include/SDL-1.2.14/include
