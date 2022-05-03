# variables:
COMPILER=g++
EXECUTABLE=hello

# make files in order from left --->
all: hello.o ${EXECUTABLE}

# make "hello" executable (linker)
${EXECUTABLE} : hello.o
	${COMPILER} -o ${EXECUTABLE} hello.o

# make "hello.o" file (compile)
hello.o : hello.cpp
	${COMPILER} -c hello.cpp

# clean build (delete executable and object files)
clean : 
	rm ${EXECUTABLE} hello.o

help :
	$@ 