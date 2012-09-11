include ../rule.mk

main: main.o console.o
	$(CC) -o $@ $^
sources = console.c main.c
include $(sources:.c=.d)

clean:
	rm -rf *.o
