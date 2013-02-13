#CFLAGS = -std=c99 -fno-stack-protector -m32 -ffreestanding -fno-builtin -g -O0
#CFLAGS = -std=c99 -fno-stack-protector -m32 -ffreestanding -fno-builtin -g -I../include
#ASFLAGS = --32 -g
#LDFLAGS = -m elf_i386


# enter protected mode kernel loader
kloaderp.bin: kloaderp.bin.elf
	objcopy -R .pdr -R .comment -R.note -S -O binary $< $@

kloaderp.bin.elf: kloader_init.o kernel_loader.o 
	ld $(LDFLAGS) -nostdlib -g -o $@ -Tklp.ld $^

kloader_init.o: kloader_init.S
	$(CC) $(CFLAGS) -o $@ -c $<


.PHONE: clean 

clean:
	rm -rf *.o *.elf *.bin kernel_loader.s *.d *.e

kernel_loader.o: kernel_loader.c
	gcc -DIPC -std=c99 -fno-stack-protector -m32 -ffreestanding -fno-builtin -g -Iinclude -I../include  -c kernel_loader.c
