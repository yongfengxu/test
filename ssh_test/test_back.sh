#!/usr/bin/expect
set time -1
set passwd "ggsn"
set log_file show_result.log

spawn ssh erv@semopcgwbgw02
expect {
"*assword:*" {send "$passwd\r"}
"*es/no)?*" {send "yes\r"; exp_continue}
}

expect "*>"
send "show interfaces ae1.3854\r"
#interact
expect eof
EOF
