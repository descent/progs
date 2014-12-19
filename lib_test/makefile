%.o : %.cpp
	g++ $(CFLAGS) -c $< 
%.o : %.c
	gcc $(CFLAGS) -c $< 
m1:m1.o libf.a
	g++ -o $@ $^

m:m.o libf.a
	gcc -o $@ $^
libf.a: f1.o
	ar rcs $@ $^

sort: sort.o
	g++ -o $@ $<
use_c_qsort: use_c_qsort.o
	g++ -o $@ $<
clean:
	rm -rf *.o sort use_c_qsort
