#!/bin/sh
	ls -1 /dev/ttyUSB* /dev/ttyAMA* /dev/ttyACM* | while read LINE; do
		echo "<br>"
		echo $LINE
		echo "<br>"
		stty < $LINE
		echo "<br>"
	done