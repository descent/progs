m: main.o hello.o
	gcc -std=c99 -o $@ $^
#hello: hello.o
#	gcc -g -o $@ $<

hello.o: hello.c
	gcc -std=c99 -c $<
main.o: main.c
	gcc -std=c99 -g -c $<
clean:
	rm -rf *.o
