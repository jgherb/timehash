<?php
/*
If you want to use a MySQL-Database: Comment out 'include "file.php"' and uncomment 'include "database.php"'
If you want to use a txt-File:       Comment out 'include "database.php"'and uncomment 'include "file.php"'
Do not forget to edit the configuration in 'file.php' or 'database.php'.
*/
#include "file.php";
include "database.php";

$filehash = $_GET["f"];
$publickey = $_GET["k"];
$arr = getData($publickey);
$_publickey = $arr[1];
$_filehash = $arr[3];
if(strcmp($_filehash,$filehash)==0) {
    echo "true1";
}
else {
    echo "false0";
}
?>
