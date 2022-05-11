CFLAGS= -O3 -g -mavx2

SOURCES=main.c lifo.c tree.c
OBJECTS=$(SOURCES:.c=.o)

all: main

exe: main
	./main config.txt

%.o: %.c
	gcc ${CFLAGS} -c -o $@ $<

main: ${OBJECTS}
	gcc $^ ${CFLAGS} -o $@


clean:
	rm -f *.o main
