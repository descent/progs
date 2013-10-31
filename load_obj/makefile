CFLAGS=-m32 -std=c99
all: m hello.o
m: main.o 
	gcc -static $(CFLAGS) -o $@ $^
#hello: hello.o
#	gcc -g -o $@ $<

hello.o: hello.c
	gcc $(CFLAGS) -c $<

main.o: main.c type.h elf.h mype.h
	gcc -g $(CFLAGS) -c $<

mh: mh.o hello.pic.o
	gcc -m32 -o $@ $^
mh.o: mh.c
	gcc -m32 -c mh.c 

hello.pic.o: hello.c
	gcc -m32 -fPIC -c hello.c -o $@


clean:
	rm -rf *.o
