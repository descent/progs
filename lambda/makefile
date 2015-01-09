CLANG=1
CXXFLAGS=-g -std=c++11 
CXX=g++

ifdef CLANG
CXX=clang++-3.4
CXXFLAGS+=-stdlib=libc++
endif
fo: fo.o
	$(CXX) -o $@ $^ $(CXXFLAGS)
t: t.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -Wall -W -I. -c $<

clean:
	rm -rf *.o t
