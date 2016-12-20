CXX=g++

target = libmylib.so.1.0.0 m

all: $(target)

m: m.o
	$(CXX) -o $@ $< -ldl
m.o: m.cpp
	$(CXX) -c $<

libmylib.so.1.0.0: hello.o
	$(CXX) -shared -Wl,-soname,libmylib.so.1 -o $@ $^
hello.o: hello.cpp hello.h
	$(CXX) -g -fPIC -c $<

clean:
	rm -rf *.o $(target)

