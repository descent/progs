CXXFLAGS=-g -std=c++11
lexer: lexer.o
	$(CXX) $(CXXFLAGS) -o $@ $<
lexer.o: lexer.cpp
	$(CXX) $(CXXFLAGS) -c $<
clean:
	rm lexer *.o
