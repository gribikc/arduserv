#!/bin/bash
echo "Content-type: text/plan"
echo
b=0
c=1
while true
do
	echo -n '$TSTCNT,'
	b=$(($b+$c))
	echo -n "$b"
	echo -n '*36'
	echo -n -e "\n"
	sleep 1s
done
