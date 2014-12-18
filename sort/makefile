%.o : %.cpp
	g++ $(CFLAGS) -c $< 

bubble_sort: bubble_sort.o
	g++ -o $@ $<
clean:
	rm -rf *.o bubble_sort
