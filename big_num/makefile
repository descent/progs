CXX=g++
CXXFLAGS=-std=c++11
TARGET=bn
bn: bn.o guint.o
	$(CXX) $(CXXFLAGS) -o $@ $^

bn.o: bn.cpp guint.h
	$(CXX) $(CXXFLAGS) -c $<

guint.o: guint.cpp guint.h
	$(CXX) $(CXXFLAGS) -c $<
#%.o: %.cpp
#	$(CXX) $(CXXFLAGS) -c $<
clean:
	rm -rf *.o $(TARGET)
