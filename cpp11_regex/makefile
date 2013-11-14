CXX=g++
CXXFLAGS=-std=c++11
r: r.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<
clean:
	rm -rf *.o m
