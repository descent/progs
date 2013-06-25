CFLAGS=-m32 -std=c99
m: main.o hello.o
	gcc $(CFLAGS) -o $@ $^
#hello: hello.o
#	gcc -g -o $@ $<

hello.o: hello.c
	gcc $(CFLAGS) -c $<
main.o: main.c
	gcc $(CFLAGS) -c $<
clean:
	rm -rf *.o
