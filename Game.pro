TEMPLATE = app
CONFIG += console
CONFIG -= qt

DESTDIR = .

SOURCES += \
    src/Vector3D.cc \
    src/TextureManager.cc \
    src/Scene.cc \
    src/main.cc \
    src/GLUtils.cc \
    src/FreeFlyCamera.cc \
    src/block.cpp \
    src/map.cpp \
    src/LecteurMap.cpp

HEADERS += \
    src/Vector3D.hh \
    src/TextureManager.hh \
    src/Singleton.hxx \
    src/Singleton.hh \
    src/Scene.hh \
    src/GLUtils.hh \
    src/FreeFlyCamera.hh \
    src/block.h \
    src/map.h


LIBS+= -L$$PWD/../../include/SDL-1.2.14/lib/ -lSDL -lSDL_image -lSDLmain -lopengl32 -lglu32 -lglut

INCLUDEPATH += $$PWD/../../include/SDL-1.2.14/include
DEPENDPATH += $$PWD/../../include/SDL-1.2.14/include