CXX=g++
#CXXFLAGS=-Wall
CXXFLAGS=

tq: tq.o queue.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -pthread

tq.o: tq.cpp
	$(CXX) $(CXXFLAGS) -c $<
queue.o: queue.cpp queue.h
	$(CXX) $(CXXFLAGS) -c $<


clean:
	rm -rf *.o tq
