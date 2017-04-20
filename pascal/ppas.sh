#!/bin/sh
DoExitAsm ()
{ echo "An error occurred while assembling $1"; exit 1; }
DoExitLink ()
{ echo "An error occurred while linking $1"; exit 1; }
echo Linking h
OFS=$IFS
IFS="
"
/usr/bin/ld -b elf32-i386 -m elf_i386      -L. -o h -T link.res -e _start
if [ $? != 0 ]; then DoExitLink h; fi
IFS=$OFS
