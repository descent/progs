CC=gcc
CXX=g++
CXXFLAGS=-std=c++14 -g
#/usr/bin/g++ -std=c++14 cps.cpp -g -o cps
cps: cps.cpp
	$(CXX) -m32 -fno-stack-protector $(CXXFLAGS)  -o $@ $<


clean:
	rm -rf *.o cps
