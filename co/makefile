CC=gcc
co_test: co_test.o gcc/coroutine.o
	$(CC) -m32 -g -o $@ $^

co_test.o: co_test.cpp
	$(CC) -m32 -g -c $<
clean:
	rm -rf *.o co_test
