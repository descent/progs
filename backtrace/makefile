CC=gcc
CFLAGS=-static -Wall -save-temps -g -no-pie
t1: t1.o
	gcc -D_GNU_SOURCE $(CFLAGS) $< -o $@ -pthread
t1.o: t1.c
	gcc -D_GNU_SOURCE $(CFLAGS) -c $<
t2: t2.o
	gcc $(CFLAGS) $< -o $@
t2.o: t2.c
	gcc $(CFLAGS) -c $<
u1: u1.o
	gcc $(CFLAGS) $< -o $@ -lunwind -llzma
u1.o: u1.c
	gcc $(CFLAGS) -c $<

t22: t22.o
	gcc $(CFLAGS) $< -o $@
t22.o: t22.c
	gcc $(CFLAGS) -c $<

clean:
	rm -rf *.o *.i *.s t2
