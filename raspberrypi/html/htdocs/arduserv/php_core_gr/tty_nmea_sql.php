<?php
	include('config_inc.php');	
	
	$id_code=addslashes($_GET["id"]);
	$random_code=addslashes($_GET["random"]);

	$data=addslashes($_GET["data"]);
	$data_arr=explode(',',$data);
	
	$data_arr_temp=explode('*',$data_arr[sizeof($data_arr)-1]);
	$data_arr[sizeof($data_arr)-1]=$data_arr_temp[0];
	array_push($data_arr, $data_arr_temp[1]);
	
	$time_mr=addslashes($_GET["time_mr"]);
	
	echo("<br>".$data);

	$json_arr=json_encode($data_arr);
	
	$sql_m='INSERT INTO `nmea` (`nmea_id`, `nmea_type`, `date`, `time`, `data`, `id_code`, `session_id`, `json`) VALUES
		(NULL, \''.$data_arr[0].'\', CURRENT_TIMESTAMP, \''.$time_mr.'\', \''.$data.'\', \''.$id_code.'\', \''.$random_code.'\', \''.$json_arr.'\')';
	$sql_res=mysqli_query($mysql_db_connect,$sql_m);
	
	echo("<br>".$sql_res);
	
	/*$last_sql_id=mysqli_insert_id($mysql_db_connect);
	if($last_sql_id>0){
		for($i=1;$i<sizeof($data_arr);$i++){
			$wr_data=$data_arr[$i];
			$nof=$i;
			//if($i==sizeof($data_arr)-1){
			//	array_push($stack, "apple", "raspberry");
			//}
			$sql_m='INSERT INTO `nmea_data` (`nmea_data_id`, `nmea_id`, `data`, `nof`) VALUES
				(NULL, \''.$last_sql_id.'\', \''.$wr_data.'\', \''.$i.'\')';
			$sql_res=mysqli_query($mysql_db_connect,$sql_m);
			echo("<br>".$sql_res);
		}
	}*/
?>