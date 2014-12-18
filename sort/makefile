%.o : %.cpp
	g++ $(CFLAGS) -c $< 

use_c_qsort: use_c_qsort.o
	g++ -o $@ $<
sort: sort.o
	g++ -o $@ $<
clean:
	rm -rf *.o sort use_c_qsort
