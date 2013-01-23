ptrptr: ptrptr.c
	gcc -g -m32 ptrptr.c -o ptrptr
ma: ma.c
	gcc -g -m32 $< -o $@
interpositioning: interpositioning.c
	gcc -g -m32 $< -o $@
clean:
	rm ptrptr
