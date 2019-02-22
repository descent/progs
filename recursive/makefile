CC=gcc
CXX=g++
sum: sum.o
	$(CC) -o $@ $<
sum.o: sum.c
	$(CC) -c -g $<

anonymous_func: anonymous_func.o
	$(CXX) -std=c++17 -g $< -o $@
anonymous_func.o: anonymous_func.cpp
	$(CXX) -std=c++17 -c -g $<

clean:
	rm *.o sum
