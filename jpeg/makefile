CXX=g++
fb-jpeg: fb-jpeg.o
	$(CXX) -o $@ $< -ljpeg
fb-jpeg.o: fb-jpeg.cpp
	$(CXX) -c $<

fb-tran: fb-tran.o
	$(CXX) -o $@ $< -ljpeg
fb-tran.o: fb-tran.cpp
	$(CXX) -c $<

clean:
	rm -rf *.o
