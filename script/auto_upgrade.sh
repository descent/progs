#!/bin/sh
#touch /tmp/1111
rm -rf /home/pkg /home/pkg.tar
cp ./pkg.tar /home/
cd /home/
tar xf /home/pkg.tar
cp -r pkg/* weiya/

