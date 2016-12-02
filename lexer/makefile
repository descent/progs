lexer_1: lexer_1.o
	$(CXX) $(CXXFLAGS) -o $@ $<
lexer_1.o: lexer_1.cpp
	$(CXX) $(CXXFLAGS) -c $<
CXXFLAGS=-g -std=c++11
lexer: lexer.o
	$(CXX) $(CXXFLAGS) -o $@ $<
lexer.o: lexer.cpp
	$(CXX) $(CXXFLAGS) -c $<
clean:
	rm lexer *.o
