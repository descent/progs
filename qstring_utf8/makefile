FT2_CFLAGS=`freetype-config --cflags`
FT2_LIBS=`freetype-config --libs`
QTDIR=/usr/share/qt4/
CXXFLAGS=-g
main: main.o graphic.o
	g++ -o main $^ $(CXXFLAGS) -L$(QTDIR)/lib -lQtCore $(FT2_LIBS) -lvgagl -lvga
	#g++ -m64 -Wl,-O1 -Wl,-rpath,/usr/local/Trolltech/Qt-4.8.3/lib -o main main.o    -L/usr/local/Trolltech/Qt-4.8.3/lib -lQtGui -L/usr/local/Trolltech/Qt-4.8.3/lib -L/usr/X11R6/lib64 -lQtCore -lpthread 

%.o: %.cpp
	g++ $(CXXFLAGS) $(FT2_CFLAGS) -Wall -W -D_REENTRANT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED -I$(QTDIR)/include/QtCore -I$(QTDIR)/include -I. -c $<

clean:
	rm -rf *.o main
