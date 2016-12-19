CXX=g++
CXXFLAGS=-std=c++14 -g  -fno-stack-protector -g -m32
EXEC=vt1 t vt

t1: t1.o
	$(CXX) $(CXXFLAGS) -o $@ $<
t1.o: t1.cpp
	$(CXX) $(CXXFLAGS) -g -c $< -lrt

t2: t2.o
	$(CXX) $(CXXFLAGS) -o $@ $<
t2.o: t2.cpp
	$(CXX) $(CXXFLAGS) -g -c $< -lrt

t: t.o
	$(CXX) $(CXXFLAGS) -o $@ $<
t.o: t.cpp
	$(CXX) $(CXXFLAGS) -g -c $< -lrt

vt: vt.o
	$(CXX) $(CXXFLAGS) -o $@ $<
vt.o: vt.cpp
	$(CXX) $(CXXFLAGS) -g -c $<

vt1: vt1.o
	$(CXX) $(CXXFLAGS) -o $@ $<
vt1.o: vt1.cpp
	$(CXX) $(CXXFLAGS) -g -c $<

clean:
	rm *.o t $(EXEC)
