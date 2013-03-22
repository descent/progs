m: m.o
	gcc -o $@ $< libt.a

libt.a: l1.o l2.o
	ar rcs $@  $^
m.o: m.c l1.h l2.h
	gcc -c $<

l1.o: l1.c l1.h
	gcc -c $<
l2.o: l2.c l2.h
	gcc -c $<
clean:
	rm -rf *.o m
