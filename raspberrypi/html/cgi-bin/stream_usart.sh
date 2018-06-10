#!/bin/bash
echo "Content-type: text/plan"
echo
sudo chmod 777 ttyACM0
sudo stty -F /dev/ttyACM0 4:0:18b2:0:0:0:0:0:1:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0
sudo stty -F /dev/ttyACM0 cs8 115200 raw
#for ((;;))
#do
cat < /dev/ttyACM0
#done


