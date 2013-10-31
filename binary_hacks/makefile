CC=gcc
ptrptr: ptrptr.c
	gcc -g -m32 ptrptr.c -o ptrptr
ma: ma.c
	gcc -g -m32 $< -o $@
interpositioning: interpositioning.c
	gcc -g -m32 $< -o $@

fill_input_scp: fill_input_scp.o
	$(CXX) -o $@ $< -lutil
fill_input_scp.o: fill_input_scp.cpp
	$(CXX) -c -g $<

92: 92.o
	$(CC) -g -o $@ $<
92.o: 92.c
	$(CC) -g -c $<

clean:
	rm -rf *.o
