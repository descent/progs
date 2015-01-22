# ref: android 及 arm 原生語言逆向工程破解 android app 一書
NDK_ROOT=/home/descent/and-dev/android-ndk-r10
TOOLCHAINS_ROOT=/home/descent/and-dev/android-ndk-r10/toolchains/arm-linux-androideabi-4.8/prebuilt/linux-x86
TOOLCHAINS_PREFIX=$(TOOLCHAINS_ROOT)/bin/arm-linux-androideabi-
TOOLCHAINS_INC=$(TOOLCHAINS_ROOT)/lib/gcc/arm-linux-androideabi/4.8/include-fixed

PLATFORM_ROOT=$(NDK_ROOT)/platforms/android-17/arch-arm
PLATFORM_INC=$(PLATFORM_ROOT)/usr/include/
PLATFORM_LIB=$(PLATFORM_ROOT)/usr/lib/

#FLAGS=-static -I$(TOOLCHAINS_INC) -I$(PLATFORM_INC) -L$(PLATFORM_LIB) -nostdlib -lgcc -Bdynamic -lc
FLAGS=-I$(TOOLCHAINS_INC) -I$(PLATFORM_INC) -L$(PLATFORM_LIB) -nostdlib -lgcc -Bdynamic -lc

OBJS=$(PLATFORM_LIB)/crtbegin_dynamic.o $(PLATFORM_LIB)/crtend_android.o
#OBJS=$(PLATFORM_LIB)/crtbegin_static.o $(PLATFORM_LIB)/crtend_android.o

hello: hello.o
	$(TOOLCHAINS_PREFIX)gcc $(FLAGS) $(OBJS) $< -o $@
hello.o: hello.c
	$(TOOLCHAINS_PREFIX)gcc -c $< $(FLAGS)

clean:
	rm -rf *.o hello
