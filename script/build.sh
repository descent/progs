# auto git clone and make the code
#!/bin/sh

build_dir=/tmp/build_mmadplayer
pkg_dir=/tmp/build_mmadplayer/pkg

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

#cd /tmp
#rm -rf mmadplayer update_connect_status c2d_rect c2d_ticker /tmp/pkg pkg*
rm -rf $build_dir

mkdir $build_dir
cd $build_dir

git clone code@192.168.20.100:/home/code/git/update_connect_status.git
git clone code@192.168.20.100:/home/code/git/mmadplayer.git
git clone code@192.168.20.100:/home/code/git/c2d_rect.git
git clone code@192.168.20.100:/home/code/git/c2d_ticker.git
git clone code@192.168.20.100:/home/code/git/gst-player

cd $build_dir/gst-player
make

cd $build_dir/mmadplayer
#git checkout xmlrpc_ver -b xmlrpc_ver
git checkout origin/play_cmd -b play_cmd
ln -s $build_dir/mmadplayer/setting.h $build_dir/update_connect_status/inc/setting.h

echo "cd $build_dir/mmadplayer to make"
sleep 2



cd $build_dir/update_connect_status
$qt_make src.pro
make
$qt_make src.pro
make install


cd $build_dir/c2d_rect
make

cd $build_dir/c2d_ticker
git checkout origin/client_server -b client_server
ln -s $build_dir/update_connect_status/inc/func.h $build_dir/c2d_ticker/c2d_server/func.h
sed -i -e "/LIBS/"d src.pro
echo "LIBS += -l2dz430 -lgsl-fsl" >> src.pro
$qt_make src.pro
make

cd $build_dir/mmadplayer/mmadplayer_ctl
$qt_make mmadplayer_ctl.pro
make

cd $build_dir/mmadplayer/qte_server/
$qt_make qtes.pro
make

cd $build_dir/mmadplayer
$qt_make prog.pro
make

ln -s $build_dir/update_connect_status/inc/func.h $build_dir/mmadplayer/func.h
version=`git show --summary |grep commit |cut -d ' ' -f2`
sed -i -e "s/\$Format:%H\\$/$version/g" const.h

#echo "DEFINES += INTER_CUT_IMMED" >> mmadplayer.pro

if [ "$en_wd" = "1" ]; then
  echo "DEFINES += ENABLE_WATCHDOG" >> mmadplayer.pro
fi
sed -i -e "/LIBS/"d mmadplayer.pro
echo "LIBS += -lqxmlrpc" >> mmadplayer.pro
$qt_make mmadplayer.pro
make
make install


mkdir $pkg_dir

cp -r $build_dir/mmadplayer/mmadplayer_dir/ $pkg_dir

cp $build_dir/mmadplayer/*.qm $pkg_dir/mmadplayer_dir/
cp $build_dir/mmadplayer/wd_tool $pkg_dir/mmadplayer_dir/


cp $build_dir/update_connect_status/tools/*  $pkg_dir/mmadplayer_dir/
cp -r $build_dir/c2d_rect/c2d_rect  $pkg_dir/mmadplayer_dir/
cp -r $build_dir/c2d_ticker/c2d_client/c2d_ticker $build_dir/c2d_ticker/c2d_server/c2d_ticker_server $pkg_dir/mmadplayer_dir/
mv $pkg_dir/mmadplayer_dir/reg* $pkg_dir
sed -i -e "s/mmadplayer&/mmadplayer -l jp\\&/g" $pkg_dir/mmadplayer_dir/mmadplayer_v2.sh
cp $pkg_dir/mmadplayer_dir/mmadplayer_v2.sh $pkg_dir/mmadplayer_dir/mmadplayer.sh
mv $pkg_dir/mmadplayer_dir $pkg_dir/mmadplayer

cd $pkg_dir/..
#tar cvf pkg-`date +%Y%m%d-%H%M%S`.tar pkg
tar cvf pkg.tar pkg
