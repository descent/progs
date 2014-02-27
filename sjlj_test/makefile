CFLAGS=-fno-stack-protector -g
TARGET=sjlj sjlj_1 sjlj_2
ALL: $(TARGET)

sjlj: sjlj.o
	gcc -static -o $@ $<
sjlj.o: sjlj.c
	gcc $(CFLAGS) -c $<

sjlj_1: sjlj_1.o
	gcc -static -o $@ $<
sjlj_1.o: sjlj_1.c
	gcc $(CFLAGS) -c $<

sjlj_2: sjlj_2.o
	gcc -static -o $@ $<
sjlj_2.o: sjlj_2.c
	gcc $(CFLAGS) -c $<

clean:
	rm -rf *.o $(TARGET)
