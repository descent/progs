ret_func: ret_func.cpp
	g++ -g -o $@ $<

get_prime: get_prime.cpp
	g++ -g -o $@ $<

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
