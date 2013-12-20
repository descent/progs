CXX=g++
CXXFLAGS=-std=c++11
TARGET=bn
bn: bn.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<
clean:
	rm -rf *.o $(TARGET)
