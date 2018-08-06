#!/bin/bash
echo "Content-type: text/plan"
echo

stty -F /dev/ttyUSB0 4:0:18b2:0:0:0:0:0:1:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0
stty -F /dev/ttyUSB0 cs8 57600 raw
#for ((;;))
#do
cat < /dev/ttyUSB0
#done


