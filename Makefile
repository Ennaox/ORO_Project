CFLAGS= -O3 -g -mavx2

SOURCES=src/main.c src/lifo.c src/tree.c
OBJECTS=$(SOURCES:src/.c=build/.o)

all: main

exe: main
	./main config.txt

build/%.o: %.c
	gcc ${CFLAGS} -c -o $@ $<

main: ${OBJECTS}
	gcc $^ ${CFLAGS} -o $@


clean:
	rm -f build/* main
