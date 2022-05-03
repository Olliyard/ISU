SOURCES=main.cpp part1.cpp part2.cpp
# add architecture folders to files (build/arch)
OBJECTS=$(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.o))
DEPS=$(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.d))

EXE=prog
CXXFLAGS=-I.
ARCH?=x86-64
# Making for x86-64 e.g. x86-64 (the architecture employed)

# > make ARCH=x86-64
ifeq (${ARCH},x86-64)
CXX=g++
BUILD_DIR=build/x86-64
BIN_DIR=bin/x86-64 # make executalbe folder for x86-64
endif


# Making for architecture
# > make ARCH=arm
ifeq (${ARCH},arm)
CXX=arm-rpizw-g++
BUILD_DIR=build/arm
BIN_DIR=bin/arm # make executalbe folder for arm
endif

$(BIN_DIR)/$(EXE): $(DEPS) $(OBJECTS) # << Check the $(DEPS) new dependency
	$(CXX) $(CXXFLAGS) -o $@/$(EXE) $(OBJECTS)

# make objects in BUILD_DIR
$(BUILD_DIR)/%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Rule that describes how a .d (dependency) file is created from a .cpp file

# Similar to the assigment that you just completed %.cpp -> %.o
$(BUILD_DIR)/%.d: %.cpp
	mkdir  -p $(BUILD_DIR) $(BIN_DIR)
	$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >> $@

ifneq ($(filter-out clean format tidy, $(MAKECMDGOALS)),)
-include $(DEPS)
endif

clean:
	rm -rf build
	rm -rf bin

format: $(SOURCES:.cpp=.format)
%.format: %.cpp
	@echo "Formatting file '$<'"...
	@clang-format -i $<
	@echo "" > $@

tidy: $(SOURCES:.cpp=.tidy)
%.tidy: %.cpp
	@echo "Tidying file '$<'"...
	@clang-tidy $< -- $(CXXFLAGS)
	@echo "" > $@