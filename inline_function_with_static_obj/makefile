CC=gcc
CXX=g++

m: m1.o m.o a.o
	$(CXX) -o $@ $^
x: x.o y.o
	$(CXX) -o $@ $^

a.o: a.cpp  
	$(CXX) -c $<
m1.o: m1.cpp a.h
	$(CXX) -c $<
m.o: m.cpp a.h
	$(CXX) -c $<

x.o: x.c  
	$(CC) -c $<
y.o: y.c
	$(CC) -c $<

clean:
	rm x m *.o
