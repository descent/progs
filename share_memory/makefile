CXX=g++

p1: p1.o smem.o
	$(CXX) -o $@ $^
p2: p2.o smem.o
	$(CXX) -o $@ $^

p1.o: p1.cpp 
	$(CXX) -c $<

p2.o: p2.cpp
	$(CXX) -c $<
smem.o: smem.cpp smem.h
	$(CXX) -c $<
clean:
	rm -f *.o p1 p2
