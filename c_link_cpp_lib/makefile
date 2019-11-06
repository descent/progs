CC=gcc
CXX=g++
AR=ar

m: m.o libt.a
	$(CC) -o $@ $^ -lstdc++
m.o: m.c 
	$(CC) -c $< 

libt.a: t.o cpp_interface.o
	$(AR) rcs $@ $^

cpp_interface.o: cpp_interface.c
	$(CXX) -c $<

t.o: t.cpp
	$(CXX) -c $<

clean:
	rm -rf *.o
distclean:
	make clean
	rm libt.a m
