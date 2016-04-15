lexer: lexer.o
	$(CXX) -std=c++11 -o $@ -g $<
lexer.o: lexer.cpp
	$(CXX) -std=c++11 -c -g $<
clean:
	rm lexer *.o
