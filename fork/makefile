CC=gcc
CXX=g++
CFLAGS=-g
CXXFLAGS=-std=c++11 -g

all: fork_prog keep_port
f: f.c
	gcc -g -fno-pic f.c -o f

fork_prog: fork_prog.o
	$(CXX) $(CFLAGS) -o $@ $< 
fork_prog.o: fork_prog.cpp
	$(CXX) $(CFLAGS) -c $<

keep_port: keep_port.o
	$(CXX) $(CXXFLAGS) -g -o $@ $<
keep_port.o: keep_port.cpp
	$(CXX) $(CFLAGS) -c $<
clean:
	rm *.o
