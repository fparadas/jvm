 
CC=g++
CFLAGS= -g -ansi -I. -UDEBUG
DEPS = src/types/access.h src/types/attribute_info.h src/types/constant_info.h src/types/dotclass.h src/types/field_info.h src/types/method_info.h src/getter.h src/printer.h src/reader.h src/utils.h
OBJ = access.o attribute_info.o constant_info.o dotclass.o field_info.o method_info.o getter.o printer.o reader.o utils.o
MAINSRC = main.cpp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: main.out

main.out: $(OBJ)
	$(CC) -o $@ $(MAINSRC) $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.out *.o *.exe