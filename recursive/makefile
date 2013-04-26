CC=gcc
sum: sum.o
	$(CC) -o $@ $<
sum.o: sum.c
	$(CC) -c -g $<


clean:
	rm *.o sum
