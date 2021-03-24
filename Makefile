# Name of the project
PROJ_NAME=JVM
 
# .c files
C_SOURCE=$(wildcard ./src/cpp/*.cpp)
 
# .h files
H_SOURCE=$(wildcard ./src/h/*.h)
 
# Object files
OBJ=$(subst .cpp,.o,$(subst src,objects,$(C_SOURCE)))
 
# Compiler and linker
CC=g++
 
# Flags for compiler
CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -ansi      \
         -pedantic	\
		 -std=c++11
 
# Command used at clean target
RM = rm -rf
 
#
# Compilation and linking
#
all: objFolder $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $^ -o $@
	@ echo 'Finished building binary: $@'
	@ echo ' '
 
./objects/cpp/%.o: ./src/cpp/%.cpp ./src/h/%.h
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '
 
./objects/cpp/main.o: ./src/cpp/main.cpp $(H_SOURCE)
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '
 
objFolder:
	@ mkdir -p objects
	@ mkdir -p objects/cpp
 
clean:
	@ $(RM) ./objects/cpp/*.o $(PROJ_NAME) *~
	@ $(RM) objects
 
.PHONY: all clean