CC=gcc
%o: %c
	$(CC) -c $<
t0: t0.o ceh.o
	$(CC) -o $@ $^
clean:
	rm -rf *.html *.o t0
