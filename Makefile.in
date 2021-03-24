# Name of the project
PROJ_NAME=JVM
 
# .c files
C_SOURCE=$(wildcard ./src/cpp/*.cpp)
 
# .h files
H_SOURCE=$(wildcard ./src/h/*.h)
 
# Object files
OBJ=$(subst .cpp,.exe,$(subst src,objects,$(C_SOURCE)))
 
# Compiler and linker
CC=g++
 
# Flags for compiler
CC_FLAGS=-W         \
         -Wall      \
         -ansi      \
         -pedantic	\
		 -std=c++11
 
# Command used at clean target
RM = del
 
#
# Compilation and linking
#
all: 
	@ ${CC} $(CC_FLAGS) src/cpp/*.cpp src/h/*.h -o $(PROJ_NAME).exe

clean:
	@ $(RM) $(PROJ_NAME).exe
 
.PHONY: all clean