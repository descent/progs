# make CC=arm-linux-gnueabihf-gcc TEST_P=1 && cp spinlock ~/www/  
# make CC=arm-linux-gnueabihf-gcc TEST_P=1 && cp spinlock.pthread ~/www/ 
CC=gcc
BIN=spinlock

CFLAGS += -g
ifdef TEST
CFLAGS += -DTEST 
endif

ifdef TEST_P
CFLAGS += -DTEST -DPTHREAD_FUNC
BIN=spinlock.pthread
endif

all: $(BIN)

$(BIN): spinlock.o
	$(CC) $(CFLAGS) -o $@ $< -lpthread

spinlock.o: spinlock.c spinlock.h
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf *.o spinlock
