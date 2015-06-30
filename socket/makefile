getaddrinfo_demo: getaddrinfo_demo.o
	$(CXX) -o $@ $<
getaddrinfo_demo.o: getaddrinfo_demo.cpp
	$(CXX) -c $<
	
all: uds_c uds_s uds_c1 uds_s1
uds_c: uds_c.o
	$(CXX) -o $@ $<
uds_c.o: uds_c.cpp
	$(CXX) -c $<

uds_s: uds_s.o
	$(CXX) -o $@ $<
uds_s.o: uds_s.cpp
	$(CXX) -c $<
uds_c1: uds_c1.o
	$(CXX) -o $@ $<
uds_c1.o: uds_c1.cpp
	$(CXX) -c $<
clean:
	rm -rf *.o uds_c uds_s
