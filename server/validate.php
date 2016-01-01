<?php
/*
If you want to use a MySQL-Database: Comment out 'include "file.php"' and uncomment 'include "database.php"'
If you want to use a txt-File:       Comment out 'include "database.php"'and uncomment 'include "file.php"'
Do not forget to edit the configuration in 'file.php' or 'database.php'.
*/
#include "file.php";
include "database.php";

$privatekey = $_GET["p"];
$arr = getData($privatekey);
$_publickey = $arr[1];
$_filehash = $arr[3];
if(!empty($_GET["k"])) {
    $publickey = $_GET["k"];
    if(strcmp($publickey,$_publickey)!=0) {
        exit("");
    }
}
if(!empty($_GET["f"])) {
    $filehash = $_GET["f"];
    if(strcmp($filehash,$_filehash)!=0) {
        exit("");
    }
}
echo "valide";
?>
