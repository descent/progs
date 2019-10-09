#!/usr/bin/expect
set timeout 60

set f [open "/tmp/1.txt"]
set commands [split [read $f] "\n"]
close $f



#exit

  spawn ssh -oBatchMode=no -oStrictHostKeyChecking=no bbsu@ptt.cc

  set BBS_ID "aa"
  set BBS_PW "bb"

expect "或以 new 註冊: " { send "$BBS_ID\r" }
sleep 1
expect "請輸入您的密碼" { send "$BBS_PW\r" }
sleep 1
#send "\n"
expect "請按任意鍵繼續" {send -- "\[D"}
expect "oodbye" {send "f\r"}
expect "編號" {send "113\r\r\r"}

# post
#send -- ""
send -- "\[C"
send -- ""
send "1\r"

send -- "輸入"
sleep 1
send -- "測試"
sleep 1
send -- " 10"
#expect -exact "\[30;47m3\[m"
sleep 1
send -- "\r"

foreach cmd $commands {
  send "$cmd\r"
sleep 1
#  puts "$cmd\r"
}

#send -- "test post 8\r"
#send -- "測試 po 文\r"
#send -- "33 測試 po 文\r"
#send -- "55 測試 po 文\r"

# 離開編輯畫面
send -- ""
send -- "s"
sleep 1
send -- "\r"

# 存檔
send -- "0"
#expect -exact "\[30;47m0\[m"
sleep 1
send -- "\r"

send -- "\[D"

send -- "\[D"
send -- "\[D"
send -- "\[D"
send -- "\r"
expect "您確定要離開【 批踢踢實業坊 】嗎(Y/N)？" {send -- "y"}
sleep 1
send -- "\r"
sleep 1
send -- "\[D"

#send -- "the 2nd line\r"
#send -- "\r"
#send -- "y\r"
#send -- "0\r"
#send -- "\r"
#
# down
#send -- "\[B"
#send -- "\[B"

interact
