CXXFLAGS=-g
reverse_str: reverse_str.o
	$(CXX) $(CXXFLAGS) -o $@ $<
reverse_str.o: reverse_str.cpp
	$(CXX) $(CXXFLAGS) -c $<
99: 99.o
	$(CXX) $(CXXFLAGS) -o $@ $<
99.o: 99.cpp
	$(CXX) $(CXXFLAGS) -c $<
clean:
	rm -rf *.o 99 reverse_str
