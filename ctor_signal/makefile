CXX=g++
m: m.o c.o
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) -c $<
clean:
	rm -rf *.o m
