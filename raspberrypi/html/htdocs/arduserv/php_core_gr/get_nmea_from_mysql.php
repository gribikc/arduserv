<?php
	include('config_inc.php');
	
	
	$sql='SELECT * FROM `nmea` WHERE (`nmea`.`id_code` = 123 && `nmea`.`nmea_id` > 0)ORDER BY `nmea`.`time`  ASC LIMIT 10';
	$result = mysqli_query($mysql_db_connect, $sql);
	//printf("Select вернул %d строк.\n", mysqli_num_rows($result));
	//echo("<br>");
	echo("[\n\r    []");
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
				}
			}
		}
	}
	echo("\n\r]");
	//echo("}");
	/*while( $rowst = mysqli_fetch_assoc($result) && $rowse = mysqli_fetch_assoc($result) ){
        echo($rowst['json']);
		echo("<br>");
    }*/
	
	mysqli_free_result($result);
?>