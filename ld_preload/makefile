all: t1 my_del.so
t1: t1.cpp
	g++ -o $@ $<
my_del.so: my_del.cpp
	g++ my_del.cpp -fPIC -shared -o my_del.so
clean:
	rm -rf *.o t1 my_del.so
