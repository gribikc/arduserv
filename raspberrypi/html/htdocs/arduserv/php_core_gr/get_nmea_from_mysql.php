<?php
	include('config_inc.php');
	if(!is_numeric($_SESSION['last_id']) || $_GET["reset"]=="1"){
		$_SESSION['last_id']=0;
	}

	$sql='SELECT * FROM `nmea` WHERE (`nmea`.`id_code` = 123 && `nmea`.`nmea_id` > '.$_SESSION['last_id'].') ORDER BY `nmea`.`time`  ASC LIMIT 100';
	$result = mysqli_query($mysql_db_connect, $sql);
	//printf("Select вернул %d строк.\n", mysqli_num_rows($result));
	//echo("<br>");
	//echo($sql);
	echo("[\n\r    [".$_SESSION['last_id']."]");
	$num_row=mysqli_num_rows($result);
	for($i=0;$i<$num_row;$i++){
		$row = mysqli_fetch_assoc($result);
		if($row['nmea_type']=='$GPGGA'){
			if($row_se = mysqli_fetch_assoc($result)){
				$i++;
				$delta_time=($row_se['time']-$row['time']);
				if($row_se['nmea_type']=='$SDDPT' && $delta_time<0.5){//!!!
					echo(",\n\r    [");
					echo($row['json']);
					echo(",");
					echo($row_se['json']);
					echo("]");
					
					if(is_numeric($row['nmea_id']) && $row['nmea_id']>$_SESSION['last_id']){
						$_SESSION['last_id']=$row['nmea_id'];
					}
				}
			}
		}
	}
	echo("\n\r]");

	mysqli_free_result($result);
?>