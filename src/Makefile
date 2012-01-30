include ../Makefile.rules

SRC= Vector3D.cc \
    TextureManager.cc \
    Scene.cc \
    main.cc \
    GLUtils.cc \
    FreeFlyCamera.cc \
    Map.cc \
    MapWriter.cc \
    Drawer.cc \
    ImageFile.cc \
    Opengl.cc

HEADER= \
    Vector3D.hh \
    TextureManager.hh \
    Singleton.hxx \
    Singleton.hh \
    Scene.hh \
    GLUtils.hh \
    FreeFlyCamera.hh \
    Block.hh \
    Map.hh \
    MapWriter.hh \
    SolTriangle.hh \
    Drawer.hh \
    ImageFile.hh \
    Core/Container3D.hh \
    Core/ListContainer3D.hh \
    Core/ListContainer3D.hxx \
    Opengl.hh

TARGET=../$(EXE)

OBJ=$(SRC:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJ) Makefile.deps
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJ) -o $(TARGET)

%o: %cpp
	$(CXX) -o $@ -c $<

Makefile.deps: $(SRC) $(HEADER)
	$(CXX) -MM $(CXXFLAGS) $(SRC) > Makefile.deps

clean:
	rm -f *.o *.~ *.core *.Dstore *.log *.ml *.err *\#*

distclean:
	rm -f $(EXE)
	rm -f Makefile.deps Makefile.rules

-include Makefile.deps
