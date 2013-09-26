CC=gcc
CFLAGS=-m32 -g
all: t0 t1
%o: %S
	$(CC) $(CFLAGS) -c $<
%o: %c
	$(CC) $(CFLAGS) -c $<
t0: t0.o 
	$(CC) $(CFLAGS) -o $@ $^
t1: t1.o my_setjmp.o
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -rf *.html *.o t0 t1
