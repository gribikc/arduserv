#!/bin/sh

#number=$RANDOM
#< /dev/urandom tr -dc _A-Z-a-z-0-9 | head -c${1:-32};echo;
#< /dev/urandom tr -dc _A-Z-a-z-0-9 | head -c6
st_rand=$(head -1 /dev/urandom | od -N 2 | awk '{ print $2 }')
echo $st_rand

while true
do
	sudo stty -F /dev/ttyUSB0 4:0:18b2:0:0:0:0:0:1:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0
	sudo stty -F /dev/ttyUSB0 cs8 57600 raw

	#echo "begin"
		cat /dev/ttyUSB0 | while read LINE; do
				nmea=$(echo "$LINE" | head -c -2)
				time_mrk=$(date +"%y%j%H%M%S.%N")
				#echo "$time_mrk"
				wget -q -b --spider "http://127.0.0.1/arduserv/php_core_gr/tty_nmea_sql.php?id=123&data=$nmea&time_mr=$time_mrk&random=$st_rand"
				#echo "$nmea"
				#echo "http://127.0.0.1/arduserv/php_core_gr/tty_nmea_sql.php?id=123&data=$nmea&time_mr=$time_mrk&random=$st_rand"
			done
			
	sleep 5s
done