#!/bin/sh

org_fn=$1
fn=`ls "$org_fn"  |cut -d '.' -f1`
echo $fn

echo ffmpeg -vn -i "\"$org_fn\"" -ar 44100 -ab 128k "\"$fn.mp3\""
echo avconv -vn -i "\"$org_fn\"" -ar 44100 -ab 128k "\"$fn.mp3\""
avconv -vn -i "$org_fn" -ar 44100 -ab 128k "$fn.mp3"
