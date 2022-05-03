# variables:
COMP=g++
EXEC=parts

# get list of all CPP-files
CPPFILES := $(wildcard *.cpp)

# get list af all O-files (object-files)
OBJECTS := $(patsubst %.cpp,%.o,$(CPPFILES))

# compilse all targets
all : ${CPPFILES} ${OBJECTS} ${EXEC}

# compile main file from o files (parts)
${EXEC} : ${OBJECTS}
	${COMP} -o ${EXEC} ${OBJECTS}
	
# compile cpp file (parts)
${OBJECTS} : ${CPPFILES}
	${COMP} -c ${CPPFILES}	

# clean all targets (delete files)
clean :
	rm ${OBJECTS} ${EXEC}
	
# help
help :
	@echo cpp files used:	*.cpp
	
