CC=gcc
CXX=g++
CXXFLAGS=-std=c++11 -g
ret_struct: ret_struct.cpp
	g++ -m32 -fno-stack-protector -g -o $@ $<

ret_struct_c: ret_struct.c
	gcc -m32 -fno-stack-protector -g -o $@ $<

mbytes: mbytes.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
ret_func: ret_func.cpp
	g++ -g -o $@ $<

get_prime: get_prime.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

cidr: cidr.cpp
	$(CXX) -g $< -o $@

recursive_call_back: recursive_call_back.o
	$(CXX) -std=c++11 -o $@ -g $<
recursive_call_back.o: recursive_call_back.cpp
	$(CXX) -std=c++11 -c -g $<
ftoa: ftoa.cpp
	g++ -g -o ftoa ftoa.cpp

ptrptr: ptrptr.c
	gcc -g -m32 ptrptr.c -o ptrptr
ma: ma.c
	gcc -g -m32 $< -o $@
ex: ex.c
	gcc -g -m32 $< -o $@
interpositioning: interpositioning.c
	gcc -g -m32 $< -o $@

fill_input_scp: fill_input_scp.o
	$(CXX) -o $@ $< -lutil
fill_input_scp.o: fill_input_scp.cpp
	$(CXX) -c -g $<

http: http.cpp
	$(CXX) -g $< -o $@
im: im.cpp
	$(CXX) -g $< -o $@
input: input.cpp
	$(CXX) -g $< -o $@
clean:
	rm ptrptr
