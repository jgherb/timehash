<?php
/*
Configuration start
*/
$db_server = "localhost";
$db_user = "yourusername";
$db_password = "yourpassword";
$db_database = "thash";
/*
Configuration finish
*/

function initConnection() {
    $db = mysqli_connect($GLOBALS["db_server"], $GLOBALS["db_user"], $GLOBALS["db_password"], $GLOBALS["db_database"]);
    if(!$db)
    {
        exit("connection error: ".mysqli_connect_error());
    }
}
function getData($key) {
    $db = mysqli_connect($GLOBALS["db_server"], $GLOBALS["db_user"], $GLOBALS["db_password"], $GLOBALS["db_database"]);
    if(!$db)
    {
        exit("connection error: ".mysqli_connect_error());
    }
    $ergebnis = mysqli_query($db,"SELECT Time, PublicKey, PrivateKey, FileHash FROM data WHERE PublicKey='".$key."' OR PrivateKey='".$key."' LIMIT 1");
    mysqli_close($db);
    return mysqli_fetch_array($ergebnis);
}
function isFree($key) { //Probably wrong
    $db = mysqli_connect($GLOBALS["db_server"], $GLOBALS["db_user"], $GLOBALS["db_password"], $GLOBALS["db_database"]);
    if(!$db)
    {
        exit("connection error: ".mysqli_connect_error());
    }
    $sql = "SELECT Time, PublicKey, PrivatKey, FileHash FROM data WHERE PublicKey='".$key."' OR PrivateKey='".$key."'";
    if ($result=mysqli_query($db,$sql))
  {
  return false;
  }
  return true;
    /*$ergebnis = mysqli_query($db,"SELECT Time, PublicKey, PrivatKey, FileHash FROM data WHERE PublicKey= ".$key." OR PrivatKey=".$key." LIMIT 1");
    mysqli_close($db);
    if(mysqli_num_rows($ergebnis)==0) {
        return false;
    }
    return true;*/
}
function save($timestamp, $publickey, $privatekey, $filehash) {
    $db = mysqli_connect($GLOBALS["db_server"], $GLOBALS["db_user"], $GLOBALS["db_password"], $GLOBALS["db_database"]);
    if(!$db)
    {
        exit("connection error: ".mysqli_connect_error());
    }
    $eintragen = mysqli_query($db, "INSERT INTO data (Time, PublicKey, PrivateKey, FileHash) VALUES ('$timestamp', '$publickey', '$privatekey', '$filehash')");
    mysqli_close($db);
}
?>
