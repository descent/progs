co_test: co_test.o gcc/coroutine.o
	$(CC) -o $@ $^

co_test.o: co_test.cpp
	$(CC) -c $<
clean:
	rm -rf *.o co_test
