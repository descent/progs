m: m.o libt.a
	gcc -o $@ $^

libt.a: l1.o l2.o
	ar rcs $@  $^
m.o: m.c l1.h l2.h
	gcc -g -c $<

l1.o: l1.c l1.h
	gcc -g -c $<
l2.o: l2.c l2.h
	gcc -g -c $<
clean:
	rm -rf *.o m libt.a
