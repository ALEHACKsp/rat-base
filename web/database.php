<?php

$link = new mysqli("ip", "username", "password", "db-name");

if($link === false){
    die("RAT-BASE: Could not connect. " . $mysqli->connect_error);
}

?>
