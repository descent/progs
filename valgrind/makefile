CFLAGS=-g
v1: v1.o
	gcc $(CFLAGS) -o $@ $<
v1.o: v1.c
	gcc $(CFLAGS) -c $<
clean:
	rm -rf *.o
