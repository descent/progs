#!/bin/sh
# ref: http://ephrain.pixnet.net/blog/post/58136247-%5Blinux%5D-%E4%BD%BF%E7%94%A8-shell-%E6%88%AA%E5%8F%96%E6%AA%94%E6%A1%88%E7%9A%84%E6%AA%94%E5%90%8D%E8%88%87%E5%89%AF%E6%AA%94%E5%90%8D

# trap: https://rimuhosting.com/knowledgebase/linux/misc/trapping-ctrl-c-in-bash
trap ctrl_c INT

function ctrl_c() 
{
  echo "** Trapped CTRL-C **"
  exit 1;
}

if [ "$1" == "" ]; then
echo "$0 filename"
exit 1
fi

for fname in "$@"
do
echo fname: $fname
org_fn=$fname
fn=`ls "$org_fn"  |cut -d '.' -f1`
filename="${org_fn%.*}"
extension="${org_fn##*.}"
echo fn: $fn
echo filename: $filename
echo ext: $extension
echo ffmpeg -vn -i "\"$org_fn\"" -ar 44100 -ab 128k "\"$filename.mp3\"" 
echo ffmpeg -vn -i "\"$org_fn\"" -ar 44100 -ab 128k "\"$filename.mp3\"" > r.sh
sh r.sh
rm r.sh
done

#org_fn="$@"
#fn=`ls "$org_fn"  |cut -d '.' -f1`
#filename="${org_fn%.*}"
#extension="${org_fn##*.}"
#echo $fn
#echo $filename
#echo $extension

#ffmpeg -vn -i $org_fn -ar 44100 -ab 128k $filename.mp3
#echo avconv -vn -i "\"$org_fn\"" -ar 44100 -ab 128k "\"$fn.mp3\""
#avconv -vn -i "$org_fn" -ar 44100 -ab 128k "$fn.mp3"
