#!/bin/sh

while true
do
	ls -1 /dev/ttyUSB* /dev/ttyAMA* /dev/ttyACM* | while read LINE; do
		#echo "$LINE"
		sudo chmod 777 "$LINE"
	done
	sleep 5s
done