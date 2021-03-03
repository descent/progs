#!/bin/sh
# 取得 html img src url
#set -x
#img=`grep -o '<img[^>]*src="[^"]*"' "$1" | grep -o '"[^"]*"' |grep jpg`



outfn="fn.sh"
echo "" > $outfn
grep -o '<img[^>]*src="[^"]*"' "$1" | grep -o '"[^"]*"' |grep jpg | 
while read f
  do 
  img_url=`echo $f | sed -e 's/"//g'`
  echo "img: $img_url"

  token=`cat bitly_token`

  echo "cmd: ./shorten.sh "$img_url" $token"
  short_url=`./shorten.sh "$img_url" $token`

  org_fn=`basename "$img_url"`
  #echo "org fn: $org_fn" >> $outfn
  #echo "ss: $short_url"

  short_url=`echo $short_url | sed -e 's/\r//g'`

  filename="${org_fn%.*}"
  extension="${org_fn##*.}"


  echo "filename=$filename" >> $outfn
  echo "short_url=$short_url" >> $outfn
  echo 'sed -i -e "s|$filename|$short_url|g" h.txt' >> $outfn
done
