include ../Makefile.rules

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
