# make co X64=1 for X64

CC=gcc
CFLAGS=-g

CO_OBJS = co.o
ifdef X64
CFLAGS += -DX64
TARGET = co.64
else
CFLAGS += -m32
CO_OBJS += my_setjmp.o
TARGET = co.32
endif

#CFLAGS=-g
co: $(CO_OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $^
co.o: co.c
	$(CC) $(CFLAGS) -c $<
my_setjmp.o: my_setjmp.S my_setjmp.h
	$(CC) $(CFLAGS) -c $<
co_test: co_test.o gcc/coroutine.o
	$(CC) $(CFLAGS) -o $@ $^

co_test.o: co_test.cpp
	$(CC) $(CFLAGS) -c $<
gcc/coroutine.o:
	(cd gcc; make)
clean:
	rm -rf *.o co_test co.32 co.64
	cd gcc; make clean
