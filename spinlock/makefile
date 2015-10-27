CC=gcc

ifdef TEST
CFLAGS += -DTEST
endif

spinlock: spinlock.o
	$(CC) $(CFLAGS) -o $@ $< -lpthread

spinlock.o: spinlock.c spinlock.h
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf *.o spinlock
