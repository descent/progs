main.out: main.o map.o
	g++ main.o map.o -o main.out

main.o: main.c
	gcc -c main.c -o main.o

map.o: map.cpp
	g++ -c map.cpp -o map.o

clean:
	rm -f *.o *.out
