FT2_CFLAGS=`freetype-config --cflags`
FT2_LIBS=`freetype-config --libs`
CXXFLAGS=-g -std=c++11
CXX=g++-5

LDFLAGS=

#CLANG=1

# support svgalib
# make SVGA=1
ifdef SVGA
LDFLAGS += -lvgagl -lvga
CXXFLAGS+=-DSVGALIB
endif

ifdef CLANG
CXX=clang++-3.4
CXXFLAGS+=-stdlib=libc++
endif

# link qt command, need not use qt now.
#g++ -m64 -Wl,-O1 -Wl,-rpath,/usr/local/Trolltech/Qt-4.8.3/lib -o main main.o    -L/usr/local/Trolltech/Qt-4.8.3/lib -lQtGui -L/usr/local/Trolltech/Qt-4.8.3/lib -L/usr/X11R6/lib64 -lQtCore -lpthread 

main: main.o graphic.o
	$(CXX) -o main $^ $(CXXFLAGS) $(FT2_LIBS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(FT2_CFLAGS) -Wall -W -I. -c $<

clean:
	rm -rf *.o main
