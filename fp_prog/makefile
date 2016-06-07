CXXFLAGS=-g -std=c++11
palindrome: palindrome.o
	$(CXX) $(CXXFLAGS) -o $@ $<
palindrome.o: palindrome.cpp
	$(CXX) $(CXXFLAGS) -c $<

fact: fact.o
	$(CXX) $(CXXFLAGS) -o $@ $<
fact.o: fact.cpp
	$(CXX) $(CXXFLAGS) -c $<
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
