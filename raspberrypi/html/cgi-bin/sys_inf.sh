#!/bin/bash
echo "Content-type: text/plan"
echo
while true
do
	echo -n '$SYST0,'
	b=$(cat /sys/class/thermal/thermal_zone0/temp)
	echo -n "$b"
	echo -n '*36'
	echo -n -e "\n"
	sleep 0.3s
done

