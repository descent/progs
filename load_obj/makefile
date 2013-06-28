CFLAGS=-m32 -std=c99
all: m hello.o
m: main.o 
	gcc -static $(CFLAGS) -o $@ $^
#hello: hello.o
#	gcc -g -o $@ $<

hello.o: hello.c
	gcc $(CFLAGS) -c $<
main.o: main.c
	gcc -g $(CFLAGS) -c $<
clean:
	rm -rf *.o
