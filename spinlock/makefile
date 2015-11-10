# make CC=arm-linux-gnueabihf-gcc TEST_P=1 && cp spinlock ~/www/  
# make CC=arm-linux-gnueabihf-gcc TEST_P=1 && cp spinlock.pthread ~/www/ 
# I test in RPI2
CC=gcc
BIN=spinlock

CFLAGS += -g -march=armv7-a -mtune=cortex-a7 
ifdef TEST
CFLAGS += -DTEST 
endif

ifdef TEST_P
CFLAGS += -DTEST -DPTHREAD_FUNC
BIN=spinlock.pthread
endif

all: $(BIN) check_result

$(BIN): spinlock.o
	$(CC) $(CFLAGS) -o $@ $< -lpthread

spinlock.o: spinlock.c spinlock.h
	$(CC) $(CFLAGS) -c $<

check_result: check_result.o spinlock.h
	$(CC) $(CFLAGS) -o $@ $< 
check_result.o: check_result.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf *.o 
