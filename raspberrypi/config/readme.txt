﻿//Обзее
	sudo raspi-config
	sudo rpi-update
	sudo apt-get upgrade
	sudo apt-get update
	sudo apt-get dist-upgrade

	sudo dd if=/dev/mmcblk0 of=/home/pi/flash_m/arduserv/raspberrypi-backup_0X0X1X.img
	!sudo dd if=/home/Username/Desktop/raspberrypi-backup.img of=/dev/mccblk0

	sudo blkid
	sudo mount /dev/sda /home/pi/flash_m

	df /dev/sdadf
	df -ah

	stress -c 4 -t 900s
	top | awk '/Cpu/{print substr($LINE,1,match($LINE,/us,/)-1)}'
	cat < /proc/loadavg


//Настройка скриптов
	chmod +x fun-script
	sudo ln -s /home/pi/data/htdocs/arduserv /var/www/html/arduserv
	/usr/lib/cgi-bin
	# cat your-script.sh | tr -d '\r' > corrected-your-script.sh
	
	usermod -a -G dialout www-data

//PHP
	system("stty -F /dev/ttyAMA0 57600");


//Настройка UART
	//ACM//AMA//
	ls /dev/ttyA*
	sudo chmod 777 /dev/ttyACM0
	sudo stty -F /dev/ttyACM0 cs8 115200 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts raw
	sudo stty -F /dev/ttyACM0 4:0:18b2:0:0:0:0:0:1:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0
	sudo stty -F /dev/ttyACM0 cs8 115200 raw

//Ввод вывод UART
	cat < /dev/ttyACM0
	cat > /dev/ttyACM0

//CGI-bin-to-html
	#!/bin/sh
	echo "Content-type: text/html"
	echo 
	echo "<html><head><title>hello world</title></head><body><p>It works!</p></body>"

//Температура
	vcgencmd measure_temp
	cat /sys/class/thermal/thermal_zone0/temp
	
	
	
	
//WIFI
	sudo iwlist wlan0 scan | grep "ESSID\|IE: IEEE"
	sudo iwlist wlan0 scan | grep "ESSID\|IE: IEEE\|Address\|Quality"
	sudo iw dev wlan0 set power_save off

	sudo ifconfig wlan0 down
	sudo ifconfig wlan0 up
	sudo ifconfig wlan0

	cd /etc/wpa_supplicant
	nano wpa_supplicant.conf

	rfkill list
	
	
//1st
	sudo apt-get install apache2 -y
	sudo a2enmod cgid
	sudo systemctl restart apache2
	chmod 777 /usr/lib/cgi-bin
	chmod +x fun-script
	
	sudo nano /etc/rc.local
	#rc.local
		sudo /usr/lib/cgi-bin/find_conf_tty.sh &
		sudo /usr/lib/cgi-bin/tty_nmea_php.sh &
		sudo chmod +s /bin/systemctl
		sudo chmod 777 /bin/systemctl
		sudo chmod +s /sbin/halt
		sudo chmod 777 /sbin/halt
		sudo chmod +s /sbin/reboot
		sudo chmod 777 /sbin/reboot
		sudo chmod +s /dev/initctl
		sudo chmod 777 /dev/initctl
		


	
//MySQL
	sudo mysql

		use mysql;
		update user set plugin='' where User='root';
		flush privileges;
		exit
		
	root:mysqlpasswd

SELECT * FROM `nmea` 
WHERE (`nmea`.`id_code` = '123' && `nmea`.`nmea_id` > 0)
ORDER BY `nmea`.`time`  ASC
LIMIT 10
		
		
//CONCEPT

	