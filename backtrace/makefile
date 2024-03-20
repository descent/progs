t2: t2.o
	gcc -static -Wall -save-temps -g -no-pie t2.o -o t2
t2.o: t2.c
	gcc -static -Wall -save-temps -c -g -no-pie t2.c

clean:
	rm -rf *.o *.i *.s t2
