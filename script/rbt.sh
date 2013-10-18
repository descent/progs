# open /home/bt number then add 1, write back to /home/bt
#!/bin/sh

BT=`cat /home/bt`
#echo $BT

BT=`expr $BT + 1`

#echo $BT
echo $BT > /home/bt

