CC=gcc
CXX=g++
CXXFLAGS=-Wall -DTEST_MAIN -DUSE_OS -std=c++11 -g
avl: avl.o
	$(CXX) $(CXXFLAGS) -o $@ $< 
avl.o: avl.cpp avl.h
	$(CXX) $(CXXFLAGS) -c -g $<
bst: bst.o
	$(CXX) $(CXXFLAGS) -o $@ $< 
bst.o: bst.cpp bst.h
	$(CXX) $(CXXFLAGS) -c -g $<

btree: btree.o
	$(CXX) -o $@ $< 
btree.o: btree.cpp
	$(CXX) -c -g $<
clean:
	rm *.o
