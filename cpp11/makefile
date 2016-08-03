CXX=g++
CXXFLAGS=-std=c++14 -g -m32 -fno-stack-protector -g
vt1: vt1.o
	$(CXX) $(CXXFLAGS) -o $@ $<
vt1.o: vt1.cpp
	$(CXX) $(CXXFLAGS) -g -c $<

t: t.o
	$(CXX) $(CXXFLAGS) -o $@ $<
t.o: t.cpp
	$(CXX) $(CXXFLAGS) -g -c $<

vt: vt.o
	$(CXX) $(CXXFLAGS) -o $@ $<
vt.o: vt.cpp
	$(CXX) $(CXXFLAGS) -g -c $<


clean:
	rm *.o t vt
