sudo chmod 777 /dev/ttyACM0

chmod +x fun-script
sudo ln -s /home/pi/data/htdocs/arduserv /var/www/html/arduserv

sudo stty -F /dev/ttyACM0 cs8 115200 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts raw
sudo stty -F /dev/ttyACM0 4:0:18b2:0:0:0:0:0:1:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0
sudo stty -F /dev/ttyACM0 cs8 115200 raw

cat < /dev/ttyACM0
cat > /dev/ttyACM0

#!/bin/sh
echo "Content-type: text/html"
echo 
echo "<html><head><title>hello world</title></head><body><p>It works!</p></body>"