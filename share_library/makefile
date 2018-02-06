
main: main.o libmylib.so
	gcc -o $@ main.o ./libmylib.so

main.o: main.c
	gcc -c $<

libmylib.so: libmylib.so.1.0.0
	ln -s libmylib.so.1.0.0 libmylib.so

libmylib.so.1.0.0: libhello.o
	gcc -shared -Wl,-soname,libmylib.so.1 -o libmylib.so.1.0.0  libhello.o

libhello.o: libhello.c
	gcc -c -fPIC libhello.c

clean:
	rm -rf *.o *.so libmylib.so.1.0.0
