<?php
	include('config_inc.php');


	$sql='SELECT * FROM `nmea` WHERE (`nmea`.`id_code` = 123 && `nmea`.`nmea_type` = \'$SDDPT\') ORDER BY `nmea`.`data`,`nmea`.`time` LIMIT 10';
	$result = mysqli_query($mysql_db_connect, $sql);
	echo("Select вернул ".mysqli_num_rows($result)." строк.\n");
	echo("<br>");
	echo($sql);
	echo("<br>");

	$num_row=mysqli_num_rows($result);
	$row = mysqli_fetch_assoc($result);
	for($i=1;$i<($num_row-1);$i++){
		$row_se = mysqli_fetch_assoc($result);
		if($row['data']==$row_se['data']){
			//$sql='SELECT * FROM `nmea` WHERE (`nmea`.`id_code` = 123 && `nmea`.`time` <= \''.$row_se['time'].'\') ORDER BY `nmea`.`time`  ASC LIMIT 2';
			//$result = mysqli_query($mysql_db_connect, $sql);
			//echo("____Запрос параметров дубликата вернул ".mysqli_num_rows($result)." строк.\n");
			echo("____<br>");
			echo("____".$sql);
			echo("____<br>");
		}
		$row=$row_se;
	}

	mysqli_free_result($result);
?>