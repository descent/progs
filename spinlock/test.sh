#!/bin/sh
time=20

if [ "$1" != "" ]; then
time=$1
fi

i=0
DURATION=1

echo "$time run"
while [ $i -le $time ];do
DURATION=$[1 + $[ RANDOM % 10 ]]
echo "$i ## DURATION: $DURATION =============="
timeout -s SIGINT $DURATION ./spinlock
ls -l /tmp/xyz1
./check_result
i=`expr $i + 1`
done


