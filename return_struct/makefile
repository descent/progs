#CXXFLAGS=-g -m32
CXXFLAGS=
all: rs_cpp_ctor rs_cpp rs
rs_cpp_ctor: rs_cpp_ctor.cpp
	g++ $(CXXFLAGS) $< -o $@
rs_cpp: rs_cpp.cpp
	g++ $(CXXFLAGS) $< -o $@
rs: rs.c
	gcc $(CXXFLAGS) $< -o $@
clean:
	rm *.o rs rs_cpp  rs_cpp_ctor
