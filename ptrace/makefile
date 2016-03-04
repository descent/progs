all: t p
t: t.o
	gcc -o $@ $<
p: p.o
	gcc -o $@ $<
*.o: *.c
	gcc -c $<
clean:
	rm -rf *.o t p
