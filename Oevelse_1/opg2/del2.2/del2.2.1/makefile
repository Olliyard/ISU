# variables:
COMP=g++
EXEC=parts

# compilse all targets
all : part1.cpp part2.cpp part1.o part2.o main.o ${EXEC}

# compile main file (parts)
${EXEC} : main.o part1.o part2.o
	${COMP} -o ${EXEC} main.o part1.o part2.o

#compile part1 object-file
part1.o : part1.cpp
	${COMP} -c part1.cpp

#compile part2 object-file
part2.o : part2.cpp
	${COMP} -c part2.cpp

#compile main object-file
main.o : main.cpp
	${COMP} -c main.cpp

# clean all targets (delete files)
clean :
	rm main.o part1.o part2.o ${EXEC}
	
# help
help :
	@echo cpp files used:	*.cpp