FT2_CFLAGS=`freetype-config --cflags`
FT2_LIBS=`freetype-config --libs`
main: main.o
	g++ -m64 -Wl,-O1 -Wl,-rpath,/usr/local/Trolltech/Qt-4.8.3/lib -o main main.o -L/usr/local/Trolltech/Qt-4.8.3/lib -lQtCore $(FT2_LIBS)
	#g++ -m64 -Wl,-O1 -Wl,-rpath,/usr/local/Trolltech/Qt-4.8.3/lib -o main main.o    -L/usr/local/Trolltech/Qt-4.8.3/lib -lQtGui -L/usr/local/Trolltech/Qt-4.8.3/lib -L/usr/X11R6/lib64 -lQtCore -lpthread 

main.o: main.cpp
	g++ $(FT2_CFLAGS) -c -m64 -pipe -O2 -Wall -W -D_REENTRANT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED -I/usr/local/Trolltech/Qt-4.8.3/mkspecs/linux-g++-64 -I. -I/usr/local/Trolltech/Qt-4.8.3/include/QtCore -I/usr/local/Trolltech/Qt-4.8.3/include/QtGui -I/usr/local/Trolltech/Qt-4.8.3/include -I. -o main.o main.cpp

clean:
	rm -rf *.o main
