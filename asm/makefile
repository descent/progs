m: m.o f.o
	gcc -m32 -o m m.o f.o
m.o: m.s
	as -o m.o m.s 
f.o: f.c
	gcc -m32 -c f.c 
clean:
	rm -rf *.o m
