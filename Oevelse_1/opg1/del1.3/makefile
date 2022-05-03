SOURCES=hello.cpp
OBJECTS=${SOURCES:.cpp=.o}
EXECUTABLE=hello 
CXX=g++

${EXECUTABLE}: ${OBJECTS}
	${CXX} -o ${EXECUTABLE} ${OBJECTS}

${OBJECTS}: ${SOURCES}
	${CXX} -c ${SOURCES}


.PHONY: all clean help
all: ${OBJECTS} ${EXECUTABLE}

clean: 
	rm ${EXECUTABLE} ${OBJECTS}

help:
	@echo ${EXECUTABLE} ${OBJECTS} ${SOURCES}