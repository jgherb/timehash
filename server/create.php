<?php
/*
If you want to use a MySQL-Database: Comment out 'include "file.php"' and uncomment 'include "database.php"'
If you want to use a txt-File:       Comment out 'include "database.php"'and uncomment 'include "file.php"'
Do not forget to edit the configuration in 'file.php' or 'database.php'.
*/
#include "file.php";
include "database.php";

function generateRandomString($length = 10) {
    $characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
    $charactersLength = strlen($characters);
    $randomString = '';
    for ($i = 0; $i < $length; $i++) {
        $randomString .= $characters[rand(0, $charactersLength - 1)];
    }
    return $randomString;
}
$filehash = $_GET["f"];
if(empty($filehash)) {
    die("File hash is not given!");
}
do {
    $publickey =  generateRandomString(10);
} while(!isFree($publickey));
do {
    $privatekey =  generateRandomString(20);
} while(!isFree($privatekey));
$timestamp = time();
save($timestamp, $publickey, $privatekey, $filehash);
echo "public key: " . $publickey . "<br>" . "private key: " . $privatekey . "<br>" . "timestamp: " . $timestamp;
?>
