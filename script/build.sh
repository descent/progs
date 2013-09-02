# auto git clone and make the code
#!/bin/sh

en_wd='0'
if [ "$1" != "" ]; then
  en_wd='1'
else
  echo "watch dog support current disable"
  echo "========================"
  echo "$0 1 can enable watch dog support"
fi
echo "enable watch dog: $en_wd"
sleep 7

qt_make=/home/lucid/ltib/rootfs/usr/local/Trolltech/qt4/bin/qmake

cd /tmp
rm -rf mmadplayer update_connect_status c2d_rect c2d_ticker /tmp/pkg pkg*

git clone code@192.168.20.100:/home/code/git/update_connect_status.git
git clone code@192.168.20.100:/home/code/git/mmadplayer.git
git clone code@192.168.20.100:/home/code/git/c2d_rect.git
git clone code@192.168.20.100:/home/code/git/c2d_ticker.git

cd /tmp/mmadplayer
git checkout origin/xmlrpc_gst-launch -b xmlrpc_gst-launch
ln -s /tmp/mmadplayer/setting.h /tmp/update_connect_status/inc/setting.h

echo "cd /tmp/mmadplayer to make"
sleep 2

cd /tmp/update_connect_status
$qt_make src.pro
make
$qt_make src.pro
make install

echo "cd /tmp/mmadplayer to make"
sleep 2


cd /tmp/c2d_rect
make

cd /tmp/c2d_ticker
ln -s /tmp/update_connect_status/inc/func.h /tmp/c2d_ticker/func.h
$qt_make src.pro
make

cd /tmp/mmadplayer/mmadplayer_ctl
$qt_make mmadplayer_ctl.pro
make

cd /tmp/mmadplayer/qte_server/
$qt_make qtes.pro
make

cd /tmp/mmadplayer
$qt_make prog.pro
make

ln -s /tmp/update_connect_status/inc/func.h /tmp/mmadplayer/func.h
version=`git show --summary |grep commit |cut -d ' ' -f2`
sed -i -e "s/\$Format:%H\\$/$version/g" const.h


if [ "$en_wd" = "1" ]; then
  echo "DEFINES += ENABLE_WATCHDOG" >> mmadplayer.pro
fi
$qt_make mmadplayer.pro
make
make install


mkdir /tmp/pkg/


cp -r /tmp/mmadplayer/mmadplayer_dir/  /tmp/pkg

cp /tmp/mmadplayer/*.qm /tmp/pkg/mmadplayer_dir/
cp /tmp/mmadplayer/wd_tool /tmp/pkg/mmadplayer_dir/


cp /tmp/update_connect_status/tools/*  /tmp/pkg/mmadplayer_dir/
cp -r /tmp/c2d_rect/c2d_rect  /tmp/pkg/mmadplayer_dir/
cp -r /tmp/c2d_ticker/c2d_ticker  /tmp/pkg/mmadplayer_dir/
mv /tmp/pkg/mmadplayer_dir/reg* /tmp/pkg/
sed -i -e "s/mmadplayer&/mmadplayer -l jp\\&/g" /tmp/pkg/mmadplayer_dir/mmadplayer_v2.sh
cp /tmp/pkg/mmadplayer_dir/mmadplayer_v2.sh /tmp/pkg/mmadplayer_dir/mmadplayer.sh
mv /tmp/pkg/mmadplayer_dir /tmp/pkg/mmadplayer

cd /tmp
#tar cvf pkg-`date +%Y%m%d-%H%M%S`.tar pkg
tar cvf pkg.tar pkg
