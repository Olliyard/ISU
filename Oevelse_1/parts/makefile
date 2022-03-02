SOURCES :=${wildcard *.cpp}
OBJECTS :=${patsubst %.cpp,%.o, ${SOURCES}}
EXECUTABLE=main
CXX=g++
format: $(SOURCES:.cpp=.format)
%.format: %.cpp
	@echo "Formatting file '$<'"...
	@clang-format -i $<
	@echo "" > $@

${EXECUTABLE}: main.o part1.o part2.o
	${CXX} -o ${EXECUTABLE} ${OBJECTS}

${OBJECTS}: ${SOURCES}
	${CXX} -c ${SOURCES}
	
.PHONY: all clean help
all: ${OBJECTS} ${EXECUTABLE}

clean: 
	rm ${OBJECTS}

help:
	@echo cpp files used ${EXECUTABLE} *.cpp