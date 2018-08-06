#!/bin/bash
echo "Content-type: text/plan"
echo

echo "123"

ls -l /dev/ttyUSB0
stty < /dev/ttyUSB0
stty -F /dev/ttyUSB0 cs8 57600 raw
stty < /dev/ttyUSB0

echo "456"
