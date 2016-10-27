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

elf_loader: elf_loader.o
	g++ -m32 -g -o $@ $<
elf_loader.o: elf_loader.cpp
	g++ -m32 -g -c $<

el:el.o
	gcc -m32 -o $@ $< -ldl
el.o:el.c
	gcc -m32 -c $<
e: e.o
	gcc -pie -fPIE -m32 -o $@ $<
e.o: e.c
	gcc -pie -fPIE -m32 -c $<

clean:
	rm -rf *.o
