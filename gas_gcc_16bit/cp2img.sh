#!/bin/sh
# copy needed files to floppy image.

#make c_init_by_boot_loader.bin
make kloaderp.bin
sudo  mount -o loop boot.img /mnt/
#sudo  cp kloader.bin  /mnt/loader.bin
sudo  cp -v kloaderp.bin  /mnt/loader.bin
sudo  ls -l /mnt 
sudo  umount /mnt 

#sudo  mount -o loop dos6.22_data.img /mnt/
#sudo  cp c_init_by_boot_loader.bin  /mnt/c.com
#sudo  umount /mnt 
