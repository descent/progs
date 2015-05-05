main: db_object.o main.o object.o
	g++ -o $@ $^
db_object.o: db_object.cpp  
	g++ -c $<
main.o: main.cpp  
	g++ -c $<
object.o: object.cpp  object.h
	g++ -c $<
clean:
	rm -rf *.o main
