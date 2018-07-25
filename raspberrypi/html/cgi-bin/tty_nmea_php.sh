#!/bin/sh

echo "begin"
	cat /dev/ttyUSB0 | while read LINE; do
			nmea=$(echo "$LINE" | head -c -2)
			time_mrk=$(date +"%y%j%H%M%S.%N")
			echo "$time_mrk"
			wget -q -b --spider "http://127.0.0.1/arduserv/php_core_gr/tty_nmea_sql.php?id=123&data=$nmea&time_mr=$time_mrk"
			echo "$nmea"
		done