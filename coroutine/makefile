all: sample

sample: sample.o my_setjmp.o
	gcc -ggdb -o sample sample.c my_setjmp.S

sample.o: sample.c
	gcc -ggdb -c $<

my_setjmp.o: my_setjmp.S
	gcc -ggdb -c $<


clean:
	rm -f sample *.o
