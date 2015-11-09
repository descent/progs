h: h.c
	gcc -o $@ $<
fill_input_scp: fill_input_scp.o
	$(CXX) -o $@ $< -lutil
fill_input_scp.o: fill_input_scp.cpp
	$(CXX) -c -g $<

fill_input_scp1: fill_input_scp1.o
	$(CXX) -o $@ $< -lutil
fill_input_scp1.o: fill_input_scp1.cpp
	$(CXX) -c -g $<
clean:
	rm -rf *.o
