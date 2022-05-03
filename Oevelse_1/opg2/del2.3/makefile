# name of executable
EXE = prog

# list of objects
OBJECTS = server.o data.o connection.o

# $@ = $(EXE) = target
# $^ = $(OBJECTS) = prerequisities
# $(CXX) = implicit variale: compiler (g++ default)
$(EXE) : $(OBJECTS)
	$(CXX) -o $@ $^

clean :
	rm $(OBJECTS)