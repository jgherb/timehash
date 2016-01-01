<?php
/*
If you want to use a MySQL-database: Comment out 'include "file.php"' and uncomment 'include "database.php"'
If you want to use a file:           Comment out 'include "database.php"'and uncomment 'include "file.php"'
Do not forget to edit the configuration in 'file.php' or 'database.php'.
*/
#include "file.php";
include "database.php";

$key = $_GET["k"];
$data = getData($key);
$timestamp = $data[0];
$filehash = $data[3];
echo "key: " . $key . "<br>" . "file hash: " . $filehash . "<br>" . "timestamp: " . $timestamp;
?>
