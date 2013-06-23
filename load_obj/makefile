m: main.o hello.o
	gcc -o $@ $^
#hello: hello.o
#	gcc -g -o $@ $<

hello.o: hello.c
	gcc -c $<
main.o: main.c
	gcc -g -c $<
clean:
	rm -rf *.o
