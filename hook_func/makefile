CC=gcc
CXX=g++
CFLAGS=-g
CXXFLAGS=-std=c++11 -g

hf1: hf1.o
	$(CXX) hf1.o -o hf1 -ldl
hf1.o: hf1.cpp
	$(CXX) -c hf1.cpp 

clean:
	rm *.o
