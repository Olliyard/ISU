# names of cpp files
SOURCES=main.cpp part1.cpp part2.cpp

# objects make from sources:
# in each word ".cpp" is replace by ".o"
OBJECTS=$(SOURCES:.cpp=.o)

# dependencie names made from replacing ".cpp" with ".d"
DEPS=$(SOURCES:.cpp=.d)

# executable name
EXE=prog

# set c++ compiler glas -> -I = abselute-path
CXXFLAGS=-I.

# 
$(EXE): $(DEPS) $(OBJECTS) # << Check the $(DEPS) new dependency
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

# Rule that describes how a .d (dependency) file is created from a .cpp file
# Similar to the assigment that you just completed %.cpp -> %.o
%.d: %.cpp
# writes to file ($@ -> .d files)
# -MM -> first prereq ($<) 
	$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@
# append/write to ($@ -> .d files)
# -MT(change ".d" to ".o")
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >> $@


-include $(DEPS)

clean :
	rm $(DEPS) $(OBJECTS) $(EXE)