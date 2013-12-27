FT2_CFLAGS=`freetype-config --cflags`
FT2_LIBS=`freetype-config --libs`
CXXFLAGS=-g -std=c++11
main: main.o graphic.o
	g++ -o main $^ $(CXXFLAGS) $(FT2_LIBS) -lvgagl -lvga
	#g++ -m64 -Wl,-O1 -Wl,-rpath,/usr/local/Trolltech/Qt-4.8.3/lib -o main main.o    -L/usr/local/Trolltech/Qt-4.8.3/lib -lQtGui -L/usr/local/Trolltech/Qt-4.8.3/lib -L/usr/X11R6/lib64 -lQtCore -lpthread 

%.o: %.cpp
	g++ $(CXXFLAGS) $(FT2_CFLAGS) -Wall -W -I. -c $<

clean:
	rm -rf *.o main