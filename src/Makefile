include ../Makefile.rules

SRC=	main.cc			\
	FreeFlyCamera.cc        \
	Scene.cc                \
	GLUtils.cc              \
	Vector3D.cc             \
	TextureManager.cc

HEADER= Singleton.hh            \
	Singleton.hxx           \
	FreeFlyCamera.hh        \
	Scene.hh                \
	GLUtils.hh              \
	Vector3D.hh             \
	TextureManager.hh

TARGET=../$(EXE)

OBJ=$(SRC:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJ) Makefile.deps
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJ) -o $(TARGET)

%o: %cpp
	$(CXX) -o $@ -c $<

Makefile.deps: $(SRC) $(HEADER)
	$(CXX) -MM $(SRC) > Makefile.deps

clean:
	rm -f *.o *.~ *.core *.Dstore *.log *.ml *.err *\#*

distclean:
	rm -f $(EXE)
	rm -f Makefile.deps Makefile.rules

-include Makefile.deps
