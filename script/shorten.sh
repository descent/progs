#!/bin/sh
# call bitly shorten api
# $1: long url
# $2: Access Token
#set -x
echo ""
#repos=`curl -H "Content-Type: application/json" -s -i --data {\"long_url\":\"$1\"} -H "Authorization: Bearer $2" https://api-ssl.bitly.com/v4/bitlinks`

curl -H "Content-Type: application/json" -s -i --data {\"long_url\":\"$1\"} -H "Authorization: Bearer $2" https://api-ssl.bitly.com/v4/bitlinks > bitly.txt


#repos=`curl -H "Content-Type: application/json" -v -i --data {\"long_url\":\"$1\"} -H "Authorization: Bearer $2" https://api-ssl.bitly.com/v4/bitlinks`

#repos="{"created_at":"2021-03-03T02:26:44+0000","id":"bit.ly/2NZxyBg","link":"https://bit.ly/2NZxyBg","custom_bitlinks":[],"long_url":"https://1.bp.blogspot.com/-pLs-eFnvdmo/XpXLhQIvmOI/AAAAAAADIJ0/qj_5Nsz2IP4mnFfiLEhfRtymgJCCsJH4ACKgBGAsYHg/s320/IMG_20190912_074320.jpg","archived":false,"tags":[],"deeplinks":[],"references":{"group":"https://api-ssl.bitly.com/v4/groups/Bl3218R7Sxz"}}"
#echo ""

#repos="{"message":"FORBIDDEN"}: default-src 'none0; includeSubDomains"
#echo "---"
#echo $repos

#echo "==="

#echo $repos | grep -o 'link*":"https:[^"]*"' |grep -o '"https:[^"]*"' 

grep -o 'link*":"https:[^"]*"' bitly.txt |grep -o '"https:[^"]*"' 

