CC=gcc

list: list.o
	$(CC) -o $@ $< 
list.o: list.c
	$(CC) -c -g $<
clean:
	rm *.o
