TEMPLATE = app
CONFIG += console
CONFIG -= qt

DESTDIR = .

SOURCES += \
    src/Vector3D.cc \
    src/TextureManager.cc \
    src/main.cc \
    src/GLUtils.cc \
    src/FreeFlyCamera.cc \
    src/Map.cc \
    src/MapWriter.cc \
    src/Drawer.cc \
    src/ImageFile.cc \
    src/Opengl.cc \
    src/Game.cc \
    src/Architecte.cc \
    src/Chunk.cc \
    src/Random.cc \
    src/SDL/SavePng.cc

HEADERS += \
    src/Vector3D.hh \
    src/TextureManager.hh \
    src/Singleton.hxx \
    src/Singleton.hh \
    src/GLUtils.hh \
    src/FreeFlyCamera.hh \
    src/Block.hh \
    src/Map.hh \
    src/MapWriter.hh \
    src/SolTriangle.hh \
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
    src/Random.hh \
    src/SDL/SavePng.hh \
    src/Core/NonCopyable.hh \
    src/Core/Array2D.hh

QMAKE_CXXFLAGS += -std=c++0x -Wno-unknown-pragmas
LIBS+= -L$$PWD/../../include/SDL-1.2.14/lib/ -lSDL -lSDL_image -lSDLmain -lopengl32 -lglu32 -lpng12-0

INCLUDEPATH += $$PWD/../../include/SDL-1.2.14/include
DEPENDPATH += $$PWD/../../include/SDL-1.2.14/include
