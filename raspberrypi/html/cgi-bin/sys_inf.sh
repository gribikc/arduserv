#!/bin/bash
echo "Content-type: text/plan"
echo
echo -n '$SYST0,'
b=$(cat /sys/class/thermal/thermal_zone0/temp)
echo -n "$b"
echo -n '*36'
echo -n -e "\n"

