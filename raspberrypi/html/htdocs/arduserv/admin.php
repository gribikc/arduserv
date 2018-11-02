<?php
session_start();
if($_GET['cmd']==1 || $_GET['cmd']=='halt'){
	delete_get_from_url();
	system("halt");//sleep 10 && echo 123 &
}
if($_GET['cmd']==2 || $_GET['cmd']=='reboot'){
	delete_get_from_url();
	system("reboot");
}
if($_GET['cmd']==3 || $_GET['cmd']=='session_reset'){
    session_unset();
    session_destroy();
	delete_get_from_url();
}
?>
<a href="admin.php?cmd=halt">Выключить</a><br><br>
<a href="admin.php?cmd=reboot">Перезагрузить</a><br><br>
<br><a href="admin.php?cmd=session_reset">Сброс PHP сессии</a><br><br>



<?php
echo('<br><b>Температура:</b>');
$a=exec('cat /sys/class/thermal/thermal_zone0/temp');
echo(($a/1000).' градусов.');

echo('<br><b>UpTime:</b>');
passthru("uptime");

echo('<br><b>Дата сервера:</b>');
echo(date('H:i:s d.m.y'));

echo('<br><b>Пинг ya.ru:</b>');
echo('<pre>');
passthru('ping 87.250.250.242 -c 1 -W 1');
echo('</pre>');

echo('<br><b>Настройки сети:</b>');
echo('<pre>');
passthru('ifconfig');
echo('</pre>');

echo('<br><b>Статус беспроводной сети:</b>');
echo('<pre>');
passthru('iwconfig');
echo('</pre>');

echo('<br><b>Точки доступа:</b>');
echo('<pre>');
passthru('iwlist wlan0 scan | grep "ESSID\|IE: IEEE\|Address\|Quality"');
echo('</pre>');

echo('<br><b>UART конфиг:</b>');
passthru('/usr/lib/cgi-bin/view_conf_tty.sh');

echo('<br><b>Процессы:</b>');
echo('<pre>');
passthru('ps -aux');
echo('</pre>');

function delete_get_from_url(){
	header('Location: admin.php?cmd=0');
}
?>