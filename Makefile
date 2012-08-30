main.out: main.o map.o
	gcc main.o map.o -o main.out -lstdc++

main.o: main.c
	gcc -c main.c -o main.o

map.o: map.cpp
	g++ -c map.cpp -o map.o

clean:
	rm -f *.o *.out
