h: h.o
	/usr/bin/ld -b elf32-i386 -m elf_i386     -s -L. -o h -T link.res -e _start

f1.o: f1.pas
	/usr/local/lib/fpc/3.1.1/ppcross386 -g -Cn $<
h.o: h.pas
	#fpc h.pas
	#ppcx64 $<
	#/usr/local/lib/fpc/3.1.1/ppcross386 -Cn h.pas
	#/usr/local/lib/fpc/3.1.1/ppcross386 -Cn h.pas -Fu/usr/local/lib/fpc/3.1.1/units/i386-linux/rtl-console/crt.ppu # -Fu spec Crt unit path
	/usr/local/lib/fpc/3.1.1/ppcross386 -g -Cn h.pas -Fu/usr/local/lib/fpc/3.1.1/units/i386-linux/rtl-console/ # -Fu spec Crt unit path
clean:
	rm -f h *.o
