all: uds_c uds_s
uds_c: uds_c.o
	$(CXX) -o $@ $<
uds_c.o: uds_c.cpp
	$(CXX) -c $<

uds_s: uds_s.o
	$(CXX) -o $@ $<
uds_s.o: uds_s.cpp
	$(CXX) -c $<
clean:
	rm -rf *.o uds_c uds_s
